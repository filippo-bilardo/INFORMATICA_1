# Esempio 4: Monitoring e Observability - Sistema di Monitoraggio Completo

## Introduzione

Il monitoraggio e l'observability sono componenti critici per mantenere sistemi affidabili in produzione. In questo esempio implementeremo un sistema completo di monitoraggio, logging, metrics e alerting utilizzando GitHub Actions, integrando strumenti moderni di observability.

## Obiettivi dell'Esempio

- Implementare monitoring end-to-end delle pipeline CI/CD
- Configurare logging strutturato e centralizzato
- Integrare metrics e alerting in tempo reale
- Implementare health checks automatizzati
- Creare dashboard di osservabilità comprehensive

## Sistema di Monitoring Completo

### 1. Workflow di Monitoring Base

```yaml
# .github/workflows/monitoring-observability.yml
name: Monitoring and Observability Pipeline

on:
  push:
    branches: [main, develop]
  schedule:
    # Health check ogni 15 minuti
    - cron: '*/15 * * * *'
  workflow_dispatch:
    inputs:
      monitoring_level:
        description: 'Monitoring Level'
        required: true
        default: 'standard'
        type: choice
        options:
        - basic
        - standard
        - comprehensive
      alert_channels:
        description: 'Alert Channels'
        required: false
        default: 'slack,email'

env:
  MONITORING_STACK: prometheus-grafana
  LOG_LEVEL: info
  METRICS_RETENTION: 30d

jobs:
  setup-monitoring:
    name: Setup Monitoring Infrastructure
    runs-on: ubuntu-latest
    outputs:
      monitoring-id: ${{ steps.setup.outputs.monitoring-id }}
      grafana-url: ${{ steps.setup.outputs.grafana-url }}
      prometheus-url: ${{ steps.setup.outputs.prometheus-url }}
    
    steps:
    - name: Checkout Repository
      uses: actions/checkout@v4
    
    - name: Setup Monitoring Stack
      id: setup
      run: |
        # Genera ID univoco per questa sessione di monitoring
        MONITORING_ID="mon-$(date +%Y%m%d-%H%M%S)-${{ github.run_number }}"
        echo "monitoring-id=$MONITORING_ID" >> $GITHUB_OUTPUT
        
        # Configure monitoring URLs
        echo "grafana-url=https://grafana.example.com/d/$MONITORING_ID" >> $GITHUB_OUTPUT
        echo "prometheus-url=https://prometheus.example.com/graph" >> $GITHUB_OUTPUT
        
        echo "🔍 Monitoring ID: $MONITORING_ID"
        echo "📊 Monitoring stack configured"

  application-monitoring:
    name: Application Performance Monitoring
    runs-on: ubuntu-latest
    needs: setup-monitoring
    strategy:
      matrix:
        service: [frontend, backend, database, cache]
        environment: [staging, production]
      fail-fast: false
    
    steps:
    - name: Checkout Code
      uses: actions/checkout@v4
    
    - name: Setup Node.js
      uses: actions/setup-node@v4
      with:
        node-version: '20'
        cache: 'npm'
    
    - name: Install Dependencies
      run: |
        npm ci
        npm install -g artillery clinic autocannon
    
    - name: Performance Monitoring - ${{ matrix.service }}
      run: |
        echo "🚀 Starting performance monitoring for ${{ matrix.service }} in ${{ matrix.environment }}"
        
        # Configurazione specifica per servizio
        case "${{ matrix.service }}" in
          "frontend")
            # Frontend performance monitoring
            echo "📱 Frontend Performance Tests"
            npx lighthouse-ci autorun --config=.lighthouseci.json
            ;;
          "backend")
            # Backend API monitoring
            echo "🔧 Backend API Load Testing"
            artillery run tests/load/api-load-test.yml --output monitoring/results/backend-${{ matrix.environment }}.json
            ;;
          "database")
            # Database performance monitoring
            echo "🗄️ Database Performance Analysis"
            # Simula query performance monitoring
            cat << 'EOF' > monitoring/db-performance.sql
            SELECT 
                query_id,
                mean_exec_time,
                calls,
                total_exec_time,
                query
            FROM pg_stat_statements
            WHERE mean_exec_time > 100
            ORDER BY mean_exec_time DESC
            LIMIT 20;
EOF
            ;;
          "cache")
            # Cache performance monitoring
            echo "⚡ Cache Performance Monitoring"
            # Redis performance metrics
            echo "MEMORY USAGE" > monitoring/cache-stats.txt
            echo "INFO MEMORY" >> monitoring/cache-stats.txt
            ;;
        esac
    
    - name: Collect Metrics
      run: |
        # Crea directory per metrics
        mkdir -p monitoring/metrics/${{ matrix.service }}/${{ matrix.environment }}
        
        # Simula raccolta metrics
        cat << EOF > monitoring/metrics/${{ matrix.service }}/${{ matrix.environment }}/metrics.json
        {
          "timestamp": "$(date -u +%Y-%m-%dT%H:%M:%SZ)",
          "service": "${{ matrix.service }}",
          "environment": "${{ matrix.environment }}",
          "monitoring_id": "${{ needs.setup-monitoring.outputs.monitoring-id }}",
          "metrics": {
            "response_time_p95": $(shuf -i 50-500 -n 1),
            "response_time_p99": $(shuf -i 100-1000 -n 1),
            "throughput_rps": $(shuf -i 100-1000 -n 1),
            "error_rate": $(echo "scale=3; $(shuf -i 0-50 -n 1) / 1000" | bc),
            "cpu_usage": $(shuf -i 20-80 -n 1),
            "memory_usage": $(shuf -i 30-90 -n 1),
            "disk_usage": $(shuf -i 10-70 -n 1)
          },
          "health_status": "healthy"
        }
EOF
        
        echo "📊 Metrics collected for ${{ matrix.service }} in ${{ matrix.environment }}"
    
    - name: Upload Metrics Artifacts
      uses: actions/upload-artifact@v4
      with:
        name: metrics-${{ matrix.service }}-${{ matrix.environment }}
        path: monitoring/metrics/
        retention-days: 30

  log-aggregation:
    name: Log Aggregation and Analysis
    runs-on: ubuntu-latest
    needs: setup-monitoring
    
    steps:
    - name: Checkout Repository
      uses: actions/checkout@v4
    
    - name: Setup Log Processing Tools
      run: |
        # Installa strumenti per log processing
        sudo apt-get update
        sudo apt-get install -y jq logrotate rsyslog
        
        # Setup log aggregation directory
        mkdir -p logs/aggregated logs/processed logs/alerts
    
    - name: Simulate Application Logs
      run: |
        # Genera logs di esempio con diversi livelli
        generate_logs() {
          local service=$1
          local count=$2
          
          for i in $(seq 1 $count); do
            timestamp=$(date -u +%Y-%m-%dT%H:%M:%SZ)
            level=$(shuf -e "INFO" "WARN" "ERROR" "DEBUG" -n 1)
            
            case $level in
              "ERROR")
                message="Database connection failed for user session"
                ;;
              "WARN")
                message="High response time detected: ${RANDOM}ms"
                ;;
              "INFO")
                message="Request processed successfully"
                ;;
              "DEBUG")
                message="Cache hit ratio: $((RANDOM % 100))%"
                ;;
            esac
            
            echo "{\"timestamp\":\"$timestamp\",\"level\":\"$level\",\"service\":\"$service\",\"message\":\"$message\",\"request_id\":\"req-$RANDOM\",\"user_id\":\"user-$((RANDOM % 1000))\"}" >> logs/$service.jsonl
          done
        }
        
        # Genera logs per diversi servizi
        generate_logs "frontend" 500
        generate_logs "backend" 1000
        generate_logs "database" 300
        generate_logs "cache" 200
        
        echo "📝 Generated $(wc -l logs/*.jsonl | tail -1 | awk '{print $1}') log entries"
    
    - name: Process and Analyze Logs
      run: |
        # Analisi degli errori
        echo "🔍 Analyzing error patterns..."
        
        # Conta errori per servizio
        for service in frontend backend database cache; do
          error_count=$(jq -r 'select(.level == "ERROR")' logs/$service.jsonl | wc -l)
          warn_count=$(jq -r 'select(.level == "WARN")' logs/$service.jsonl | wc -l)
          
          echo "Service: $service - Errors: $error_count, Warnings: $warn_count"
          
          # Crea report per servizio
          cat << EOF > logs/processed/$service-report.json
        {
          "service": "$service",
          "timestamp": "$(date -u +%Y-%m-%dT%H:%M:%SZ)",
          "monitoring_id": "${{ needs.setup-monitoring.outputs.monitoring-id }}",
          "summary": {
            "total_logs": $(wc -l logs/$service.jsonl | awk '{print $1}'),
            "error_count": $error_count,
            "warning_count": $warn_count,
            "error_rate": $(echo "scale=4; $error_count * 100 / $(wc -l logs/$service.jsonl | awk '{print $1}')" | bc)
          },
          "top_errors": [
$(jq -r 'select(.level == "ERROR") | .message' logs/$service.jsonl | sort | uniq -c | sort -nr | head -5 | while read count msg; do
  echo "            {\"count\": $count, \"message\": \"$msg\"}"
done | paste -sd ',' -)
          ]
        }
EOF
        done
        
        # Crea report aggregato
        total_errors=$(cat logs/processed/*-report.json | jq '.summary.error_count' | awk '{sum += $1} END {print sum}')
        echo "🚨 Total errors across all services: $total_errors"
        
        # Alert se troppi errori
        if [ $total_errors -gt 50 ]; then
          echo "⚠️ High error rate detected: $total_errors errors" > logs/alerts/high-error-rate.alert
        fi
    
    - name: Upload Log Analysis
      uses: actions/upload-artifact@v4
      with:
        name: log-analysis-${{ needs.setup-monitoring.outputs.monitoring-id }}
        path: logs/
        retention-days: 30

  health-checks:
    name: Comprehensive Health Checks
    runs-on: ubuntu-latest
    needs: setup-monitoring
    strategy:
      matrix:
        check_type: [endpoint, database, external_services, infrastructure]
    
    steps:
    - name: Checkout Code
      uses: actions/checkout@v4
    
    - name: Setup Health Check Tools
      run: |
        # Installa strumenti per health checks
        curl -L https://github.com/mcuadros/go-healthcheck/releases/download/v1.0.0/healthcheck_linux_amd64 -o healthcheck
        chmod +x healthcheck
        
        # Setup curl per API testing
        sudo apt-get update
        sudo apt-get install -y curl jq netcat-openbsd
    
    - name: Execute Health Checks - ${{ matrix.check_type }}
      run: |
        mkdir -p health-checks/${{ matrix.check_type }}
        
        case "${{ matrix.check_type }}" in
          "endpoint")
            echo "🌐 Checking API endpoints..."
            
            # Lista di endpoint da controllare
            endpoints=(
              "https://api.example.com/health"
              "https://api.example.com/version"
              "https://api.example.com/metrics"
            )
            
            for endpoint in "${endpoints[@]}"; do
              echo "Checking $endpoint..."
              
              # Simula health check (usando httpbin per testing)
              status_code=$(curl -s -o /dev/null -w "%{http_code}" "https://httpbin.org/status/200" || echo "000")
              response_time=$(curl -s -o /dev/null -w "%{time_total}" "https://httpbin.org/delay/1" || echo "999")
              
              cat << EOF > health-checks/${{ matrix.check_type }}/$(basename $endpoint).json
        {
          "endpoint": "$endpoint",
          "status_code": $status_code,
          "response_time": $response_time,
          "timestamp": "$(date -u +%Y-%m-%dT%H:%M:%SZ)",
          "healthy": $([ $status_code -eq 200 ] && echo "true" || echo "false")
        }
EOF
            done
            ;;
            
          "database")
            echo "🗄️ Checking database connectivity..."
            
            # Simula database health checks
            databases=("postgres" "redis" "mongodb")
            
            for db in "${databases[@]}"; do
              # Simula check di connessione
              connection_time=$(echo "scale=3; $(shuf -i 1-100 -n 1) / 100" | bc)
              query_time=$(echo "scale=3; $(shuf -i 5-200 -n 1) / 100" | bc)
              
              cat << EOF > health-checks/${{ matrix.check_type }}/$db.json
        {
          "database": "$db",
          "connection_time": $connection_time,
          "query_time": $query_time,
          "timestamp": "$(date -u +%Y-%m-%dT%H:%M:%SZ)",
          "healthy": true,
          "pool_size": $(shuf -i 5-50 -n 1),
          "active_connections": $(shuf -i 1-30 -n 1)
        }
EOF
            done
            ;;
            
          "external_services")
            echo "🔗 Checking external service dependencies..."
            
            services=("payment-gateway" "email-service" "analytics-api")
            
            for service in "${services[@]}"; do
              # Simula check di servizi esterni
              availability=$([ $((RANDOM % 100)) -gt 5 ] && echo "true" || echo "false")
              latency=$(shuf -i 50-500 -n 1)
              
              cat << EOF > health-checks/${{ matrix.check_type }}/$service.json
        {
          "service": "$service",
          "available": $availability,
          "latency_ms": $latency,
          "timestamp": "$(date -u +%Y-%m-%dT%H:%M:%SZ)",
          "last_successful_call": "$(date -u -d '1 minute ago' +%Y-%m-%dT%H:%M:%SZ)"
        }
EOF
            done
            ;;
            
          "infrastructure")
            echo "🏗️ Checking infrastructure health..."
            
            # Simula infrastructure checks
            components=("load-balancer" "cdn" "dns" "ssl-certificates")
            
            for component in "${components[@]}"; do
              health_score=$(shuf -i 85-100 -n 1)
              
              cat << EOF > health-checks/${{ matrix.check_type }}/$component.json
        {
          "component": "$component",
          "health_score": $health_score,
          "status": "$([ $health_score -gt 90 ] && echo "excellent" || echo "good")",
          "timestamp": "$(date -u +%Y-%m-%dT%H:%M:%SZ)",
          "details": {
            "uptime": "99.9%",
            "last_incident": "$(date -u -d '7 days ago' +%Y-%m-%dT%H:%M:%SZ)"
          }
        }
EOF
            done
            ;;
        esac
        
        echo "✅ Health checks completed for ${{ matrix.check_type }}"
    
    - name: Upload Health Check Results
      uses: actions/upload-artifact@v4
      with:
        name: health-checks-${{ matrix.check_type }}
        path: health-checks/
        retention-days: 7

  alerting-system:
    name: Alerting and Notification System
    runs-on: ubuntu-latest
    needs: [application-monitoring, log-aggregation, health-checks]
    if: always()
    
    steps:
    - name: Download All Monitoring Data
      uses: actions/download-artifact@v4
      with:
        path: monitoring-data/
    
    - name: Analyze Monitoring Data
      run: |
        echo "📊 Analyzing monitoring data for alerts..."
        
        # Inizializza alert summary
        mkdir -p alerts
        
        cat << 'EOF' > alerts/alert-summary.json
        {
          "timestamp": "'$(date -u +%Y-%m-%dT%H:%M:%SZ)'",
          "monitoring_run": "'${{ github.run_id }}'",
          "alerts": [],
          "summary": {
            "critical": 0,
            "warning": 0,
            "info": 0
          }
        }
EOF
        
        # Analizza metrics per alert
        if find monitoring-data -name "*.json" -type f | head -1 >/dev/null 2>&1; then
          echo "🔍 Processing metrics data..."
          
          # Conta servizi con problemi
          error_services=0
          high_latency_services=0
          
          for metrics_file in monitoring-data/*/monitoring/metrics/*/*/metrics.json; do
            if [ -f "$metrics_file" ]; then
              error_rate=$(jq -r '.metrics.error_rate' "$metrics_file" 2>/dev/null || echo "0")
              response_time=$(jq -r '.metrics.response_time_p95' "$metrics_file" 2>/dev/null || echo "0")
              
              # Check error rate (> 0.01 = 1%)
              if [ "$(echo "$error_rate > 0.01" | bc 2>/dev/null || echo 0)" -eq 1 ]; then
                error_services=$((error_services + 1))
              fi
              
              # Check response time (> 400ms)
              if [ "$(echo "$response_time > 400" | bc 2>/dev/null || echo 0)" -eq 1 ]; then
                high_latency_services=$((high_latency_services + 1))
              fi
            fi
          done
          
          # Crea alert se necessario
          if [ $error_services -gt 0 ]; then
            echo "🚨 CRITICAL: $error_services services with high error rates"
            jq '.alerts += [{"level": "critical", "message": "High error rate detected in '$error_services' services", "timestamp": "'$(date -u +%Y-%m-%dT%H:%M:%SZ)'"}] | .summary.critical += 1' alerts/alert-summary.json > alerts/temp.json && mv alerts/temp.json alerts/alert-summary.json
          fi
          
          if [ $high_latency_services -gt 0 ]; then
            echo "⚠️ WARNING: $high_latency_services services with high latency"
            jq '.alerts += [{"level": "warning", "message": "High latency detected in '$high_latency_services' services", "timestamp": "'$(date -u +%Y-%m-%dT%H:%M:%SZ)'"}] | .summary.warning += 1' alerts/alert-summary.json > alerts/temp.json && mv alerts/temp.json alerts/alert-summary.json
          fi
        fi
        
        # Controlla log alerts
        if find monitoring-data -name "*.alert" -type f | head -1 >/dev/null 2>&1; then
          alert_count=$(find monitoring-data -name "*.alert" -type f | wc -l)
          echo "🚨 Found $alert_count log-based alerts"
          jq '.alerts += [{"level": "warning", "message": "Found '$alert_count' log-based alerts", "timestamp": "'$(date -u +%Y-%m-%dT%H:%M:%SZ)'"}] | .summary.warning += 1' alerts/alert-summary.json > alerts/temp.json && mv alerts/temp.json alerts/alert-summary.json
        fi
    
    - name: Send Notifications
      run: |
        # Leggi alert summary
        total_alerts=$(jq '.summary.critical + .summary.warning' alerts/alert-summary.json)
        
        if [ "$total_alerts" -gt 0 ]; then
          echo "📢 Sending notifications for $total_alerts alerts..."
          
          # Simula invio notifiche
          echo "📧 Email notification sent"
          echo "💬 Slack notification sent"
          echo "📱 PagerDuty alert created"
          
          # Crea notification log
          cat << EOF > alerts/notifications.log
        $(date -u +%Y-%m-%dT%H:%M:%SZ) - Email sent to ops-team@example.com
        $(date -u +%Y-%m-%dT%H:%M:%SZ) - Slack message posted to #alerts
        $(date -u +%Y-%m-%dT%H:%M:%SZ) - PagerDuty incident created: INC-$(date +%Y%m%d)-${{ github.run_number }}
EOF
        else
          echo "✅ No alerts to send - all systems healthy"
        fi
    
    - name: Generate Monitoring Report
      run: |
        # Crea report completo di monitoring
        cat << EOF > monitoring-report.md
        # Monitoring Report - $(date -u +%Y-%m-%d)
        
        **Monitoring ID:** ${{ needs.setup-monitoring.outputs.monitoring-id }}  
        **GitHub Run:** ${{ github.run_id }}  
        **Timestamp:** $(date -u +%Y-%m-%dT%H:%M:%SZ)
        
        ## Summary
        
        - **Total Services Monitored:** $(find monitoring-data -name "metrics.json" -type f | wc -l)
        - **Health Checks Performed:** $(find monitoring-data -name "*.json" -path "*/health-checks/*" -type f | wc -l)
        - **Log Entries Analyzed:** $(find monitoring-data -name "*.jsonl" -type f -exec wc -l {} + 2>/dev/null | tail -1 | awk '{print $1}' || echo "0")
        - **Alerts Generated:** $(jq '.summary.critical + .summary.warning' alerts/alert-summary.json)
        
        ## Alert Summary
        
        $(jq -r '.alerts[] | "- **" + .level + ":** " + .message + " (" + .timestamp + ")"' alerts/alert-summary.json)
        
        ## Dashboard Links
        
        - [Grafana Dashboard](${{ needs.setup-monitoring.outputs.grafana-url }})
        - [Prometheus Metrics](${{ needs.setup-monitoring.outputs.prometheus-url }})
        
        ## Next Steps
        
        1. Review critical alerts and take immediate action
        2. Investigate warning conditions
        3. Update monitoring thresholds if needed
        4. Schedule follow-up monitoring
        
        ---
        *Generated by GitHub Actions Monitoring Pipeline*
EOF
        
        echo "📋 Monitoring report generated"
    
    - name: Upload Monitoring Report
      uses: actions/upload-artifact@v4
      with:
        name: monitoring-report-${{ needs.setup-monitoring.outputs.monitoring-id }}
        path: |
          monitoring-report.md
          alerts/
        retention-days: 30
    
    - name: Comment on PR (if applicable)
      if: github.event_name == 'pull_request'
      uses: actions/github-script@v7
      with:
        script: |
          const fs = require('fs');
          const report = fs.readFileSync('monitoring-report.md', 'utf8');
          
          github.rest.issues.createComment({
            issue_number: context.issue.number,
            owner: context.repo.owner,
            repo: context.repo.repo,
            body: `## 🔍 Monitoring Report\n\n${report}`
          });

  monitoring-dashboard:
    name: Deploy Monitoring Dashboard
    runs-on: ubuntu-latest
    needs: [setup-monitoring, alerting-system]
    if: github.ref == 'refs/heads/main'
    
    steps:
    - name: Checkout Repository
      uses: actions/checkout@v4
    
    - name: Setup Dashboard Configuration
      run: |
        mkdir -p dashboard/config dashboard/templates
        
        # Crea configurazione Grafana
        cat << 'EOF' > dashboard/config/grafana-dashboard.json
        {
          "dashboard": {
            "id": null,
            "title": "GitHub Actions Monitoring",
            "tags": ["github-actions", "ci-cd", "monitoring"],
            "timezone": "UTC",
            "panels": [
              {
                "id": 1,
                "title": "Pipeline Success Rate",
                "type": "stat",
                "targets": [
                  {
                    "expr": "rate(github_actions_workflow_runs_total{status=\"success\"}[5m])"
                  }
                ]
              },
              {
                "id": 2,
                "title": "Average Build Time",
                "type": "graph",
                "targets": [
                  {
                    "expr": "avg(github_actions_workflow_duration_seconds)"
                  }
                ]
              },
              {
                "id": 3,
                "title": "Error Rate by Service",
                "type": "table",
                "targets": [
                  {
                    "expr": "rate(application_errors_total[5m]) by (service)"
                  }
                ]
              }
            ]
          }
        }
EOF
        
        # Crea configurazione Prometheus
        cat << 'EOF' > dashboard/config/prometheus-rules.yml
        groups:
        - name: github-actions
          rules:
          - alert: HighErrorRate
            expr: rate(application_errors_total[5m]) > 0.1
            for: 2m
            labels:
              severity: critical
            annotations:
              summary: "High error rate detected"
              description: "Error rate is {{ $value }} errors per second"
          
          - alert: LongBuildTime
            expr: github_actions_workflow_duration_seconds > 600
            for: 5m
            labels:
              severity: warning
            annotations:
              summary: "Build taking too long"
              description: "Build has been running for {{ $value }} seconds"
EOF
        
        echo "📊 Dashboard configuration created"
    
    - name: Deploy Dashboard
      run: |
        echo "🚀 Deploying monitoring dashboard..."
        
        # Simula deploy del dashboard
        echo "Dashboard URL: ${{ needs.setup-monitoring.outputs.grafana-url }}"
        echo "Prometheus URL: ${{ needs.setup-monitoring.outputs.prometheus-url }}"
        
        # Log deployment
        cat << EOF > dashboard/deployment.log
        $(date -u +%Y-%m-%dT%H:%M:%SZ) - Dashboard deployment started
        $(date -u +%Y-%m-%dT%H:%M:%SZ) - Grafana configuration uploaded
        $(date -u +%Y-%m-%dT%H:%M:%SZ) - Prometheus rules updated
        $(date -u +%Y-%m-%dT%H:%M:%SZ) - Dashboard deployment completed
        $(date -u +%Y-%m-%dT%H:%M:%SZ) - Dashboard available at: ${{ needs.setup-monitoring.outputs.grafana-url }}
EOF
        
        echo "✅ Dashboard deployed successfully"
    
    - name: Upload Dashboard Artifacts
      uses: actions/upload-artifact@v4
      with:
        name: monitoring-dashboard-${{ needs.setup-monitoring.outputs.monitoring-id }}
        path: dashboard/
        retention-days: 30
```

## Struttura del Progetto

```
monitoring-project/
├── .github/
│   └── workflows/
│       └── monitoring-observability.yml
├── monitoring/
│   ├── config/
│   │   ├── prometheus.yml
│   │   ├── grafana-datasources.yml
│   │   └── alert-rules.yml
│   ├── scripts/
│   │   ├── health-check.sh
│   │   ├── log-parser.py
│   │   └── metric-collector.js
│   └── dashboards/
│       ├── overview.json
│       ├── performance.json
│       └── alerts.json
├── tests/
│   ├── load/
│   │   ├── api-load-test.yml
│   │   └── frontend-perf.js
│   └── monitoring/
│       ├── health-check.test.js
│       └── metrics.test.js
└── docs/
    ├── monitoring-setup.md
    ├── alert-playbook.md
    └── dashboard-guide.md
```

## File di Configurazione

### 1. Configurazione Prometheus

```yaml
# monitoring/config/prometheus.yml
global:
  scrape_interval: 15s
  evaluation_interval: 15s

rule_files:
  - "alert-rules.yml"

scrape_configs:
  - job_name: 'github-actions'
    static_configs:
      - targets: ['localhost:9090']
    metrics_path: /metrics
    scrape_interval: 30s

  - job_name: 'application'
    static_configs:
      - targets: ['app:3000']
    metrics_path: /api/metrics

alerting:
  alertmanagers:
    - static_configs:
        - targets:
          - alertmanager:9093
```

### 2. Script di Health Check

```bash
#!/bin/bash
# monitoring/scripts/health-check.sh

set -euo pipefail

ENDPOINTS=(
    "https://api.example.com/health"
    "https://api.example.com/version"
    "https://example.com"
)

check_endpoint() {
    local url=$1
    local start_time=$(date +%s.%N)
    
    if response=$(curl -s -o /dev/null -w "%{http_code}" "$url" --max-time 30); then
        local end_time=$(date +%s.%N)
        local duration=$(echo "$end_time - $start_time" | bc)
        
        if [ "$response" = "200" ]; then
            echo "✅ $url - OK (${duration}s)"
            return 0
        else
            echo "❌ $url - HTTP $response (${duration}s)"
            return 1
        fi
    else
        echo "❌ $url - Connection failed"
        return 1
    fi
}

main() {
    echo "🔍 Starting health checks..."
    local failed=0
    
    for endpoint in "${ENDPOINTS[@]}"; do
        if ! check_endpoint "$endpoint"; then
            failed=$((failed + 1))
        fi
    done
    
    if [ $failed -eq 0 ]; then
        echo "✅ All health checks passed"
        exit 0
    else
        echo "❌ $failed health checks failed"
        exit 1
    fi
}

main "$@"
```

### 3. Collector di Metriche

```javascript
// monitoring/scripts/metric-collector.js
const prometheus = require('prom-client');
const express = require('express');

// Crea registro per le metriche
const register = new prometheus.Registry();

// Metriche personalizzate
const httpRequestDuration = new prometheus.Histogram({
  name: 'http_request_duration_seconds',
  help: 'Duration of HTTP requests in seconds',
  labelNames: ['method', 'route', 'status'],
  buckets: [0.1, 0.5, 1, 2, 5]
});

const deploymentCounter = new prometheus.Counter({
  name: 'deployments_total',
  help: 'Total number of deployments',
  labelNames: ['environment', 'status']
});

const buildDuration = new prometheus.Gauge({
  name: 'build_duration_seconds',
  help: 'Duration of builds in seconds',
  labelNames: ['branch', 'workflow']
});

// Registra metriche
register.registerMetric(httpRequestDuration);
register.registerMetric(deploymentCounter);
register.registerMetric(buildDuration);

// Aggiungi metriche di default
prometheus.collectDefaultMetrics({ register });

// Setup Express server
const app = express();

app.get('/metrics', async (req, res) => {
  res.set('Content-Type', register.contentType);
  res.end(await register.metrics());
});

// Simula raccolta di metriche
setInterval(() => {
  // Simula richieste HTTP
  httpRequestDuration
    .labels('GET', '/api/users', '200')
    .observe(Math.random() * 2);
  
  // Simula deployment
  if (Math.random() > 0.95) {
    deploymentCounter
      .labels('production', 'success')
      .inc();
  }
  
  // Simula durata build
  buildDuration
    .labels('main', 'ci')
    .set(300 + Math.random() * 200);
}, 5000);

const PORT = process.env.PORT || 3001;
app.listen(PORT, () => {
  console.log(`📊 Metrics server running on port ${PORT}`);
});
```

## Test di Load

```yaml
# tests/load/api-load-test.yml
config:
  target: 'https://api.example.com'
  phases:
    - duration: 60
      arrivalRate: 5
      name: "Warm up"
    - duration: 120
      arrivalRate: 20
      name: "Normal load"
    - duration: 60
      arrivalRate: 50
      name: "Peak load"
  
scenarios:
  - name: "API Health Check"
    weight: 30
    flow:
      - get:
          url: "/health"
          expect:
            - statusCode: 200

  - name: "User Operations"
    weight: 50
    flow:
      - get:
          url: "/api/users"
          expect:
            - statusCode: 200
      - think: 2
      - post:
          url: "/api/users"
          json:
            name: "Test User"
            email: "test@example.com"

  - name: "Data Analytics"
    weight: 20
    flow:
      - get:
          url: "/api/analytics/dashboard"
          expect:
            - statusCode: 200
            - hasProperty: "metrics"
```

## Guida all'Uso

### 1. Setup Iniziale

```bash
# Clone del repository
git clone <repository-url>
cd monitoring-project

# Installa dipendenze
npm install

# Setup configurazione monitoring
cp monitoring/config/prometheus.yml.example monitoring/config/prometheus.yml
cp monitoring/config/grafana-datasources.yml.example monitoring/config/grafana-datasources.yml
```

### 2. Configurazione degli Alert

```yaml
# monitoring/config/alert-rules.yml
groups:
- name: application.rules
  rules:
  - alert: HighErrorRate
    expr: rate(http_requests_total{status=~"5.."}[5m]) > 0.1
    for: 2m
    labels:
      severity: critical
    annotations:
      summary: High error rate detected
      description: "Error rate is {{ $value }} per second"

  - alert: HighResponseTime
    expr: histogram_quantile(0.95, rate(http_request_duration_seconds_bucket[5m])) > 1
    for: 5m
    labels:
      severity: warning
    annotations:
      summary: High response time
      description: "95th percentile response time is {{ $value }}s"
```

### 3. Test del Sistema

```bash
# Esegui health checks
./monitoring/scripts/health-check.sh

# Avvia test di carico
artillery run tests/load/api-load-test.yml

# Test metriche
npm test -- tests/monitoring/
```

## Troubleshooting

### Problemi Comuni

1. **Metriche non visibili**
   - Verifica configurazione Prometheus
   - Controlla endpoint `/metrics`
   - Verifica network connectivity

2. **Alert non funzionanti**
   - Verifica sintassi PromQL
   - Controlla configurazione Alertmanager
   - Verifica webhook/notifiche

3. **Dashboard vuoti**
   - Verifica datasource Grafana
   - Controlla query delle metriche
   - Verifica retention dei dati

### Log di Debug

```bash
# Verifica log Prometheus
docker logs prometheus

# Verifica log Grafana
docker logs grafana

# Test connettività
curl -f http://localhost:9090/api/v1/query?query=up
```

## Risorse Aggiuntive

- [Prometheus Documentation](https://prometheus.io/docs/)
- [Grafana Dashboard Gallery](https://grafana.com/grafana/dashboards/)
- [GitHub Actions Monitoring Best Practices](https://docs.github.com/en/actions/monitoring-and-troubleshooting-workflows)
- [Observability Engineering](https://www.oreilly.com/library/view/observability-engineering/9781492076438/)

## Conclusioni

Questo esempio fornisce una base solida per implementare monitoring e observability completi in progetti enterprise. La combinazione di metriche, logging, health checks e alerting garantisce visibilità totale sullo stato del sistema e permette di identificare e risolvere problemi rapidamente.

L'integrazione con GitHub Actions automatizza completamente il processo di monitoring, rendendo il sistema self-healing e proattivo nella gestione dei problemi.
