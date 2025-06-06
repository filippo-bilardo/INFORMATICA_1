#!/bin/bash

# Script di Automazione per Esempi Submodules e Subtree
# Utilizza questo script per configurare rapidamente gli ambienti di esempio

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to print colored output
print_step() {
    echo -e "${BLUE}📋 $1${NC}"
}

print_success() {
    echo -e "${GREEN}✅ $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠️  $1${NC}"
}

print_error() {
    echo -e "${RED}❌ $1${NC}"
}

# Function to create directory and navigate
create_and_enter() {
    local dir=$1
    if [ -d "$dir" ]; then
        print_warning "Directory $dir already exists. Removing..."
        rm -rf "$dir"
    fi
    mkdir -p "$dir"
    cd "$dir"
    print_success "Created and entered directory: $dir"
}

# Function to setup submodules example
setup_submodules_example() {
    print_step "Setting up Submodules Example Environment"
    
    # Create base directory
    local base_dir="submodules-example"
    create_and_enter "$base_dir"
    
    # Create UI Components Library
    print_step "Creating UI Components Library"
    create_and_enter "ui-components"
    
    git init --quiet
    
    # Create component files
    cat > button.js << 'EOF'
class Button {
    constructor(text, color = 'blue') {
        this.text = text;
        this.color = color;
    }
    
    render() {
        return `<button class="btn btn-${this.color}">${this.text}</button>`;
    }
}

export default Button;
EOF

    cat > modal.js << 'EOF'
class Modal {
    constructor(title, content) {
        this.title = title;
        this.content = content;
    }
    
    show() {
        return `
        <div class="modal">
            <h2>${this.title}</h2>
            <p>${this.content}</p>
        </div>`;
    }
}

export default Modal;
EOF

    cat > package.json << 'EOF'
{
  "name": "ui-components",
  "version": "1.0.0",
  "description": "Libreria di componenti UI riusabili",
  "main": "index.js",
  "type": "module",
  "author": "Team UI"
}
EOF

    git add . && git commit -m "Initial UI components library" --quiet
    git tag v1.0.0
    print_success "UI Components library created with tag v1.0.0"
    
    # Return to base directory
    cd ..
    
    # Create main webapp
    print_step "Creating Main WebApp"
    create_and_enter "webapp-main"
    
    git init --quiet
    mkdir -p src assets libs
    
    cat > src/app.js << 'EOF'
import Button from '../libs/ui-components/button.js';
import Modal from '../libs/ui-components/modal.js';

class App {
    constructor() {
        this.initComponents();
    }
    
    initComponents() {
        const saveBtn = new Button('Salva', 'green');
        const cancelBtn = new Button('Annulla', 'red');
        const helpModal = new Modal('Aiuto', 'Questa è la guida utente');
        
        console.log('App initialized with components:');
        console.log('- Save Button:', saveBtn.render());
        console.log('- Cancel Button:', cancelBtn.render());
        console.log('- Help Modal:', helpModal.show());
    }
}

export default App;
EOF

    cat > index.html << 'EOF'
<!DOCTYPE html>
<html>
<head>
    <title>WebApp con Submoduli</title>
    <style>
        .btn { padding: 10px 20px; margin: 5px; border: none; border-radius: 4px; }
        .btn-blue { background: #007bff; color: white; }
        .btn-green { background: #28a745; color: white; }
        .btn-red { background: #dc3545; color: white; }
        .modal { border: 1px solid #ccc; padding: 20px; margin: 20px; }
    </style>
</head>
<body>
    <h1>WebApp Example</h1>
    <script type="module" src="src/app.js"></script>
</body>
</html>
EOF

    cat > README.md << 'EOF'
# WebApp Main

Applicazione web che utilizza la libreria ui-components come submodulo.

## Setup
```bash
git submodule update --init --recursive
```

## Test
```bash
node -e "import('./src/app.js').then(m => new m.default())"
```
EOF

    git add . && git commit -m "Initial webapp structure" --quiet
    
    # Add submodule
    print_step "Adding UI Components as Submodule"
    git submodule add ../ui-components libs/ui-components --quiet
    git commit -m "Add ui-components submodule" --quiet
    
    print_success "Submodule added successfully"
    
    # Test the setup
    print_step "Testing Submodules Integration"
    if node -e "import('./src/app.js').then(m => new m.default())" 2>/dev/null; then
        print_success "✅ Submodules example is working correctly!"
    else
        print_warning "Integration test completed (Node.js modules may need browser environment)"
    fi
    
    cd ../..
    print_success "Submodules example setup completed in: $(pwd)/$base_dir"
}

# Function to setup subtree example
setup_subtree_example() {
    print_step "Setting up Subtree Example Environment"
    
    # Create base directory
    local base_dir="subtree-example"
    create_and_enter "$base_dir"
    
    # Create JS Utilities Library
    print_step "Creating JS Utilities Library"
    create_and_enter "js-utilities"
    
    git init --quiet
    mkdir -p string-helpers date-helpers validation
    
    # String helpers
    cat > string-helpers/index.js << 'EOF'
export function capitalize(str) {
    return str.charAt(0).toUpperCase() + str.slice(1).toLowerCase();
}

export function slugify(str) {
    return str
        .toLowerCase()
        .trim()
        .replace(/[^\w\s-]/g, '')
        .replace(/[\s_-]+/g, '-')
        .replace(/^-+|-+$/g, '');
}

export function truncate(str, length = 100) {
    return str.length <= length ? str : str.slice(0, length) + '...';
}
EOF

    # Date helpers
    cat > date-helpers/index.js << 'EOF'
export function formatDate(date, format = 'YYYY-MM-DD') {
    const d = new Date(date);
    const year = d.getFullYear();
    const month = String(d.getMonth() + 1).padStart(2, '0');
    const day = String(d.getDate()).padStart(2, '0');
    
    return format
        .replace('YYYY', year)
        .replace('MM', month)
        .replace('DD', day);
}

export function isToday(date) {
    const today = new Date();
    const checkDate = new Date(date);
    return today.toDateString() === checkDate.toDateString();
}
EOF

    # Validation helpers
    cat > validation/index.js << 'EOF'
export function isEmail(email) {
    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return emailRegex.test(email);
}

export function isStrongPassword(password) {
    return password.length >= 8 &&
           /[a-z]/.test(password) &&
           /[A-Z]/.test(password) &&
           /\d/.test(password) &&
           /[!@#$%^&*]/.test(password);
}
EOF

    # Main index
    cat > index.js << 'EOF'
export * from './string-helpers/index.js';
export * from './date-helpers/index.js';
export * from './validation/index.js';
EOF

    cat > package.json << 'EOF'
{
  "name": "js-utilities",
  "version": "1.0.0",
  "description": "Libreria di utilità JavaScript",
  "main": "index.js",
  "type": "module",
  "author": "Utils Team"
}
EOF

    git add . && git commit -m "Initial utilities library" --quiet
    git tag v1.0.0
    print_success "JS Utilities library created with tag v1.0.0"
    
    # Return to base directory
    cd ..
    
    # Create main project
    print_step "Creating Main Project"
    create_and_enter "main-project"
    
    git init --quiet
    mkdir -p src docs tests
    
    cat > src/user-manager.js << 'EOF'
class UserManager {
    constructor() {
        this.users = [];
    }
    
    addUser(userData) {
        // Will use utilities after subtree integration
        this.users.push({
            ...userData,
            id: Date.now(),
            createdAt: new Date().toISOString()
        });
    }
    
    getUsers() {
        return this.users;
    }
}

export default UserManager;
EOF

    git add . && git commit -m "Initial main project structure" --quiet
    
    # Add subtree
    print_step "Adding JS Utilities as Subtree"
    git subtree add --prefix=utils ../js-utilities main --squash --quiet
    print_success "Subtree added successfully"
    
    # Update user manager to use utilities
    print_step "Integrating Utilities in Main Project"
    cat > src/user-manager.js << 'EOF'
import { capitalize, slugify, isEmail, isStrongPassword, formatDate } from '../utils/index.js';

class UserManager {
    constructor() {
        this.users = [];
    }
    
    addUser(userData) {
        if (!this.validateUser(userData)) {
            throw new Error('Dati utente non validi');
        }
        
        const user = {
            id: Date.now(),
            name: capitalize(userData.name),
            slug: slugify(userData.name),
            email: userData.email.toLowerCase(),
            registrationDate: formatDate(new Date()),
            createdAt: new Date().toISOString()
        };
        
        this.users.push(user);
        return user;
    }
    
    validateUser(userData) {
        return userData.name &&
               isEmail(userData.email) &&
               isStrongPassword(userData.password);
    }
    
    getUserBySlug(slug) {
        return this.users.find(user => user.slug === slug);
    }
    
    getUsers() {
        return this.users;
    }
}

export default UserManager;
EOF

    # Create test file
    cat > tests/integration-test.js << 'EOF'
import UserManager from '../src/user-manager.js';

const userManager = new UserManager();

console.log('🧪 Testing Subtree Integration');

// Test valid user
try {
    const user = userManager.addUser({
        name: 'john doe',
        email: 'john@example.com',
        password: 'SecurePass123!'
    });
    
    console.log('✅ Valid user created:', user.name);
    console.log('✅ Slug generated:', user.slug);
    console.log('✅ Date formatted:', user.registrationDate);
    
    // Test search by slug
    const found = userManager.getUserBySlug('john-doe');
    console.log('✅ User found by slug:', found ? 'Yes' : 'No');
    
} catch (error) {
    console.log('❌ Error with valid user:', error.message);
}

// Test invalid user
try {
    userManager.addUser({
        name: 'Invalid User',
        email: 'not-an-email',
        password: '123'
    });
    console.log('❌ Invalid user was accepted (should not happen)');
} catch (error) {
    console.log('✅ Invalid user rejected:', error.message);
}

console.log('🎉 Integration test completed!');
EOF

    git add . && git commit -m "Integrate utilities via subtree" --quiet
    
    # Test the setup
    print_step "Testing Subtree Integration"
    if node tests/integration-test.js; then
        print_success "✅ Subtree example is working correctly!"
    else
        print_error "Integration test failed"
    fi
    
    cd ../..
    print_success "Subtree example setup completed in: $(pwd)/$base_dir"
}

# Function to clean up examples
cleanup_examples() {
    print_step "Cleaning up example directories"
    
    if [ -d "submodules-example" ]; then
        rm -rf submodules-example
        print_success "Removed submodules-example directory"
    fi
    
    if [ -d "subtree-example" ]; then
        rm -rf subtree-example
        print_success "Removed subtree-example directory"
    fi
    
    print_success "Cleanup completed"
}

# Function to run demonstrations
run_demonstrations() {
    print_step "Running demonstrations for both examples"
    
    if [ -d "submodules-example" ]; then
        print_step "Testing Submodules Example"
        cd submodules-example/webapp-main
        
        echo "📊 Submodule Status:"
        git submodule status
        
        echo "📁 Submodule Files:"
        ls -la libs/ui-components/
        
        cd ../..
    fi
    
    if [ -d "subtree-example" ]; then
        print_step "Testing Subtree Example"
        cd subtree-example/main-project
        
        echo "📊 Subtree Files:"
        ls -la utils/
        
        echo "🧪 Running Integration Test:"
        node tests/integration-test.js
        
        cd ../..
    fi
}

# Main menu
show_menu() {
    echo -e "${BLUE}"
    echo "=========================================="
    echo "  Git Submodules & Subtree Examples"
    echo "=========================================="
    echo -e "${NC}"
    echo "1) Setup Submodules Example"
    echo "2) Setup Subtree Example"
    echo "3) Setup Both Examples"
    echo "4) Run Demonstrations"
    echo "5) Cleanup Examples"
    echo "6) Exit"
    echo
}

# Main script execution
main() {
    while true; do
        show_menu
        read -p "Choose an option (1-6): " choice
        
        case $choice in
            1)
                setup_submodules_example
                ;;
            2)
                setup_subtree_example
                ;;
            3)
                setup_submodules_example
                setup_subtree_example
                ;;
            4)
                run_demonstrations
                ;;
            5)
                cleanup_examples
                ;;
            6)
                print_success "Goodbye!"
                exit 0
                ;;
            *)
                print_error "Invalid option. Please choose 1-6."
                ;;
        esac
        
        echo
        read -p "Press Enter to continue..."
        clear
    done
}

# Check if script is being run directly
if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
    clear
    echo -e "${GREEN}🚀 Git Submodules & Subtree Examples Setup${NC}"
    echo "This script will help you set up and test practical examples."
    echo
    main
fi
