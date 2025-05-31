# Esempio 3: Deploy Automation - Strategie di Deployment Avanzate

## Introduzione

Il deploy automation è fondamentale per garantire rilasci rapidi, sicuri e affidabili. In questo esempio esploreremo strategie di deployment avanzate utilizzando GitHub Actions, inclusi blue-green deployment, canary releases, e rollback automatici.

## Obiettivi dell'Esempio

- Implementare strategie di deployment enterprise
- Configurare ambienti di staging e produzione
- Gestire rollback automatici in caso di errori
- Implementare canary releases e blue-green deployment
- Integrare monitoraggio e alerting post-deployment

## Architettura del Sistema

### Ambiente Multi-Stage

```yaml
# .github/workflows/deploy-automation.yml
name: Advanced Deploy Automation

on:
  push:
    branches: [main, develop]
  pull_request:
    branches: [main]
  workflow_dispatch:
    inputs:
      environment:
        description: 'Deployment Environment'
        required: true
        default: 'staging'
        type: choice
        options:
        - staging
        - production
      deployment_strategy:
        description: 'Deployment Strategy'
        required: true
        default: 'rolling'
        type: choice
        options:
        - rolling
        - blue-green
        - canary

env:
  DOCKER_REGISTRY: ghcr.io
  IMAGE_NAME: ${{ github.repository }}
  HEALTH_CHECK_TIMEOUT: 300
  ROLLBACK_TIMEOUT: 600

jobs:
  # Build e Test
  build-and-test:
    runs-on: ubuntu-latest
    outputs:
      image-tag: ${{ steps.meta.outputs.tags }}
      image-digest: ${{ steps.build.outputs.digest }}
    steps:
      - name: Checkout
        uses: actions/checkout@v4

      - name: Set up Docker Buildx
        uses: docker/setup-buildx-action@v3

      - name: Log in to Container Registry
        uses: docker/login-action@v3
        with:
          registry: ${{ env.DOCKER_REGISTRY }}
          username: ${{ github.actor }}
          password: ${{ secrets.GITHUB_TOKEN }}

      - name: Extract metadata
        id: meta
        uses: docker/metadata-action@v5
        with:
          images: ${{ env.DOCKER_REGISTRY }}/${{ env.IMAGE_NAME }}
          tags: |
            type=ref,event=branch
            type=ref,event=pr
            type=sha,prefix={{branch}}-
            type=raw,value=latest,enable={{is_default_branch}}

      - name: Build and push Docker image
        id: build
        uses: docker/build-push-action@v5
        with:
          context: .
          push: true
          tags: ${{ steps.meta.outputs.tags }}
          labels: ${{ steps.meta.outputs.labels }}
          cache-from: type=gha
          cache-to: type=gha,mode=max

      - name: Run security scan
        uses: aquasecurity/trivy-action@master
        with:
          image-ref: ${{ steps.meta.outputs.tags }}
          format: 'sarif'
          output: 'trivy-results.sarif'

      - name: Upload security scan results
        uses: github/codeql-action/upload-sarif@v2
        if: always()
        with:
          sarif_file: 'trivy-results.sarif'

  # Deployment su Staging
  deploy-staging:
    needs: build-and-test
    if: github.ref == 'refs/heads/develop' || github.event_name == 'pull_request'
    runs-on: ubuntu-latest
    environment:
      name: staging
      url: https://staging.myapp.com
    steps:
      - name: Deploy to Staging
        uses: ./.github/actions/deploy
        with:
          environment: staging
          image: ${{ needs.build-and-test.outputs.image-tag }}
          strategy: rolling
          health-check-url: https://staging.myapp.com/health

  # Deployment su Produzione con Strategie Avanzate
  deploy-production:
    needs: build-and-test
    if: github.ref == 'refs/heads/main' || github.event.inputs.environment == 'production'
    runs-on: ubuntu-latest
    environment:
      name: production
      url: https://myapp.com
    steps:
      - name: Checkout
        uses: actions/checkout@v4

      - name: Determine deployment strategy
        id: strategy
        run: |
          if [ "${{ github.event.inputs.deployment_strategy }}" != "" ]; then
            echo "strategy=${{ github.event.inputs.deployment_strategy }}" >> $GITHUB_OUTPUT
          else
            # Default strategy based on time of day (example logic)
            hour=$(date +%H)
            if [ $hour -ge 9 ] && [ $hour -le 17 ]; then
              echo "strategy=canary" >> $GITHUB_OUTPUT
            else
              echo "strategy=blue-green" >> $GITHUB_OUTPUT
            fi
          fi

      - name: Blue-Green Deployment
        if: steps.strategy.outputs.strategy == 'blue-green'
        uses: ./.github/actions/blue-green-deploy
        with:
          image: ${{ needs.build-and-test.outputs.image-tag }}
          environment: production
          health-check-url: https://myapp.com/health

      - name: Canary Deployment
        if: steps.strategy.outputs.strategy == 'canary'
        uses: ./.github/actions/canary-deploy
        with:
          image: ${{ needs.build-and-test.outputs.image-tag }}
          environment: production
          traffic-percentage: 10

      - name: Rolling Deployment
        if: steps.strategy.outputs.strategy == 'rolling'
        uses: ./.github/actions/rolling-deploy
        with:
          image: ${{ needs.build-and-test.outputs.image-tag }}
          environment: production

  # Post-deployment monitoring
  post-deployment-monitoring:
    needs: [deploy-production]
    if: always() && needs.deploy-production.result == 'success'
    runs-on: ubuntu-latest
    steps:
      - name: Health Check
        id: health-check
        run: |
          echo "Performing health checks..."
          for i in {1..10}; do
            if curl -f https://myapp.com/health; then
              echo "Health check passed"
              echo "healthy=true" >> $GITHUB_OUTPUT
              break
            fi
            echo "Health check failed, attempt $i/10"
            sleep 30
          done
          
          if [ "$i" -eq 10 ]; then
            echo "healthy=false" >> $GITHUB_OUTPUT
          fi

      - name: Performance Test
        id: performance
        run: |
          echo "Running performance tests..."
          # Simulate performance test with Artillery or similar
          cat > artillery-config.yml << EOF
          config:
            target: 'https://myapp.com'
            phases:
              - duration: 120
                arrivalRate: 10
          scenarios:
            - name: "Load test"
              requests:
                - get:
                    url: "/"
                - get:
                    url: "/api/status"
          EOF
          
          # Mock performance test result
          response_time=250
          error_rate=0.1
          
          if [ $response_time -lt 500 ] && [ $(echo "$error_rate < 1.0" | bc) -eq 1 ]; then
            echo "performance=good" >> $GITHUB_OUTPUT
          else
            echo "performance=poor" >> $GITHUB_OUTPUT
          fi

      - name: Rollback on failure
        if: steps.health-check.outputs.healthy == 'false' || steps.performance.outputs.performance == 'poor'
        uses: ./.github/actions/rollback
        with:
          environment: production
          reason: "Health check or performance test failed"

      - name: Send notification
        uses: 8398a7/action-slack@v3
        with:
          status: ${{ job.status }}
          text: |
            Deployment Status: ${{ job.status }}
            Health Check: ${{ steps.health-check.outputs.healthy }}
            Performance: ${{ steps.performance.outputs.performance }}
            Environment: production
            Commit: ${{ github.sha }}
        env:
          SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK }}
```

## Custom Actions per Deployment

### Blue-Green Deployment Action

```yaml
# .github/actions/blue-green-deploy/action.yml
name: 'Blue-Green Deployment'
description: 'Deploys using blue-green strategy'
inputs:
  image:
    description: 'Docker image to deploy'
    required: true
  environment:
    description: 'Target environment'
    required: true
  health-check-url:
    description: 'Health check URL'
    required: true

runs:
  using: 'composite'
  steps:
    - name: Setup kubectl
      uses: azure/setup-kubectl@v3

    - name: Configure kubectl
      shell: bash
      run: |
        echo "${{ secrets.KUBECONFIG }}" | base64 -d > kubeconfig
        export KUBECONFIG=kubeconfig

    - name: Determine current environment
      id: current
      shell: bash
      run: |
        current_color=$(kubectl get service app-service -o jsonpath='{.spec.selector.version}' || echo "blue")
        if [ "$current_color" = "blue" ]; then
          echo "new-color=green" >> $GITHUB_OUTPUT
          echo "old-color=blue" >> $GITHUB_OUTPUT
        else
          echo "new-color=blue" >> $GITHUB_OUTPUT
          echo "old-color=green" >> $GITHUB_OUTPUT
        fi

    - name: Deploy new version
      shell: bash
      run: |
        cat > deployment-${{ steps.current.outputs.new-color }}.yml << EOF
        apiVersion: apps/v1
        kind: Deployment
        metadata:
          name: app-${{ steps.current.outputs.new-color }}
          labels:
            app: myapp
            version: ${{ steps.current.outputs.new-color }}
        spec:
          replicas: 3
          selector:
            matchLabels:
              app: myapp
              version: ${{ steps.current.outputs.new-color }}
          template:
            metadata:
              labels:
                app: myapp
                version: ${{ steps.current.outputs.new-color }}
            spec:
              containers:
              - name: app
                image: ${{ inputs.image }}
                ports:
                - containerPort: 8080
                livenessProbe:
                  httpGet:
                    path: /health
                    port: 8080
                  initialDelaySeconds: 30
                  periodSeconds: 10
                readinessProbe:
                  httpGet:
                    path: /ready
                    port: 8080
                  initialDelaySeconds: 5
                  periodSeconds: 5
        EOF
        
        kubectl apply -f deployment-${{ steps.current.outputs.new-color }}.yml

    - name: Wait for deployment
      shell: bash
      run: |
        kubectl rollout status deployment/app-${{ steps.current.outputs.new-color }} --timeout=300s

    - name: Test new deployment
      shell: bash
      run: |
        # Port forward for testing
        kubectl port-forward deployment/app-${{ steps.current.outputs.new-color }} 8080:8080 &
        sleep 10
        
        # Test health endpoint
        for i in {1..5}; do
          if curl -f http://localhost:8080/health; then
            echo "Health check passed"
            break
          fi
          sleep 10
        done

    - name: Switch traffic
      shell: bash
      run: |
        cat > service.yml << EOF
        apiVersion: v1
        kind: Service
        metadata:
          name: app-service
        spec:
          selector:
            app: myapp
            version: ${{ steps.current.outputs.new-color }}
          ports:
          - port: 80
            targetPort: 8080
          type: LoadBalancer
        EOF
        
        kubectl apply -f service.yml

    - name: Verify traffic switch
      shell: bash
      run: |
        sleep 30
        for i in {1..10}; do
          if curl -f ${{ inputs.health-check-url }}; then
            echo "Traffic switch successful"
            break
          fi
          sleep 10
        done

    - name: Cleanup old deployment
      shell: bash
      run: |
        kubectl delete deployment app-${{ steps.current.outputs.old-color }} --ignore-not-found=true
```

### Canary Deployment Action

```yaml
# .github/actions/canary-deploy/action.yml
name: 'Canary Deployment'
description: 'Deploys using canary strategy'
inputs:
  image:
    description: 'Docker image to deploy'
    required: true
  environment:
    description: 'Target environment'
    required: true
  traffic-percentage:
    description: 'Percentage of traffic for canary'
    required: true
    default: '10'

runs:
  using: 'composite'
  steps:
    - name: Deploy canary version
      shell: bash
      run: |
        cat > canary-deployment.yml << EOF
        apiVersion: apps/v1
        kind: Deployment
        metadata:
          name: app-canary
          labels:
            app: myapp
            version: canary
        spec:
          replicas: 1
          selector:
            matchLabels:
              app: myapp
              version: canary
          template:
            metadata:
              labels:
                app: myapp
                version: canary
            spec:
              containers:
              - name: app
                image: ${{ inputs.image }}
                ports:
                - containerPort: 8080
        EOF
        
        kubectl apply -f canary-deployment.yml

    - name: Configure traffic splitting
      shell: bash
      run: |
        # Using Istio for traffic management
        cat > virtual-service.yml << EOF
        apiVersion: networking.istio.io/v1beta1
        kind: VirtualService
        metadata:
          name: app-vs
        spec:
          hosts:
          - myapp.com
          http:
          - match:
            - headers:
                canary:
                  exact: "true"
            route:
            - destination:
                host: app-service
                subset: canary
          - route:
            - destination:
                host: app-service
                subset: stable
              weight: ${{ 100 - inputs.traffic-percentage }}
            - destination:
                host: app-service
                subset: canary
              weight: ${{ inputs.traffic-percentage }}
        EOF
        
        kubectl apply -f virtual-service.yml

    - name: Monitor canary metrics
      shell: bash
      run: |
        echo "Monitoring canary deployment for 5 minutes..."
        sleep 300
        
        # Check error rate and latency
        error_rate=$(kubectl exec -it prometheus-pod -- promtool query instant 'rate(http_requests_total{status=~"5.."}[5m]) / rate(http_requests_total[5m])')
        
        if [ $(echo "$error_rate > 0.01" | bc) -eq 1 ]; then
          echo "High error rate detected, rolling back canary"
          exit 1
        fi

    - name: Promote canary on success
      shell: bash
      run: |
        # Scale up canary and scale down stable
        kubectl scale deployment app-stable --replicas=0
        kubectl scale deployment app-canary --replicas=3
        
        # Update service to point to canary
        kubectl patch service app-service -p '{"spec":{"selector":{"version":"canary"}}}'
        
        # Clean up
        kubectl delete deployment app-stable
        kubectl label deployment app-canary version=stable
```

### Rollback Action

```yaml
# .github/actions/rollback/action.yml
name: 'Automatic Rollback'
description: 'Performs automatic rollback to previous version'
inputs:
  environment:
    description: 'Environment to rollback'
    required: true
  reason:
    description: 'Reason for rollback'
    required: true

runs:
  using: 'composite'
  steps:
    - name: Get previous deployment
      id: previous
      shell: bash
      run: |
        previous_image=$(kubectl rollout history deployment/app --revision=1 -o jsonpath='{.spec.template.spec.containers[0].image}')
        echo "image=$previous_image" >> $GITHUB_OUTPUT

    - name: Rollback deployment
      shell: bash
      run: |
        kubectl rollout undo deployment/app
        kubectl rollout status deployment/app --timeout=300s

    - name: Verify rollback
      shell: bash
      run: |
        for i in {1..10}; do
          if curl -f https://myapp.com/health; then
            echo "Rollback successful"
            break
          fi
          sleep 30
        done

    - name: Create incident report
      shell: bash
      run: |
        cat > incident-report.json << EOF
        {
          "timestamp": "$(date -u +%Y-%m-%dT%H:%M:%SZ)",
          "environment": "${{ inputs.environment }}",
          "reason": "${{ inputs.reason }}",
          "previous_image": "${{ steps.previous.outputs.image }}",
          "rollback_commit": "${{ github.sha }}",
          "triggered_by": "${{ github.actor }}"
        }
        EOF
        
        # Send to incident management system
        curl -X POST -H "Content-Type: application/json" \
             -d @incident-report.json \
             "${{ secrets.INCIDENT_WEBHOOK_URL }}"
```

## Configurazione Kubernetes

### Namespace e RBAC

```yaml
# k8s/namespace.yml
apiVersion: v1
kind: Namespace
metadata:
  name: myapp-production
---
apiVersion: v1
kind: Namespace
metadata:
  name: myapp-staging
---
apiVersion: v1
kind: ServiceAccount
metadata:
  name: github-actions
  namespace: myapp-production
---
apiVersion: rbac.authorization.k8s.io/v1
kind: Role
metadata:
  namespace: myapp-production
  name: github-actions-role
rules:
- apiGroups: ["apps"]
  resources: ["deployments"]
  verbs: ["get", "list", "create", "update", "patch", "delete"]
- apiGroups: [""]
  resources: ["services", "pods"]
  verbs: ["get", "list", "create", "update", "patch", "delete"]
---
apiVersion: rbac.authorization.k8s.io/v1
kind: RoleBinding
metadata:
  name: github-actions-binding
  namespace: myapp-production
subjects:
- kind: ServiceAccount
  name: github-actions
  namespace: myapp-production
roleRef:
  kind: Role
  name: github-actions-role
  apiGroup: rbac.authorization.k8s.io
```

## Monitoraggio e Alerting

### Prometheus Configuration

```yaml
# monitoring/prometheus-rules.yml
groups:
- name: deployment.rules
  rules:
  - alert: DeploymentFailed
    expr: kube_deployment_status_replicas_unavailable > 0
    for: 5m
    labels:
      severity: critical
    annotations:
      summary: "Deployment has unavailable replicas"
      description: "{{ $labels.deployment }} has {{ $value }} unavailable replicas"

  - alert: HighErrorRate
    expr: rate(http_requests_total{status=~"5.."}[5m]) / rate(http_requests_total[5m]) > 0.01
    for: 2m
    labels:
      severity: warning
    annotations:
      summary: "High error rate detected"
      description: "Error rate is {{ $value | humanizePercentage }}"

  - alert: HighLatency
    expr: histogram_quantile(0.95, rate(http_request_duration_seconds_bucket[5m])) > 0.5
    for: 5m
    labels:
      severity: warning
    annotations:
      summary: "High latency detected"
      description: "95th percentile latency is {{ $value }}s"
```

## Script di Utilità

### Health Check Script

```bash
#!/bin/bash
# scripts/health-check.sh

HEALTH_URL=$1
TIMEOUT=${2:-300}
INTERVAL=${3:-10}

echo "Starting health check for $HEALTH_URL"
echo "Timeout: ${TIMEOUT}s, Interval: ${INTERVAL}s"

start_time=$(date +%s)
while true; do
    current_time=$(date +%s)
    elapsed=$((current_time - start_time))
    
    if [ $elapsed -gt $TIMEOUT ]; then
        echo "Health check timed out after ${TIMEOUT}s"
        exit 1
    fi
    
    if curl -f -s "$HEALTH_URL" > /dev/null; then
        echo "Health check passed after ${elapsed}s"
        exit 0
    fi
    
    echo "Health check failed, retrying in ${INTERVAL}s... (${elapsed}/${TIMEOUT}s elapsed)"
    sleep $INTERVAL
done
```

### Deployment Status Script

```bash
#!/bin/bash
# scripts/deployment-status.sh

NAMESPACE=${1:-default}
DEPLOYMENT=${2:-app}

echo "Checking deployment status for $DEPLOYMENT in namespace $NAMESPACE"

# Get deployment status
kubectl get deployment $DEPLOYMENT -n $NAMESPACE -o jsonpath='{.status.conditions[?(@.type=="Progressing")].status}'

# Get pod status
echo "Pod status:"
kubectl get pods -n $NAMESPACE -l app=$DEPLOYMENT

# Get events
echo "Recent events:"
kubectl get events -n $NAMESPACE --field-selector involvedObject.name=$DEPLOYMENT --sort-by='.lastTimestamp' | tail -10
```

## Configurazione Secrets

### GitHub Secrets necessari

```bash
# Repository secrets richiesti
KUBECONFIG                 # Base64 encoded kubeconfig
DOCKER_USERNAME           # Docker registry username
DOCKER_PASSWORD           # Docker registry password
SLACK_WEBHOOK             # Slack webhook URL for notifications
INCIDENT_WEBHOOK_URL      # Incident management webhook
AWS_ACCESS_KEY_ID         # AWS credentials (se necessario)
AWS_SECRET_ACCESS_KEY     # AWS credentials (se necessario)
DATADOG_API_KEY          # Datadog API key per monitoring
```

## Best Practices Implementate

### 1. **Sicurezza**
- Scansione vulnerabilità con Trivy
- RBAC per accesso Kubernetes limitato
- Secrets management con GitHub Secrets
- Firma e verifica immagini Docker

### 2. **Affidabilità**
- Health checks multi-livello
- Rollback automatico su fallimenti
- Timeout configurabili
- Retry logic per operazioni critiche

### 3. **Observability**
- Logging strutturato
- Metriche custom per deployment
- Alerting proattivo
- Incident reporting automatico

### 4. **Performance**
- Deploy paralleli quando possibile
- Cache per build Docker
- Ottimizzazione immagini container
- Load testing post-deployment

## Risultati Attesi

Dopo aver implementato questo sistema di deploy automation:

1. **Deployment Sicuri**: Zero-downtime deployments con rollback automatico
2. **Monitoring Proattivo**: Rilevamento precoce di problemi
3. **Scalabilità**: Supporto per multiple strategie di deployment
4. **Compliance**: Audit trail completo di tutti i deployment
5. **Efficienza**: Riduzione del time-to-market e degli errori manuali

## Quiz di Verifica

### Domanda 1
Quale strategia di deployment è più adatta per un'applicazione critica che richiede zero downtime?

A) Rolling deployment
B) Blue-green deployment
C) Canary deployment
D) Direct replacement

**Risposta: B) Blue-green deployment**

Il blue-green deployment garantisce zero downtime mantenendo due ambienti identici e switchando il traffico istantaneamente tra di essi.

### Domanda 2
In un canary deployment, quale percentuale di traffico dovrebbe inizialmente ricevere la nuova versione?

A) 50%
B) 25%
C) 5-10%
D) 100%

**Risposta: C) 5-10%**

Il canary deployment inizia con una piccola percentuale di traffico (5-10%) per minimizzare l'impatto di eventuali problemi.

### Domanda 3
Qual è il timeout raccomandato per un health check post-deployment?

A) 30 secondi
B) 2 minuti
C) 5 minuti
D) 10 minuti

**Risposta: C) 5 minuti**

5 minuti fornisce tempo sufficiente per il warm-up dell'applicazione mantenendo un feedback rapido.

## Conclusione

Questo esempio dimostra come implementare un sistema di deploy automation enterprise-grade con GitHub Actions. Le strategie presentate garantiscono deployment sicuri, monitoraggio proattivo e capacità di rollback automatico, elementi essenziali per ambienti di produzione critici.
