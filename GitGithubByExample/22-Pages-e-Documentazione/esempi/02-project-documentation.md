# Esempio 2: Documentazione Completa di Progetto

## Obiettivo
Creare un sistema di documentazione completo per un progetto software utilizzando GitHub Pages, Markdown avanzato e strumenti di documentazione automatica.

## Scenario
Stai sviluppando "DevToolsKit", una libreria JavaScript per sviluppatori. Devi creare una documentazione completa che includa:
- API Reference automatica
- Guide per utenti e sviluppatori
- Tutorial interattivi
- Changelog automatico
- Esempi di codice funzionanti

## Struttura della Documentazione

### Repository Setup
```bash
devtoolskit/
├── docs/                    # Documentazione source
│   ├── _config.yml         # Configurazione Jekyll
│   ├── index.md            # Homepage documentazione
│   ├── getting-started.md  # Quick start guide
│   ├── api/                # API Documentation
│   │   ├── index.md
│   │   ├── core.md
│   │   ├── utils.md
│   │   └── plugins.md
│   ├── guides/             # User guides
│   │   ├── installation.md
│   │   ├── configuration.md
│   │   ├── advanced-usage.md
│   │   └── troubleshooting.md
│   ├── tutorials/          # Step-by-step tutorials
│   │   ├── basic-setup.md
│   │   ├── building-plugin.md
│   │   └── integration-examples.md
│   ├── examples/           # Code examples
│   │   ├── basic/
│   │   ├── advanced/
│   │   └── integrations/
│   ├── changelog/          # Version history
│   │   └── index.md
│   ├── _layouts/           # Jekyll layouts
│   │   ├── default.html
│   │   ├── docs.html
│   │   ├── api.html
│   │   └── example.html
│   ├── _includes/          # Reusable components
│   │   ├── nav.html
│   │   ├── sidebar.html
│   │   ├── code-example.html
│   │   └── api-method.html
│   ├── assets/             # Static assets
│   │   ├── css/
│   │   ├── js/
│   │   └── images/
│   └── _data/              # Data files
│       ├── navigation.yml
│       ├── api.yml
│       └── versions.yml
├── src/                    # Source code
├── examples/               # Runnable examples
├── scripts/                # Build scripts
│   ├── generate-docs.js    # Auto-generate API docs
│   ├── update-changelog.js # Auto-update changelog
│   └── deploy-docs.sh      # Deploy script
└── package.json
```

## Implementazione Completa

### 1. Configurazione Jekyll Avanzata (`docs/_config.yml`)

```yaml
# Site settings
title: "DevToolsKit Documentation"
description: "Complete documentation for DevToolsKit - The ultimate JavaScript developer toolkit"
baseurl: "/devtoolskit"
url: "https://yourorg.github.io"

# Repository info
repository: "yourorg/devtoolskit"
edit_page: true

# Jekyll settings
markdown: kramdown
highlighter: rouge
kramdown:
  input: GFM
  syntax_highlighter: rouge
  syntax_highlighter_opts:
    block:
      line_numbers: true

# Plugins
plugins:
  - jekyll-feed
  - jekyll-sitemap
  - jekyll-seo-tag
  - jekyll-toc
  - jekyll-relative-links
  - jekyll-optional-front-matter
  - jekyll-readme-index
  - jekyll-default-layout

# Collections
collections:
  api:
    output: true
    permalink: /:collection/:name/
  guides:
    output: true
    permalink: /:collection/:name/
  tutorials:
    output: true
    permalink: /:collection/:name/
  examples:
    output: true
    permalink: /:collection/:name/

# Defaults
defaults:
  - scope:
      path: ""
      type: "pages"
    values:
      layout: "docs"
  - scope:
      path: "api"
      type: "api"
    values:
      layout: "api"
      toc: true
  - scope:
      path: "guides"
      type: "guides"
    values:
      layout: "docs"
      toc: true
  - scope:
      path: "tutorials"
      type: "tutorials"
    values:
      layout: "docs"
      toc: true
  - scope:
      path: "examples"
      type: "examples"
    values:
      layout: "example"

# Navigation
nav_primary:
  - title: "Getting Started"
    url: "/getting-started"
  - title: "API Reference"
    url: "/api/"
    children:
      - title: "Core"
        url: "/api/core"
      - title: "Utils"
        url: "/api/utils"
      - title: "Plugins"
        url: "/api/plugins"
  - title: "Guides"
    url: "/guides/"
    children:
      - title: "Installation"
        url: "/guides/installation"
      - title: "Configuration"
        url: "/guides/configuration"
      - title: "Advanced Usage"
        url: "/guides/advanced-usage"
      - title: "Troubleshooting"
        url: "/guides/troubleshooting"
  - title: "Tutorials"
    url: "/tutorials/"
  - title: "Examples"
    url: "/examples/"
  - title: "Changelog"
    url: "/changelog/"

# Search
search:
  enabled: true
  url: "/search.json"

# Code highlighting
code_themes:
  light: "github"
  dark: "github-dark"

# Social links
github_repo: "https://github.com/yourorg/devtoolskit"
npm_package: "https://www.npmjs.com/package/devtoolskit"
```

### 2. Layout per Documentazione (`docs/_layouts/docs.html`)

```html
---
layout: default
---

<div class="docs-container">
  <!-- Sidebar Navigation -->
  <nav class="docs-sidebar">
    <div class="sidebar-header">
      <h2><a href="{{ '/' | relative_url }}">{{ site.title }}</a></h2>
      <div class="version-selector">
        <select id="version-select">
          {% for version in site.data.versions %}
          <option value="{{ version.number }}" 
                  {% if version.current %}selected{% endif %}>
            v{{ version.number }}
          </option>
          {% endfor %}
        </select>
      </div>
    </div>
    
    <div class="sidebar-search">
      <input type="search" 
             id="docs-search" 
             placeholder="Search documentation..."
             autocomplete="off">
      <div id="search-results"></div>
    </div>
    
    {% include nav.html nav=site.nav_primary %}
  </nav>
  
  <!-- Main Content -->
  <main class="docs-main">
    <div class="docs-content">
      <!-- Breadcrumb -->
      <nav class="breadcrumb">
        <ol>
          <li><a href="{{ '/' | relative_url }}">Home</a></li>
          {% assign parts = page.url | split: '/' %}
          {% assign breadcrumb_url = '' %}
          {% for part in parts %}
            {% if part != '' %}
              {% assign breadcrumb_url = breadcrumb_url | append: '/' | append: part %}
              <li>
                {% if forloop.last %}
                  {{ page.title | default: part | capitalize }}
                {% else %}
                  <a href="{{ breadcrumb_url }}">{{ part | capitalize }}</a>
                {% endif %}
              </li>
            {% endif %}
          {% endfor %}
        </ol>
      </nav>
      
      <!-- Page Header -->
      <header class="page-header">
        <h1>{{ page.title }}</h1>
        {% if page.description %}
        <p class="page-description">{{ page.description }}</p>
        {% endif %}
        
        <!-- Page Meta -->
        <div class="page-meta">
          {% if page.version %}
          <span class="meta-item">
            <i class="icon-tag"></i>
            Version {{ page.version }}
          </span>
          {% endif %}
          
          {% if page.last_modified_at %}
          <span class="meta-item">
            <i class="icon-clock"></i>
            Updated {{ page.last_modified_at | date: "%B %d, %Y" }}
          </span>
          {% endif %}
          
          {% if site.edit_page and page.path %}
          <a href="{{ site.repository }}/edit/main/{{ page.path }}" 
             class="meta-item edit-link"
             target="_blank">
            <i class="icon-edit"></i>
            Edit this page
          </a>
          {% endif %}
        </div>
      </header>
      
      <!-- Table of Contents -->
      {% if page.toc %}
      <div class="toc-container">
        <details class="toc" open>
          <summary>Table of Contents</summary>
          {{ content | toc }}
        </details>
      </div>
      {% endif %}
      
      <!-- Main Content -->
      <div class="content">
        {{ content }}
      </div>
      
      <!-- Page Footer -->
      <footer class="page-footer">
        <div class="footer-nav">
          {% if page.previous %}
          <a href="{{ page.previous.url | relative_url }}" class="prev-page">
            <i class="icon-arrow-left"></i>
            <div>
              <span class="nav-label">Previous</span>
              <span class="nav-title">{{ page.previous.title }}</span>
            </div>
          </a>
          {% endif %}
          
          {% if page.next %}
          <a href="{{ page.next.url | relative_url }}" class="next-page">
            <div>
              <span class="nav-label">Next</span>
              <span class="nav-title">{{ page.next.title }}</span>
            </div>
            <i class="icon-arrow-right"></i>
          </a>
          {% endif %}
        </div>
        
        <div class="footer-feedback">
          <h4>Was this page helpful?</h4>
          <div class="feedback-buttons">
            <button class="feedback-btn" data-feedback="yes">
              <i class="icon-thumbs-up"></i>
              Yes
            </button>
            <button class="feedback-btn" data-feedback="no">
              <i class="icon-thumbs-down"></i>
              No
            </button>
          </div>
        </div>
      </footer>
    </div>
    
    <!-- Right Sidebar (TOC on desktop) -->
    {% if page.toc %}
    <aside class="docs-toc">
      <div class="toc-content">
        <h4>On this page</h4>
        {{ content | toc }}
      </div>
    </aside>
    {% endif %}
  </main>
</div>

<!-- Scripts -->
<script src="{{ '/assets/js/docs.js' | relative_url }}"></script>
<script>
document.addEventListener('DOMContentLoaded', function() {
  // Initialize search functionality
  initializeSearch();
  
  // Initialize feedback system
  initializeFeedback();
  
  // Initialize code examples
  initializeCodeExamples();
  
  // Initialize version selector
  initializeVersionSelector();
});
</script>
```

### 3. Homepage Documentazione (`docs/index.md`)

```markdown
---
layout: docs
title: "DevToolsKit Documentation"
description: "The ultimate JavaScript developer toolkit - Comprehensive documentation and guides"
---

# Welcome to DevToolsKit

DevToolsKit is a comprehensive JavaScript library that provides essential tools and utilities for modern web development. Whether you're building a simple website or a complex application, DevToolsKit has the tools you need.

## Quick Start

Get started with DevToolsKit in just a few minutes:

```bash
# Install via npm
npm install devtoolskit

# Install via yarn
yarn add devtoolskit
```

```javascript
// ES6 import
import { createApp, utils } from 'devtoolskit';

// CommonJS
const { createApp, utils } = require('devtoolskit');

// Basic usage
const app = createApp({
  target: '#app',
  plugins: ['router', 'state']
});
```

<div class="getting-started-grid">
  <div class="card">
    <h3>🚀 Getting Started</h3>
    <p>Learn the basics and set up your first project with DevToolsKit.</p>
    <a href="{{ '/getting-started' | relative_url }}" class="btn btn-primary">Start Here</a>
  </div>
  
  <div class="card">
    <h3>📚 API Reference</h3>
    <p>Complete API documentation with examples and usage patterns.</p>
    <a href="{{ '/api/' | relative_url }}" class="btn btn-outline">Browse API</a>
  </div>
  
  <div class="card">
    <h3>🎯 Tutorials</h3>
    <p>Step-by-step tutorials for common use cases and advanced features.</p>
    <a href="{{ '/tutorials/' | relative_url }}" class="btn btn-outline">View Tutorials</a>
  </div>
  
  <div class="card">
    <h3>🔧 Examples</h3>
    <p>Ready-to-use code examples and integration patterns.</p>
    <a href="{{ '/examples/' | relative_url }}" class="btn btn-outline">See Examples</a>
  </div>
</div>

## Key Features

<div class="features-grid">
  <div class="feature">
    <div class="feature-icon">⚡</div>
    <h3>Performance Optimized</h3>
    <p>Built with performance in mind, DevToolsKit provides lightning-fast execution with minimal overhead.</p>
  </div>
  
  <div class="feature">
    <div class="feature-icon">🔧</div>
    <h3>Modular Architecture</h3>
    <p>Use only what you need. Our modular design allows you to import specific functionality.</p>
  </div>
  
  <div class="feature">
    <div class="feature-icon">📱</div>
    <h3>Cross-Platform</h3>
    <p>Works seamlessly across all modern browsers and Node.js environments.</p>
  </div>
  
  <div class="feature">
    <div class="feature-icon">🛡️</div>
    <h3>Type Safe</h3>
    <p>Full TypeScript support with comprehensive type definitions included.</p>
  </div>
  
  <div class="feature">
    <div class="feature-icon">🧪</div>
    <h3>Well Tested</h3>
    <p>Extensive test coverage ensures reliability and stability in production.</p>
  </div>
  
  <div class="feature">
    <div class="feature-icon">📖</div>
    <h3>Great Documentation</h3>
    <p>Comprehensive documentation with examples, guides, and tutorials.</p>
  </div>
</div>

## Installation Options

### Package Managers

```bash
# npm
npm install devtoolskit

# Yarn
yarn add devtoolskit

# pnpm
pnpm add devtoolskit
```

### CDN

```html
<!-- Latest version -->
<script src="https://cdn.jsdelivr.net/npm/devtoolskit@latest/dist/devtoolskit.min.js"></script>

<!-- Specific version -->
<script src="https://cdn.jsdelivr.net/npm/devtoolskit@2.1.0/dist/devtoolskit.min.js"></script>

<!-- ES Modules -->
<script type="module">
  import { createApp } from 'https://cdn.skypack.dev/devtoolskit';
</script>
```

### Download

Download the latest release directly from GitHub:

<a href="https://github.com/yourorg/devtoolskit/releases/latest" class="btn btn-primary">
  <i class="icon-download"></i>
  Download Latest Release
</a>

## Basic Example

Here's a simple example to get you started:

```html
<!DOCTYPE html>
<html>
<head>
    <title>DevToolsKit Example</title>
</head>
<body>
    <div id="app">
        <h1>Hello, DevToolsKit!</h1>
        <button id="btn">Click me</button>
        <div id="output"></div>
    </div>

    <script src="https://cdn.jsdelivr.net/npm/devtoolskit@latest/dist/devtoolskit.min.js"></script>
    <script>
        const { createApp, utils } = DevToolsKit;
        
        const app = createApp({
            target: '#app',
            state: {
                count: 0
            },
            methods: {
                increment() {
                    this.state.count++;
                    this.render();
                },
                render() {
                    document.getElementById('output').textContent = 
                        `Count: ${this.state.count}`;
                }
            }
        });
        
        document.getElementById('btn').addEventListener('click', () => {
            app.increment();
        });
    </script>
</body>
</html>
```

<div class="example-demo">
  <h4>Try it yourself:</h4>
  <iframe src="{{ '/examples/basic-counter/' | relative_url }}" 
          width="100%" 
          height="200" 
          frameborder="0">
  </iframe>
  <p><a href="{{ '/examples/basic-counter/' | relative_url }}" target="_blank">View full example</a></p>
</div>

## What's New

### Version 2.1.0 (Latest)

- ✨ **New Plugin System**: Enhanced plugin architecture with lifecycle hooks
- 🚀 **Performance Improvements**: 40% faster rendering and state management
- 🛡️ **Security Updates**: Enhanced XSS protection and input validation
- 📱 **Mobile Optimizations**: Better touch support and gesture handling
- 🔧 **Developer Experience**: Improved debugging tools and error messages

[View full changelog]({{ '/changelog/' | relative_url }})

## Community & Support

<div class="community-grid">
  <div class="community-item">
    <h4>🐛 Bug Reports</h4>
    <p>Found a bug? Report it on GitHub Issues.</p>
    <a href="https://github.com/yourorg/devtoolskit/issues">Report Bug</a>
  </div>
  
  <div class="community-item">
    <h4>💡 Feature Requests</h4>
    <p>Have an idea? We'd love to hear about it!</p>
    <a href="https://github.com/yourorg/devtoolskit/discussions">Request Feature</a>
  </div>
  
  <div class="community-item">
    <h4>💬 Discussions</h4>
    <p>Join the community discussions on GitHub.</p>
    <a href="https://github.com/yourorg/devtoolskit/discussions">Join Discussion</a>
  </div>
  
  <div class="community-item">
    <h4>📧 Newsletter</h4>
    <p>Stay updated with the latest news and releases.</p>
    <a href="/newsletter">Subscribe</a>
  </div>
</div>

## Contributing

We welcome contributions from the community! Here's how you can help:

- 🐛 **Report bugs** and submit feature requests
- 📝 **Improve documentation** and write tutorials
- 🔧 **Submit pull requests** with bug fixes and new features
- 🧪 **Write tests** and improve code coverage
- 🎨 **Design** and UX improvements

[Read our Contributing Guide](https://github.com/yourorg/devtoolskit/blob/main/CONTRIBUTING.md)

## License

DevToolsKit is [MIT licensed](https://github.com/yourorg/devtoolskit/blob/main/LICENSE).
```

### 4. API Documentation Automatica

**Script per Generazione API** (`scripts/generate-docs.js`):

```javascript
#!/usr/bin/env node
/**
 * Auto-generate API documentation from JSDoc comments
 */

const fs = require('fs');
const path = require('path');
const jsdoc2md = require('jsdoc-to-markdown');
const glob = require('glob');

class APIDocGenerator {
  constructor(config = {}) {
    this.config = {
      srcDir: config.srcDir || 'src',
      docsDir: config.docsDir || 'docs/api',
      templateDir: config.templateDir || 'docs/_templates',
      ...config
    };
  }

  async generateDocs() {
    console.log('🔧 Generating API documentation...');
    
    // Find all source files
    const sourceFiles = glob.sync(`${this.config.srcDir}/**/*.js`);
    
    // Group files by module
    const modules = this.groupFilesByModule(sourceFiles);
    
    // Generate docs for each module
    for (const [moduleName, files] of Object.entries(modules)) {
      await this.generateModuleDocs(moduleName, files);
    }
    
    // Generate index page
    await this.generateIndexPage(Object.keys(modules));
    
    console.log('✅ API documentation generated successfully!');
  }

  groupFilesByModule(files) {
    const modules = {};
    
    files.forEach(file => {
      const relativePath = path.relative(this.config.srcDir, file);
      const moduleName = this.getModuleName(relativePath);
      
      if (!modules[moduleName]) {
        modules[moduleName] = [];
      }
      modules[moduleName].push(file);
    });
    
    return modules;
  }

  getModuleName(filePath) {
    const parts = filePath.split(path.sep);
    if (parts.length > 1) {
      return parts[0]; // Use directory name as module name
    }
    return 'core'; // Default module
  }

  async generateModuleDocs(moduleName, files) {
    console.log(`📝 Generating docs for module: ${moduleName}`);
    
    try {
      // Extract JSDoc data
      const templateData = await jsdoc2md.getTemplateData({
        files: files,
        configure: '.jsdocrc.json'
      });
      
      // Filter by module
      const moduleData = templateData.filter(item => 
        !item.ignore && (item.memberof === moduleName || !item.memberof)
      );
      
      // Generate markdown content
      const content = await this.renderModuleTemplate(moduleName, moduleData);
      
      // Write to file
      const outputPath = path.join(this.config.docsDir, `${moduleName}.md`);
      fs.writeFileSync(outputPath, content);
      
      console.log(`   ✅ Generated: ${outputPath}`);
    } catch (error) {
      console.error(`   ❌ Error generating ${moduleName}:`, error.message);
    }
  }

  async renderModuleTemplate(moduleName, data) {
    const template = fs.readFileSync(
      path.join(this.config.templateDir, 'module.hbs'),
      'utf8'
    );
    
    // Organize data by kind
    const organized = {
      classes: data.filter(item => item.kind === 'class'),
      functions: data.filter(item => item.kind === 'function'),
      constants: data.filter(item => item.kind === 'constant'),
      typedefs: data.filter(item => item.kind === 'typedef')
    };
    
    // Render with Handlebars
    const Handlebars = require('handlebars');
    
    // Register helpers
    this.registerHandlebarsHelpers(Handlebars);
    
    const compiledTemplate = Handlebars.compile(template);
    
    return compiledTemplate({
      moduleName,
      ...organized,
      generatedAt: new Date().toISOString()
    });
  }

  registerHandlebarsHelpers(Handlebars) {
    // Helper for code syntax highlighting
    Handlebars.registerHelper('code', function(language, code) {
      return `\`\`\`${language}\n${code}\n\`\`\``;
    });
    
    // Helper for parameter formatting
    Handlebars.registerHelper('formatParams', function(params) {
      if (!params || !params.length) return '';
      
      return params.map(param => {
        const optional = param.optional ? '?' : '';
        const type = param.type ? ` {${param.type.names.join('|')}}` : '';
        return `${param.name}${optional}${type}`;
      }).join(', ');
    });
    
    // Helper for return type formatting
    Handlebars.registerHelper('formatReturns', function(returns) {
      if (!returns || !returns.length) return 'void';
      
      const ret = returns[0];
      return ret.type ? ret.type.names.join('|') : 'any';
    });
    
    // Helper for example formatting
    Handlebars.registerHelper('formatExample', function(examples) {
      if (!examples || !examples.length) return '';
      
      return examples.map(example => {
        return `\`\`\`javascript\n${example}\n\`\`\``;
      }).join('\n\n');
    });
  }

  async generateIndexPage(modules) {
    const indexTemplate = `---
layout: docs
title: "API Reference"
description: "Complete API documentation for DevToolsKit"
toc: true
---

# API Reference

This section contains the complete API documentation for DevToolsKit, automatically generated from source code comments.

## Modules

${modules.map(module => `
### [${module.charAt(0).toUpperCase() + module.slice(1)}]({{ '/api/${module}' | relative_url }})

Documentation for the ${module} module.
`).join('')}

## Quick Reference

### Core Functions

\`\`\`javascript
import { createApp, mount, unmount } from 'devtoolskit';

// Create new app instance
const app = createApp(options);

// Mount app to DOM element
mount(app, '#app');

// Unmount app
unmount(app);
\`\`\`

### Utility Functions

\`\`\`javascript
import { utils } from 'devtoolskit';

// Deep clone object
const cloned = utils.deepClone(original);

// Debounce function
const debounced = utils.debounce(fn, 300);

// Format date
const formatted = utils.formatDate(date, 'YYYY-MM-DD');
\`\`\`

### Plugin System

\`\`\`javascript
import { plugin } from 'devtoolskit';

// Register plugin
plugin.register('myPlugin', {
  install(app, options) {
    // Plugin logic
  }
});

// Use plugin
app.use('myPlugin', { option: 'value' });
\`\`\`

---

*Documentation generated on: ${new Date().toLocaleDateString()}*
`;

    const indexPath = path.join(this.config.docsDir, 'index.md');
    fs.writeFileSync(indexPath, indexTemplate);
    console.log(`📄 Generated API index: ${indexPath}`);
  }
}

// Template per modulo (`docs/_templates/module.hbs`)
const moduleTemplate = `---
layout: api
title: "{{ moduleName }} Module"
description: "API documentation for the {{ moduleName }} module"
module: "{{ moduleName }}"
toc: true
generated_at: "{{ generatedAt }}"
---

# {{ moduleName }} Module

{{#if classes}}
## Classes

{{#each classes}}
### {{ name }}

{{ description }}

{{#if params}}
#### Constructor Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
{{#each params}}
| \`{{ name }}\`{{#if optional}} *(optional)*{{/if}} | \`{{ type.names }}\` | {{ description }} |
{{/each}}
{{/if}}

{{#if examples}}
#### Example

{{{ formatExample examples }}}
{{/if}}

{{#if members}}
#### Methods

{{#each members}}
{{#if (eq kind 'function')}}
##### {{ name }}({{ formatParams params }}) → {{{ formatReturns returns }}}

{{ description }}

{{#if params}}
**Parameters:**

{{#each params}}
- \`{{ name }}\`{{#if optional}} *(optional)*{{/if}} {{{ type.names }}} - {{ description }}
{{/each}}
{{/if}}

{{#if returns}}
**Returns:** {{{ formatReturns returns }}} - {{ returns.0.description }}
{{/if}}

{{#if examples}}
**Example:**

{{{ formatExample examples }}}
{{/if}}

{{/if}}
{{/each}}
{{/if}}

---

{{/each}}
{{/if}}

{{#if functions}}
## Functions

{{#each functions}}
### {{ name }}({{ formatParams params }}) → {{{ formatReturns returns }}}

{{ description }}

{{#if params}}
#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
{{#each params}}
| \`{{ name }}\`{{#if optional}} *(optional)*{{/if}} | \`{{ type.names }}\` | {{ description }} |
{{/each}}
{{/if}}

{{#if returns}}
#### Returns

{{{ formatReturns returns }}} - {{ returns.0.description }}
{{/if}}

{{#if examples}}
#### Example

{{{ formatExample examples }}}
{{/if}}

{{#if see}}
#### See Also

{{#each see}}
- {{ this }}
{{/each}}
{{/if}}

---

{{/each}}
{{/if}}

{{#if constants}}
## Constants

{{#each constants}}
### {{ name }}

{{ description }}

**Type:** \`{{ type.names }}\`  
**Value:** \`{{ meta.code.value }}\`

{{#if examples}}
#### Example

{{{ formatExample examples }}}
{{/if}}

---

{{/each}}
{{/if}}

{{#if typedefs}}
## Type Definitions

{{#each typedefs}}
### {{ name }}

{{ description }}

{{#if properties}}
#### Properties

| Property | Type | Description |
|----------|------|-------------|
{{#each properties}}
| \`{{ name }}\`{{#if optional}} *(optional)*{{/if}} | \`{{ type.names }}\` | {{ description }} |
{{/each}}
{{/if}}

{{#if examples}}
#### Example

{{{ formatExample examples }}}
{{/if}}

---

{{/each}}
{{/if}}

---

*Generated automatically from source code on {{ generatedAt }}*
`;

// Configuration JSDoc (`.jsdocrc.json`)
const jsdocConfig = {
  "source": {
    "include": ["./src"],
    "includePattern": "\\.(js|jsx)$",
    "exclude": ["node_modules/", "dist/", "build/"]
  },
  "opts": {
    "recurse": true
  },
  "plugins": [
    "plugins/markdown"
  ]
};

// CLI Usage
if (require.main === module) {
  const generator = new APIDocGenerator({
    srcDir: process.argv[2] || 'src',
    docsDir: process.argv[3] || 'docs/api'
  });
  
  generator.generateDocs().catch(console.error);
}

module.exports = APIDocGenerator;
```

### 5. Sistema di Versioning

**Script Changelog** (`scripts/update-changelog.js`):

```javascript
#!/usr/bin/env node
/**
 * Auto-generate changelog from git commits and releases
 */

const { execSync } = require('child_process');
const fs = require('fs');
const path = require('path');

class ChangelogGenerator {
  constructor(options = {}) {
    this.options = {
      outputFile: options.outputFile || 'docs/changelog/index.md',
      repoUrl: options.repoUrl || this.getRepoUrl(),
      conventionalCommits: options.conventionalCommits !== false,
      ...options
    };
  }

  getRepoUrl() {
    try {
      const remote = execSync('git remote get-url origin', { encoding: 'utf8' }).trim();
      return remote.replace(/\.git$/, '');
    } catch {
      return 'https://github.com/yourorg/devtoolskit';
    }
  }

  async generateChangelog() {
    console.log('📝 Generating changelog...');
    
    // Get all tags (releases)
    const tags = this.getTags();
    
    // Generate changelog content
    const changelog = await this.buildChangelog(tags);
    
    // Write to file
    fs.writeFileSync(this.options.outputFile, changelog);
    
    console.log(`✅ Changelog generated: ${this.options.outputFile}`);
  }

  getTags() {
    try {
      const output = execSync('git tag -l --sort=-version:refname', { encoding: 'utf8' });
      return output.trim().split('\n').filter(tag => tag.startsWith('v'));
    } catch {
      return [];
    }
  }

  async buildChangelog(tags) {
    const header = `---
layout: docs
title: "Changelog"
description: "Release history and changes for DevToolsKit"
toc: true
---

# Changelog

All notable changes to DevToolsKit will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

`;

    let content = header;
    
    for (let i = 0; i < tags.length; i++) {
      const currentTag = tags[i];
      const previousTag = tags[i + 1];
      
      const release = await this.buildReleaseSection(currentTag, previousTag);
      content += release + '\n';
    }
    
    // Add unreleased section
    if (tags.length > 0) {
      const unreleased = await this.buildReleaseSection('HEAD', tags[0], 'Unreleased');
      if (unreleased.trim()) {
        content = header + unreleased + '\n' + content.substring(header.length);
      }
    }
    
    return content;
  }

  async buildReleaseSection(currentRef, previousRef, title = null) {
    const versionTitle = title || currentRef;
    const releaseDate = this.getReleaseDate(currentRef);
    
    // Get commits between refs
    const commits = this.getCommitsBetween(currentRef, previousRef);
    
    if (!commits.length && !title) {
      return '';
    }
    
    let section = `## [${versionTitle}]`;
    
    if (currentRef !== 'HEAD') {
      section += `(${this.options.repoUrl}/releases/tag/${currentRef})`;
    }
    
    if (releaseDate) {
      section += ` - ${releaseDate}`;
    }
    
    section += '\n\n';
    
    if (!commits.length) {
      section += '*No changes*\n\n';
      return section;
    }
    
    // Categorize commits
    const categories = this.categorizeCommits(commits);
    
    // Add sections for each category
    const categoryOrder = ['breaking', 'added', 'changed', 'deprecated', 'removed', 'fixed', 'security'];
    
    for (const category of categoryOrder) {
      if (categories[category] && categories[category].length > 0) {
        section += `### ${this.getCategoryTitle(category)}\n\n`;
        
        for (const commit of categories[category]) {
          const commitLink = `[${commit.hash.substring(0, 7)}](${this.options.repoUrl}/commit/${commit.hash})`;
          section += `- ${commit.message} (${commitLink})\n`;
        }
        
        section += '\n';
      }
    }
    
    return section;
  }

  getReleaseDate(ref) {
    if (ref === 'HEAD') return null;
    
    try {
      const date = execSync(`git log -1 --format=%ai ${ref}`, { encoding: 'utf8' }).trim();
      return new Date(date).toISOString().split('T')[0];
    } catch {
      return null;
    }
  }

  getCommitsBetween(currentRef, previousRef) {
    try {
      const range = previousRef ? `${previousRef}..${currentRef}` : currentRef;
      const output = execSync(`git log ${range} --pretty=format:"%H|%s|%an|%ad" --date=short`, { 
        encoding: 'utf8' 
      });
      
      return output.trim().split('\n')
        .filter(line => line)
        .map(line => {
          const [hash, message, author, date] = line.split('|');
          return { hash, message, author, date };
        });
    } catch {
      return [];
    }
  }

  categorizeCommits(commits) {
    const categories = {
      breaking: [],
      added: [],
      changed: [],
      deprecated: [],
      removed: [],
      fixed: [],
      security: []
    };
    
    commits.forEach(commit => {
      const message = commit.message.toLowerCase();
      
      // Conventional commits parsing
      if (this.options.conventionalCommits) {
        if (message.includes('!:') || message.includes('breaking change')) {
          categories.breaking.push(commit);
        } else if (message.startsWith('feat')) {
          categories.added.push(commit);
        } else if (message.startsWith('fix')) {
          categories.fixed.push(commit);
        } else if (message.startsWith('perf') || message.startsWith('refactor')) {
          categories.changed.push(commit);
        } else if (message.includes('deprecat')) {
          categories.deprecated.push(commit);
        } else if (message.includes('remov')) {
          categories.removed.push(commit);
        } else if (message.includes('security')) {
          categories.security.push(commit);
        } else {
          categories.changed.push(commit);
        }
      } else {
        // Simple keyword-based categorization
        if (message.includes('break')) {
          categories.breaking.push(commit);
        } else if (message.includes('add') || message.includes('new')) {
          categories.added.push(commit);
        } else if (message.includes('fix') || message.includes('bug')) {
          categories.fixed.push(commit);
        } else if (message.includes('remove') || message.includes('delete')) {
          categories.removed.push(commit);
        } else if (message.includes('security')) {
          categories.security.push(commit);
        } else {
          categories.changed.push(commit);
        }
      }
    });
    
    return categories;
  }

  getCategoryTitle(category) {
    const titles = {
      breaking: '💥 Breaking Changes',
      added: '✨ Added',
      changed: '🔄 Changed',
      deprecated: '⚠️ Deprecated',
      removed: '🗑️ Removed',
      fixed: '🐛 Fixed',
      security: '🔒 Security'
    };
    
    return titles[category] || category.charAt(0).toUpperCase() + category.slice(1);
  }
}

// CLI Usage
if (require.main === module) {
  const generator = new ChangelogGenerator({
    outputFile: process.argv[2] || 'docs/changelog/index.md'
  });
  
  generator.generateChangelog().catch(console.error);
}

module.exports = ChangelogGenerator;
```

### 6. Deploy Script (`scripts/deploy-docs.sh`)

```bash
#!/bin/bash

# Deploy documentation to GitHub Pages

set -e

echo "🚀 Deploying documentation to GitHub Pages..."

# Configuration
DOCS_DIR="docs"
BUILD_DIR="_site"
BRANCH="gh-pages"

# Check if we're in the right directory
if [ ! -d "$DOCS_DIR" ]; then
    echo "❌ Error: docs directory not found"
    exit 1
fi

# Generate API documentation
echo "📚 Generating API documentation..."
node scripts/generate-docs.js

# Update changelog
echo "📝 Updating changelog..."
node scripts/update-changelog.js

# Build Jekyll site
echo "🔨 Building Jekyll site..."
cd $DOCS_DIR
bundle install --quiet
bundle exec jekyll build --destination="../$BUILD_DIR"
cd ..

# Deploy to gh-pages branch
echo "📤 Deploying to $BRANCH branch..."

# Create/checkout gh-pages branch
if git show-ref --verify --quiet refs/heads/$BRANCH; then
    git checkout $BRANCH
else
    git checkout --orphan $BRANCH
    git rm -rf .
fi

# Copy built site
cp -r $BUILD_DIR/* .
cp $BUILD_DIR/.nojekyll . 2>/dev/null || true

# Commit and push
git add .
git commit -m "Deploy documentation - $(date '+%Y-%m-%d %H:%M:%S')"
git push origin $BRANCH --force

# Return to main branch
git checkout main

echo "✅ Documentation deployed successfully!"
echo "🌐 Visit: https://yourorg.github.io/devtoolskit"
```

## Workflow Automatico

### 7. GitHub Actions (`docs/.github/workflows/docs.yml`)

```yaml
name: Documentation

on:
  push:
    branches: [ main ]
    paths: 
      - 'src/**'
      - 'docs/**'
      - 'package.json'
  pull_request:
    branches: [ main ]
    paths:
      - 'docs/**'
  release:
    types: [published]

jobs:
  build-and-deploy:
    runs-on: ubuntu-latest
    
    steps:
    - name: Checkout
      uses: actions/checkout@v3
      with:
        fetch-depth: 0 # Needed for changelog generation
        
    - name: Setup Node.js
      uses: actions/setup-node@v3
      with:
        node-version: '18'
        cache: 'npm'
        
    - name: Setup Ruby
      uses: ruby/setup-ruby@v1
      with:
        ruby-version: 3.0
        bundler-cache: true
        working-directory: docs
        
    - name: Install dependencies
      run: |
        npm ci
        cd docs && bundle install
        
    - name: Generate API documentation
      run: node scripts/generate-docs.js
      
    - name: Update changelog
      run: node scripts/update-changelog.js
      
    - name: Build documentation
      run: |
        cd docs
        bundle exec jekyll build
        
    - name: Test documentation
      run: |
        cd docs
        bundle exec htmlproofer ./_site \
          --disable-external \
          --check-html \
          --check-img-http \
          --check-opengraph
          
    - name: Deploy to GitHub Pages
      if: github.ref == 'refs/heads/main'
      uses: peaceiris/actions-gh-pages@v3
      with:
        github_token: ${{ secrets.GITHUB_TOKEN }}
        publish_dir: ./docs/_site
        cname: devtoolskit.example.com # Optional custom domain
        
    - name: Update search index
      if: github.ref == 'refs/heads/main'
      run: |
        # Generate search index for documentation
        node scripts/generate-search-index.js
        
    - name: Notify team
      if: github.ref == 'refs/heads/main'
      uses: 8398a7/action-slack@v3
      with:
        status: success
        text: |
          📚 Documentation updated successfully!
          🌐 Live at: https://yourorg.github.io/devtoolskit
        webhook_url: ${{ secrets.SLACK_WEBHOOK_URL }}
      env:
        SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK_URL }}
```

## Risultati e Metriche

### Performance
- ✅ **Build Time**: <2 minuti
- ✅ **Page Load**: <1 secondo
- ✅ **Search**: Istantaneo
- ✅ **Mobile**: 100% responsive

### SEO e Accessibilità
- ✅ **Lighthouse Score**: 95+
- ✅ **WCAG 2.1**: AA compliant
- ✅ **Search Indexing**: Completo
- ✅ **Social Sharing**: Ottimizzato

### Features Avanzate
- ✅ **API Auto-generation**: Da JSDoc
- ✅ **Changelog Automatico**: Da git commits
- ✅ **Search Functionality**: Full-text search
- ✅ **Version Management**: Multi-version support
- ✅ **Interactive Examples**: Live code demos

---

**Live Documentation**: https://yourorg.github.io/devtoolskit  
**Repository**: https://github.com/yourorg/devtoolskit  
**Auto-Deploy**: Su ogni push a main
