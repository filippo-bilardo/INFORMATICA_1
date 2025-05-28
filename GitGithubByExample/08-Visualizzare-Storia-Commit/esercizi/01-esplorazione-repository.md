# Esercizio 01: Esplorazione Completa di un Repository

## Obiettivi dell'Esercizio
- Padroneggiare i comandi di base per esplorare la cronologia di Git
- Sviluppare competenze nell'analisi della struttura di un progetto
- Imparare a identificare pattern e trend di sviluppo
- Acquisire familiarità con la formattazione e personalizzazione dell'output

## Prerequisiti
- Conoscenza base dei comandi Git
- Comprensione dei concetti di commit, branch e repository
- Terminal/Command line basic skills

## Durata Stimata
45 minuti

---

## Scenario: Analisi di un Repository Open Source

Sei appena entrato in un team che mantiene una libreria JavaScript open source chiamata "DataViz Pro". Il repository ha una storia complessa con molti contributori e feature branch. Il tuo compito è esplorare e documentare la struttura del progetto per comprendere come è evoluto nel tempo.

### Setup dell'Ambiente

```bash
# Creiamo un repository di esempio con storia complessa
mkdir dataviz-exploration
cd dataviz-exploration
git init

# Configuriamo alcuni alias utili per l'esplorazione
git config alias.lg "log --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit"
git config alias.stats "log --stat --oneline"
git config alias.authors "shortlog -sn"
```

### Creazione della Storia del Repository

Prima di iniziare l'esplorazione, creiamo una storia realistica:

```bash
# Struttura iniziale del progetto
mkdir -p {src/{components,utils,charts},tests,docs,examples}

cat > README.md << 'EOF'
# DataViz Pro

A powerful JavaScript library for creating interactive data visualizations.

## Features
- Multiple chart types (bar, line, pie, scatter)
- Responsive design
- Animation support
- Plugin architecture
- TypeScript support

## Installation
```bash
npm install dataviz-pro
```

## Quick Start
```javascript
import { BarChart } from 'dataviz-pro';

const chart = new BarChart('#chart-container', {
  data: myData,
  width: 800,
  height: 400
});
```
EOF

cat > package.json << 'EOF'
{
  "name": "dataviz-pro",
  "version": "1.0.0",
  "description": "Interactive data visualization library",
  "main": "dist/index.js",
  "scripts": {
    "build": "webpack --mode production",
    "test": "jest",
    "dev": "webpack-dev-server",
    "lint": "eslint src/**/*.js"
  },
  "keywords": ["visualization", "charts", "d3", "svg"],
  "author": "DataViz Team",
  "license": "MIT"
}
EOF

cat > src/index.js << 'EOF'
// Main entry point for DataViz Pro
export { BarChart } from './charts/BarChart';
export { LineChart } from './charts/LineChart';
export { PieChart } from './charts/PieChart';
export { ScatterPlot } from './charts/ScatterPlot';

export { DataProcessor } from './utils/DataProcessor';
export { ColorPalette } from './utils/ColorPalette';
export { Animation } from './utils/Animation';

// Version info
export const VERSION = '1.0.0';
EOF

git add .
git commit -m "initial: create DataViz Pro library structure

- Set up basic project structure with src, tests, docs
- Add package.json with build scripts and dependencies
- Create main entry point with exports
- Add comprehensive README with usage examples"

# Simuliamo sviluppo di diverse features da parte di team diversi
git checkout -b feature/bar-charts
mkdir -p src/charts

cat > src/charts/BarChart.js << 'EOF'
import { BaseChart } from './BaseChart';
import { DataProcessor } from '../utils/DataProcessor';

export class BarChart extends BaseChart {
  constructor(selector, options = {}) {
    super(selector, options);
    this.type = 'bar';
    this.orientation = options.orientation || 'vertical';
    this.padding = options.padding || 0.1;
  }

  render() {
    const processedData = DataProcessor.normalize(this.data);
    this.setupSVG();
    this.createBars(processedData);
    this.addAxes();
    this.addInteractivity();
  }

  createBars(data) {
    const bars = this.svg.selectAll('.bar')
      .data(data)
      .enter()
      .append('rect')
      .attr('class', 'bar')
      .attr('x', (d, i) => this.xScale(i))
      .attr('y', d => this.yScale(d.value))
      .attr('width', this.xScale.bandwidth())
      .attr('height', d => this.height - this.yScale(d.value))
      .attr('fill', this.options.color || '#1976d2');

    return bars;
  }

  addInteractivity() {
    this.svg.selectAll('.bar')
      .on('mouseover', this.handleMouseOver.bind(this))
      .on('mouseout', this.handleMouseOut.bind(this))
      .on('click', this.handleClick.bind(this));
  }

  handleMouseOver(event, d) {
    // Tooltip logic here
    this.showTooltip(event, d);
  }

  handleMouseOut() {
    this.hideTooltip();
  }

  handleClick(event, d) {
    if (this.options.onClick) {
      this.options.onClick(d);
    }
  }
}
EOF

git add .
git commit -m "feat(charts): implement interactive bar chart component

- Add BarChart class with full interactivity
- Support for vertical and horizontal orientations
- Implement mouse events (hover, click)
- Add tooltip functionality
- Integrate with DataProcessor for data normalization
- Configurable styling and padding options"

cat > src/charts/BaseChart.js << 'EOF'
import * as d3 from 'd3';

export class BaseChart {
  constructor(selector, options = {}) {
    this.container = d3.select(selector);
    this.data = options.data || [];
    this.width = options.width || 800;
    this.height = options.height || 400;
    this.margin = options.margin || { top: 20, right: 20, bottom: 30, left: 40 };
    this.options = options;
    
    // Calculate inner dimensions
    this.innerWidth = this.width - this.margin.left - this.margin.right;
    this.innerHeight = this.height - this.margin.top - this.margin.bottom;
    
    this.setupScales();
  }

  setupSVG() {
    // Remove existing SVG if any
    this.container.select('svg').remove();
    
    this.svg = this.container
      .append('svg')
      .attr('width', this.width)
      .attr('height', this.height)
      .append('g')
      .attr('transform', `translate(${this.margin.left},${this.margin.top})`);
  }

  setupScales() {
    // Override in subclasses
    this.xScale = d3.scaleBand()
      .range([0, this.innerWidth])
      .padding(0.1);
      
    this.yScale = d3.scaleLinear()
      .range([this.innerHeight, 0]);
  }

  addAxes() {
    // X Axis
    this.svg.append('g')
      .attr('class', 'x-axis')
      .attr('transform', `translate(0,${this.innerHeight})`)
      .call(d3.axisBottom(this.xScale));

    // Y Axis
    this.svg.append('g')
      .attr('class', 'y-axis')
      .call(d3.axisLeft(this.yScale));
  }

  showTooltip(event, data) {
    // Tooltip implementation
    const tooltip = this.container.select('.tooltip').empty() 
      ? this.container.append('div').attr('class', 'tooltip')
      : this.container.select('.tooltip');
      
    tooltip
      .style('opacity', 1)
      .style('left', (event.pageX + 10) + 'px')
      .style('top', (event.pageY - 10) + 'px')
      .html(`Value: ${data.value}<br/>Label: ${data.label}`);
  }

  hideTooltip() {
    this.container.select('.tooltip').style('opacity', 0);
  }

  updateData(newData) {
    this.data = newData;
    this.render();
  }

  destroy() {
    this.container.select('svg').remove();
    this.container.select('.tooltip').remove();
  }
}
EOF

git add .
git commit -m "feat(core): add BaseChart class for chart inheritance

- Create reusable base class for all chart types
- Implement common functionality (SVG setup, scales, axes)
- Add tooltip system with positioning logic
- Provide data update and cleanup methods
- Set up responsive margin system
- Establish consistent API for all chart components"

# Sviluppo parallelo - LineChart
git checkout main
git checkout -b feature/line-charts

cat > src/charts/LineChart.js << 'EOF'
import { BaseChart } from './BaseChart';
import * as d3 from 'd3';

export class LineChart extends BaseChart {
  constructor(selector, options = {}) {
    super(selector, options);
    this.type = 'line';
    this.curved = options.curved !== false;
    this.showPoints = options.showPoints !== false;
    this.area = options.area || false;
  }

  setupScales() {
    this.xScale = d3.scaleTime()
      .range([0, this.innerWidth]);
      
    this.yScale = d3.scaleLinear()
      .range([this.innerHeight, 0]);
      
    // Update domains based on data
    if (this.data.length > 0) {
      this.xScale.domain(d3.extent(this.data, d => d.date));
      this.yScale.domain(d3.extent(this.data, d => d.value));
    }
  }

  render() {
    this.setupScales();
    this.setupSVG();
    this.createLine();
    if (this.area) this.createArea();
    if (this.showPoints) this.createPoints();
    this.addAxes();
    this.addInteractivity();
  }

  createLine() {
    const line = d3.line()
      .x(d => this.xScale(d.date))
      .y(d => this.yScale(d.value));
      
    if (this.curved) {
      line.curve(d3.curveCatmullRom);
    }

    this.svg.append('path')
      .datum(this.data)
      .attr('class', 'line')
      .attr('fill', 'none')
      .attr('stroke', this.options.color || '#1976d2')
      .attr('stroke-width', this.options.strokeWidth || 2)
      .attr('d', line);
  }

  createArea() {
    const area = d3.area()
      .x(d => this.xScale(d.date))
      .y0(this.innerHeight)
      .y1(d => this.yScale(d.value));
      
    if (this.curved) {
      area.curve(d3.curveCatmullRom);
    }

    this.svg.append('path')
      .datum(this.data)
      .attr('class', 'area')
      .attr('fill', this.options.areaColor || 'rgba(25, 118, 210, 0.2)')
      .attr('d', area);
  }

  createPoints() {
    this.svg.selectAll('.point')
      .data(this.data)
      .enter()
      .append('circle')
      .attr('class', 'point')
      .attr('cx', d => this.xScale(d.date))
      .attr('cy', d => this.yScale(d.value))
      .attr('r', this.options.pointRadius || 4)
      .attr('fill', this.options.pointColor || '#1976d2')
      .attr('stroke', '#fff')
      .attr('stroke-width', 2);
  }

  addInteractivity() {
    // Add hover line
    const hoverLine = this.svg.append('line')
      .attr('class', 'hover-line')
      .attr('stroke', '#999')
      .attr('stroke-width', 1)
      .attr('stroke-dasharray', '3,3')
      .style('opacity', 0);

    // Add invisible overlay for mouse tracking
    this.svg.append('rect')
      .attr('class', 'overlay')
      .attr('width', this.innerWidth)
      .attr('height', this.innerHeight)
      .attr('fill', 'none')
      .attr('pointer-events', 'all')
      .on('mouseover', () => hoverLine.style('opacity', 1))
      .on('mouseout', () => {
        hoverLine.style('opacity', 0);
        this.hideTooltip();
      })
      .on('mousemove', (event) => {
        const [mouseX] = d3.pointer(event);
        const x0 = this.xScale.invert(mouseX);
        const bisectDate = d3.bisector(d => d.date).left;
        const i = bisectDate(this.data, x0, 1);
        const d0 = this.data[i - 1];
        const d1 = this.data[i];
        const d = x0 - d0.date > d1.date - x0 ? d1 : d0;
        
        hoverLine
          .attr('x1', this.xScale(d.date))
          .attr('x2', this.xScale(d.date))
          .attr('y1', 0)
          .attr('y2', this.innerHeight);
          
        this.showTooltip(event, d);
      });
  }
}
EOF

git add .
git commit -m "feat(charts): implement LineChart with time series support

- Add LineChart class with time-based x-axis
- Support for curved and straight lines
- Optional area fill underneath line
- Interactive hover with vertical tracking line
- Configurable points display
- Mouse tracking with bisector for data point detection
- Smooth animations and responsive design"

# Continuiamo lo sviluppo delle utilities
cat > src/utils/DataProcessor.js << 'EOF'
export class DataProcessor {
  static normalize(data, options = {}) {
    if (!Array.isArray(data)) {
      throw new Error('Data must be an array');
    }

    const normalized = data.map((item, index) => {
      if (typeof item === 'number') {
        return { value: item, label: `Item ${index + 1}`, index };
      }
      
      if (typeof item === 'object' && item !== null) {
        return {
          value: item.value || item.y || 0,
          label: item.label || item.name || `Item ${index + 1}`,
          date: item.date ? new Date(item.date) : null,
          category: item.category || 'default',
          index,
          ...item
        };
      }
      
      return { value: 0, label: `Item ${index + 1}`, index };
    });

    // Apply sorting if requested
    if (options.sortBy) {
      normalized.sort((a, b) => {
        const aVal = a[options.sortBy];
        const bVal = b[options.sortBy];
        return options.sortOrder === 'desc' ? bVal - aVal : aVal - bVal;
      });
    }

    // Apply filtering if requested
    if (options.filter && typeof options.filter === 'function') {
      return normalized.filter(options.filter);
    }

    return normalized;
  }

  static aggregate(data, groupBy, aggregateBy = 'value', method = 'sum') {
    const groups = {};
    
    data.forEach(item => {
      const key = item[groupBy];
      if (!groups[key]) {
        groups[key] = [];
      }
      groups[key].push(item[aggregateBy]);
    });

    return Object.keys(groups).map(key => {
      let aggregatedValue;
      const values = groups[key];
      
      switch (method) {
        case 'sum':
          aggregatedValue = values.reduce((sum, val) => sum + val, 0);
          break;
        case 'average':
          aggregatedValue = values.reduce((sum, val) => sum + val, 0) / values.length;
          break;
        case 'max':
          aggregatedValue = Math.max(...values);
          break;
        case 'min':
          aggregatedValue = Math.min(...values);
          break;
        case 'count':
          aggregatedValue = values.length;
          break;
        default:
          aggregatedValue = values.reduce((sum, val) => sum + val, 0);
      }
      
      return {
        label: key,
        value: aggregatedValue,
        count: values.length
      };
    });
  }

  static generateTimeSeriesData(options = {}) {
    const {
      startDate = new Date('2023-01-01'),
      endDate = new Date(),
      interval = 'day',
      valueRange = [0, 100],
      trend = 'random'
    } = options;

    const data = [];
    const current = new Date(startDate);
    let previousValue = (valueRange[0] + valueRange[1]) / 2;

    while (current <= endDate) {
      let value;
      
      switch (trend) {
        case 'increasing':
          value = previousValue + Math.random() * 5;
          break;
        case 'decreasing':
          value = previousValue - Math.random() * 5;
          break;
        case 'seasonal':
          const dayOfYear = current.getDate();
          value = 50 + 30 * Math.sin(dayOfYear * 2 * Math.PI / 365) + Math.random() * 10;
          break;
        default:
          value = valueRange[0] + Math.random() * (valueRange[1] - valueRange[0]);
      }
      
      value = Math.max(valueRange[0], Math.min(valueRange[1], value));
      
      data.push({
        date: new Date(current),
        value: Math.round(value * 100) / 100
      });
      
      previousValue = value;
      
      // Increment date based on interval
      switch (interval) {
        case 'hour':
          current.setHours(current.getHours() + 1);
          break;
        case 'day':
          current.setDate(current.getDate() + 1);
          break;
        case 'week':
          current.setDate(current.getDate() + 7);
          break;
        case 'month':
          current.setMonth(current.getMonth() + 1);
          break;
      }
    }

    return data;
  }

  static validateData(data, schema) {
    const errors = [];
    
    if (!Array.isArray(data)) {
      errors.push('Data must be an array');
      return { valid: false, errors };
    }

    data.forEach((item, index) => {
      if (schema.required) {
        schema.required.forEach(field => {
          if (!(field in item)) {
            errors.push(`Missing required field '${field}' at index ${index}`);
          }
        });
      }

      if (schema.types) {
        Object.keys(schema.types).forEach(field => {
          if (field in item && typeof item[field] !== schema.types[field]) {
            errors.push(`Invalid type for field '${field}' at index ${index}. Expected ${schema.types[field]}, got ${typeof item[field]}`);
          }
        });
      }
    });

    return {
      valid: errors.length === 0,
      errors
    };
  }
}
EOF

git add .
git commit -m "feat(utils): add comprehensive DataProcessor utility

- Implement data normalization with flexible input formats
- Add aggregation methods (sum, average, max, min, count)
- Create time series data generation for testing
- Add data validation with schema support
- Support for sorting and filtering operations
- Generate realistic test data with trends
- Comprehensive error handling and validation"

# Merge della feature line-charts
git checkout main
git merge feature/line-charts -m "merge: integrate LineChart component and DataProcessor utilities

- Add advanced line chart with time series support
- Include comprehensive data processing utilities
- Support for curved lines, areas, and interactive hover
- Add data validation and aggregation capabilities"

# Merge della feature bar-charts
git merge feature/bar-charts -m "merge: integrate BarChart component with BaseChart architecture

- Add interactive bar chart implementation
- Establish BaseChart foundation for all chart types
- Include tooltip system and event handling
- Support for vertical and horizontal orientations"

# Aggiungiamo ulteriori feature per rendere la storia più interessante
git checkout -b feature/pie-charts

cat > src/charts/PieChart.js << 'EOF'
import { BaseChart } from './BaseChart';
import * as d3 from 'd3';

export class PieChart extends BaseChart {
  constructor(selector, options = {}) {
    super(selector, options);
    this.type = 'pie';
    this.innerRadius = options.innerRadius || 0;
    this.outerRadius = options.outerRadius || Math.min(this.innerWidth, this.innerHeight) / 2;
    this.showLabels = options.showLabels !== false;
    this.showLegend = options.showLegend !== false;
    this.cornerRadius = options.cornerRadius || 0;
  }

  render() {
    this.setupSVG();
    this.createPie();
    if (this.showLegend) this.createLegend();
    this.addInteractivity();
  }

  createPie() {
    const pie = d3.pie()
      .value(d => d.value)
      .sort(null);

    const arc = d3.arc()
      .innerRadius(this.innerRadius)
      .outerRadius(this.outerRadius)
      .cornerRadius(this.cornerRadius);

    const color = d3.scaleOrdinal(d3.schemeCategory10);

    const g = this.svg.append('g')
      .attr('transform', `translate(${this.innerWidth / 2}, ${this.innerHeight / 2})`);

    const arcs = g.selectAll('.arc')
      .data(pie(this.data))
      .enter()
      .append('g')
      .attr('class', 'arc');

    arcs.append('path')
      .attr('d', arc)
      .attr('fill', (d, i) => this.options.colors ? this.options.colors[i] : color(i))
      .attr('stroke', '#fff')
      .attr('stroke-width', 2);

    if (this.showLabels) {
      const labelArc = d3.arc()
        .innerRadius(this.outerRadius * 0.8)
        .outerRadius(this.outerRadius * 0.8);

      arcs.append('text')
        .attr('transform', d => `translate(${labelArc.centroid(d)})`)
        .attr('dy', '0.35em')
        .attr('text-anchor', 'middle')
        .style('font-size', '12px')
        .style('fill', '#333')
        .text(d => {
          const percent = ((d.endAngle - d.startAngle) / (2 * Math.PI) * 100).toFixed(1);
          return percent > 5 ? `${percent}%` : '';
        });
    }
  }

  createLegend() {
    const legend = this.svg.append('g')
      .attr('class', 'legend')
      .attr('transform', `translate(${this.innerWidth + 20}, 20)`);

    const legendItems = legend.selectAll('.legend-item')
      .data(this.data)
      .enter()
      .append('g')
      .attr('class', 'legend-item')
      .attr('transform', (d, i) => `translate(0, ${i * 20})`);

    legendItems.append('rect')
      .attr('width', 15)
      .attr('height', 15)
      .attr('fill', (d, i) => d3.schemeCategory10[i]);

    legendItems.append('text')
      .attr('x', 20)
      .attr('y', 12)
      .style('font-size', '12px')
      .text(d => d.label);
  }

  addInteractivity() {
    this.svg.selectAll('.arc path')
      .on('mouseover', function(event, d) {
        d3.select(this)
          .transition()
          .duration(200)
          .attr('transform', 'scale(1.05)');
      })
      .on('mouseout', function(event, d) {
        d3.select(this)
          .transition()
          .duration(200)
          .attr('transform', 'scale(1)');
      });
  }
}
EOF

git add .
git commit -m "feat(charts): implement PieChart with legend and animations

- Add PieChart class with donut chart support
- Implement percentage labels with visibility threshold
- Add interactive legend with color coding
- Include hover animations with scaling effects
- Support for custom colors and corner radius
- Configurable inner/outer radius for donut charts"

git checkout main
git merge feature/pie-charts -m "merge: add PieChart component with full interactivity

Integrate pie chart functionality with:
- Percentage-based labeling system
- Interactive legend component
- Hover animations and scaling
- Donut chart configuration options"

# Aggiungiamo tag per le release
git tag -a v1.0.0 -m "Release v1.0.0: Initial stable release

Features:
- BarChart with interactivity
- LineChart with time series support
- PieChart with animations
- BaseChart architecture
- DataProcessor utilities
- Comprehensive documentation"

# Aggiungiamo hotfix
git checkout -b hotfix/tooltip-position

cat > src/utils/TooltipManager.js << 'EOF'
export class TooltipManager {
  constructor(container) {
    this.container = container;
    this.tooltip = null;
    this.createTooltip();
  }

  createTooltip() {
    if (this.container.select('.dataviz-tooltip').empty()) {
      this.tooltip = this.container
        .append('div')
        .attr('class', 'dataviz-tooltip')
        .style('position', 'absolute')
        .style('background', 'rgba(0, 0, 0, 0.8)')
        .style('color', 'white')
        .style('padding', '8px 12px')
        .style('border-radius', '4px')
        .style('font-size', '12px')
        .style('pointer-events', 'none')
        .style('opacity', 0)
        .style('z-index', 1000);
    } else {
      this.tooltip = this.container.select('.dataviz-tooltip');
    }
  }

  show(event, content) {
    const containerRect = this.container.node().getBoundingClientRect();
    const tooltipRect = this.tooltip.node().getBoundingClientRect();
    
    let left = event.clientX - containerRect.left + 10;
    let top = event.clientY - containerRect.top - 10;
    
    // Prevent tooltip from going outside container
    if (left + tooltipRect.width > containerRect.width) {
      left = event.clientX - containerRect.left - tooltipRect.width - 10;
    }
    
    if (top < 0) {
      top = event.clientY - containerRect.top + 20;
    }
    
    this.tooltip
      .html(content)
      .style('left', left + 'px')
      .style('top', top + 'px')
      .transition()
      .duration(200)
      .style('opacity', 1);
  }

  hide() {
    this.tooltip
      .transition()
      .duration(200)
      .style('opacity', 0);
  }

  destroy() {
    if (this.tooltip) {
      this.tooltip.remove();
    }
  }
}
EOF

# Aggiorniamo BaseChart per usare il nuovo TooltipManager
cat > src/charts/BaseChart.js << 'EOF'
import * as d3 from 'd3';
import { TooltipManager } from '../utils/TooltipManager';

export class BaseChart {
  constructor(selector, options = {}) {
    this.container = d3.select(selector);
    this.data = options.data || [];
    this.width = options.width || 800;
    this.height = options.height || 400;
    this.margin = options.margin || { top: 20, right: 20, bottom: 30, left: 40 };
    this.options = options;
    
    // Calculate inner dimensions
    this.innerWidth = this.width - this.margin.left - this.margin.right;
    this.innerHeight = this.height - this.margin.top - this.margin.bottom;
    
    // Initialize tooltip manager
    this.tooltipManager = new TooltipManager(this.container);
    
    this.setupScales();
  }

  setupSVG() {
    // Remove existing SVG if any
    this.container.select('svg').remove();
    
    this.svg = this.container
      .append('svg')
      .attr('width', this.width)
      .attr('height', this.height)
      .append('g')
      .attr('transform', `translate(${this.margin.left},${this.margin.top})`);
  }

  setupScales() {
    // Override in subclasses
    this.xScale = d3.scaleBand()
      .range([0, this.innerWidth])
      .padding(0.1);
      
    this.yScale = d3.scaleLinear()
      .range([this.innerHeight, 0]);
  }

  addAxes() {
    // X Axis
    this.svg.append('g')
      .attr('class', 'x-axis')
      .attr('transform', `translate(0,${this.innerHeight})`)
      .call(d3.axisBottom(this.xScale));

    // Y Axis
    this.svg.append('g')
      .attr('class', 'y-axis')
      .call(d3.axisLeft(this.yScale));
  }

  showTooltip(event, data) {
    const content = this.formatTooltipContent(data);
    this.tooltipManager.show(event, content);
  }

  hideTooltip() {
    this.tooltipManager.hide();
  }

  formatTooltipContent(data) {
    // Override in subclasses for custom tooltip formatting
    return `Value: ${data.value}<br/>Label: ${data.label}`;
  }

  updateData(newData) {
    this.data = newData;
    this.render();
  }

  destroy() {
    this.container.select('svg').remove();
    this.tooltipManager.destroy();
  }
}
EOF

git add .
git commit -m "fix: improve tooltip positioning and management

- Add TooltipManager class for better tooltip handling
- Fix tooltip positioning to stay within container bounds
- Add smooth transitions for tooltip show/hide
- Improve tooltip styling with consistent design
- Fix edge cases where tooltip would render outside viewport
- Add proper cleanup in destroy method

Fixes #42: Tooltip positioning issues on small screens"

git checkout main
git merge hotfix/tooltip-position -m "hotfix: merge tooltip positioning improvements

Critical fixes for tooltip display issues:
- Prevent tooltips from rendering outside container
- Improve positioning logic for edge cases
- Add smooth animations for better UX"

git tag -a v1.0.1 -m "Release v1.0.1: Hotfix for tooltip positioning

Bug Fixes:
- Fixed tooltip positioning on small screens
- Improved tooltip boundary detection
- Enhanced tooltip animations"
```

---

## Parte 1: Esplorazione Base della Cronologia

### Compito 1.1: Analisi Generale del Repository

Utilizza i comandi di Git per rispondere alle seguenti domande:

**a) Quanti commit sono presenti nel repository?**
```bash
# Il tuo comando qui:


# Risposta attesa: ___ commit
```

**b) Chi sono i contributori principali e quanti commit ha fatto ciascuno?**
```bash
# Il tuo comando qui:


# Compila la tabella:
# Autore                | Numero di Commit
# _____________________|_________________
#                      |
#                      |
#                      |
```

**c) Qual è il range temporale di sviluppo del progetto?**
```bash
# Il tuo comando qui:


# Data primo commit: ________________
# Data ultimo commit: _______________
# Durata totale sviluppo: ___________
```

### Compito 1.2: Analisi dei Pattern di Commit

**a) Visualizza la storia del repository in formato grafico**
```bash
# Usa l'alias lg che abbiamo configurato o crea il tuo formato personalizzato:


# Disegna o descrivi la struttura dei branch che osservi:
```

**b) Identifica i merge commit**
```bash
# Il tuo comando per trovare solo i merge commit:


# Quanti merge commit ci sono? ___
# Elenca i messaggi dei merge commit:
# 1. _________________________________
# 2. _________________________________
# 3. _________________________________
```

**c) Trova tutti i commit di tipo "fix" o "hotfix"**
```bash
# Il tuo comando qui:


# Elenca i commit trovati:
# Hash      | Messaggio
# __________|_____________________
#           |
#           |
```

---

## Parte 2: Analisi Dettagliata dei File e Modifiche

### Compito 2.1: Statistiche sui File

**a) Trova i file più modificati nel repository**
```bash
# Il tuo comando qui:


# Top 5 file più modificati:
# 1. _________________ (__ modifiche)
# 2. _________________ (__ modifiche)
# 3. _________________ (__ modifiche)
# 4. _________________ (__ modifiche)
# 5. _________________ (__ modifiche)
```

**b) Analizza le statistiche dei commit**
```bash
# Comando per visualizzare statistiche dettagliate:


# Commit con più aggiunte di righe:
# Hash: _______ Righe aggiunte: ____ Descrizione: ________________

# Commit con più eliminazioni:
# Hash: _______ Righe eliminate: ____ Descrizione: ________________
```

### Compito 2.2: Evoluzione Specifica dei File

**a) Traccia l'evoluzione del file `src/index.js`**
```bash
# Comando per vedere la cronologia di un file specifico:


# Quante volte è stato modificato? ____
# Chi lo ha modificato di più? ____________________
```

**b) Confronta due versioni del file `package.json`**
```bash
# Comando per vedere le differenze tra il primo e ultimo commit:


# Descrivi le principali differenze osservate:
# 1. _________________________________________________
# 2. _________________________________________________
# 3. _________________________________________________
```

---

## Parte 3: Ricerca Avanzata nella Cronologia

### Compito 3.1: Ricerca per Contenuto

**a) Trova tutti i commit che hanno menzionato "tooltip"**
```bash
# Il tuo comando qui:


# Risultati trovati:
# Hash      | Data     | Autore   | Messaggio
# __________|__________|__________|___________________
#           |          |          |
```

**b) Cerca commit che hanno modificato codice contenente "d3.select"**
```bash
# Il tuo comando qui (usa git log -S o -G):


# Analizza il risultato: questi commit mostrano l'evoluzione di quale funzionalità?
# _________________________________________________________________
```

### Compito 3.2: Ricerca per Tempo e Autore

**a) Trova tutti i commit di oggi (se disponibili) o dell'ultima settimana**
```bash
# Il tuo comando qui:


# Numero di commit nell'ultimo periodo: ____
```

**b) Filtra i commit di un autore specifico per un file particolare**
```bash
# Esempio: commit del "DataViz Team" che hanno modificato file nella cartella charts/
# Il tuo comando qui:


# Descrivi il pattern di lavoro osservato:
# _________________________________________________________________
```

---

## Parte 4: Formattazione e Personalizzazione

### Compito 4.1: Creazione di Alias Personalizzati

Crea e testa i seguenti alias Git:

**a) Alias per visualizzazione compatta con statistiche**
```bash
# Crea un alias chiamato "summary" che mostri:
# - Hash abbreviato
# - Data relativa
# - Autore
# - Messaggio
# - Statistiche dei file modificati

git config alias.summary "___________________________________"

# Testa l'alias:
git summary -5

# Risultato:
```

**b) Alias per ricerca nei commit**
```bash
# Crea un alias chiamato "search" che permetta di cercare nei messaggi di commit:

git config alias.search "___________________________________"

# Testa con: git search "feat"
```

### Compito 4.2: Formato Personalizzato

**a) Crea un formato personalizzato per il log**
```bash
# Progetta un formato che includa:
# - Codice colore per tipo di commit (feat=verde, fix=rosso, etc.)
# - Emoji per rappresentare il tipo di modifica
# - Informazioni sull'autore e data

# Il tuo comando git log con format personalizzato:


# Risultato (disegna/descrivi l'output):
```

---

## Parte 5: Analisi di Tendenze e Pattern

### Compito 5.1: Analisi Temporale

**a) Analizza la frequenza dei commit nel tempo**
```bash
# Crea un comando che raggruppi i commit per giorno:


# Identifica il giorno più produttivo:
# Data: _____________ Numero di commit: ____
```

**b) Analizza i pattern dei messaggi di commit**
```bash
# Usa grep per identificare i tipi di commit più comuni:


# Statistiche dei tipi di commit:
# feat: ____ commit
# fix: ____ commit
# refactor: ____ commit
# docs: ____ commit
# Altri: ____ commit
```

### Compito 5.2: Analisi della Crescita del Codice

**a) Calcola la crescita totale delle righe di codice**
```bash
# Comando per vedere l'aggiunta/rimozione cumulativa:


# Crescita netta finale: 
# Righe aggiunte totali: ______
# Righe rimosse totali: ______
# Crescita netta: ______
```

**b) Identifica i commit che hanno cambiato la direzione del progetto**
```bash
# Cerca commit con messaggi che indicano cambiamenti importanti:
# (cerca termini come "breaking", "major", "rewrite", "refactor")


# Commit significativi identificati:
# 1. Hash: _______ Descrizione: _________________________
# 2. Hash: _______ Descrizione: _________________________
```

---

## Parte 6: Verifica e Validazione

### Compito 6.1: Verifica della Coerenza

**a) Controlla se ci sono commit orfani o problemi nella storia**
```bash
# Comando per verificare l'integrità del repository:


# Risultato della verifica: ________________________
```

**b) Analizza la qualità dei messaggi di commit**
```bash
# Trova commit con messaggi troppo brevi (meno di 10 caratteri):


# Trova commit senza descrizione dettagliata:


# Valutazione qualità messaggi: ___/10
```

### Compito 6.2: Documentazione dei Risultati

**Scrivi un breve report (200-300 parole) che riassuma:**

1. La struttura generale del progetto
2. I pattern di sviluppo osservati
3. I contributori principali e il loro stile
4. L'evoluzione delle funzionalità nel tempo
5. Raccomandazioni per migliorare il workflow

**Il tuo report:**

```
_________________________________________________________________
_________________________________________________________________
_________________________________________________________________
_________________________________________________________________
_________________________________________________________________
_________________________________________________________________
_________________________________________________________________
_________________________________________________________________
_________________________________________________________________
_________________________________________________________________
```

---

## Soluzioni di Riferimento

<details>
<summary>Clicca per vedere le soluzioni</summary>

### Compito 1.1 - Soluzioni

**a) Numero di commit:**
```bash
git rev-list --count HEAD
# oppure
git log --oneline | wc -l
```

**b) Contributori:**
```bash
git shortlog -sn
```

**c) Range temporale:**
```bash
git log --reverse --format="%ad" --date=short | head -1
git log --format="%ad" --date=short | head -1
```

### Compito 2.1 - Soluzioni

**a) File più modificati:**
```bash
git log --format=format: --name-only | egrep -v '^$' | sort | uniq -c | sort -rn | head -5
```

**b) Statistiche commit:**
```bash
git log --stat --format=fuller | grep -E "files? changed|insertions|deletions"
```

### Compito 3.1 - Soluzioni

**a) Ricerca tooltip:**
```bash
git log --grep="tooltip" --oneline
```

**b) Ricerca codice:**
```bash
git log -S "d3.select" --oneline
```

</details>

---

## Criteri di Valutazione

- **Correttezza dei comandi** (40%): I comandi utilizzati producono i risultati corretti
- **Completezza dell'analisi** (30%): Tutte le parti dell'esercizio sono completate
- **Qualità delle osservazioni** (20%): Le analisi mostrano comprensione dei pattern
- **Personalizzazione e creatività** (10%): Uso efficace di alias e formattazione personalizzata

---

**Navigazione:**
- [→ Prossimo Esercizio: Detective Git](02-detective-git.md)
- [← Torna agli Esempi](../esempi/04-cronologia-visuale.md)
- [↑ Torna all'Indice del Modulo](../README.md)
