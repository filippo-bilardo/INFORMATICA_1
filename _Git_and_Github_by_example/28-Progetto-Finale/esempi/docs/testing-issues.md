# Testing Issues & Troubleshooting Guide

## Common Testing Problems & Solutions

### 1. Test Environment Issues

#### Problem: Tests Pass Locally, Fail in CI
```javascript
// Common causes and solutions

// ❌ Timezone-dependent tests
test('should format date correctly', () => {
    const date = new Date('2024-01-15T10:00:00');
    expect(formatDate(date)).toBe('January 15, 2024'); // Fails in different timezones
});

// ✅ Fixed version
test('should format date correctly', () => {
    const date = new Date('2024-01-15T10:00:00Z'); // UTC timezone
    expect(formatDate(date)).toBe('January 15, 2024');
});

// ❌ File system path issues
const testFile = './test-data/sample.json'; // Unix path fails on Windows

// ✅ Cross-platform paths
const testFile = path.join(__dirname, 'test-data', 'sample.json');
```

#### Solution: Environment Configuration
```javascript
// jest.config.js
module.exports = {
    testEnvironment: 'node', // or 'jsdom' for browser environment
    setupFilesAfterEnv: ['<rootDir>/tests/setup.js'],
    globalSetup: '<rootDir>/tests/globalSetup.js',
    globalTeardown: '<rootDir>/tests/globalTeardown.js',
    
    // Environment variables for testing
    testEnvironmentOptions: {
        NODE_ENV: 'test',
        DATABASE_URL: 'postgresql://test:test@localhost:5432/test_db'
    }
};

// tests/setup.js
beforeEach(() => {
    // Reset environment state
    process.env.NODE_ENV = 'test';
    jest.clearAllMocks();
    jest.resetModules();
});
```

### 2. Async Testing Problems

#### Problem: Flaky Async Tests
```javascript
// ❌ Race conditions and timing issues
test('should update user after API call', async () => {
    const user = await createUser();
    updateUser(user.id, { name: 'Updated' }); // No await!
    
    expect(user.name).toBe('Updated'); // Test might pass or fail randomly
});

// ❌ Improper promise handling
test('should handle API error', () => {
    const promise = apiCall();
    promise.catch(error => {
        expect(error.message).toBe('Network error'); // Never runs
    });
});
```

#### Solution: Proper Async Handling
```javascript
// ✅ Proper async/await
test('should update user after API call', async () => {
    const user = await createUser();
    await updateUser(user.id, { name: 'Updated' });
    
    const updatedUser = await getUser(user.id);
    expect(updatedUser.name).toBe('Updated');
});

// ✅ Testing rejections correctly
test('should handle API error', async () => {
    await expect(apiCall()).rejects.toThrow('Network error');
});

// ✅ Testing with explicit promise resolution
test('should resolve promise with correct data', () => {
    return expect(fetchUserData()).resolves.toMatchObject({
        id: expect.any(Number),
        name: expect.any(String)
    });
});
```

### 3. Mock and Stub Issues

#### Problem: Incorrect Mocking
```javascript
// ❌ Mocking too much, testing nothing
jest.mock('../database');
jest.mock('../api');
jest.mock('../validation');

test('should create user', async () => {
    const result = await createUser(userData);
    expect(result).toBeDefined(); // This test doesn't verify anything meaningful
});

// ❌ Mocks leaking between tests
const mockFetch = jest.fn();
global.fetch = mockFetch;

test('test1', () => {
    mockFetch.mockResolvedValue({ json: () => ({ data: 'test1' }) });
    // test logic
});

test('test2', () => {
    // mockFetch still has previous mock implementation
    // test might fail unexpectedly
});
```

#### Solution: Strategic Mocking
```javascript
// ✅ Mock only external dependencies
jest.mock('../external-api');
// Keep business logic unmocked to test it properly

// ✅ Proper mock cleanup
beforeEach(() => {
    jest.clearAllMocks();
});

afterEach(() => {
    jest.restoreAllMocks();
});

// ✅ Partial mocking for focused testing
jest.mock('../userService', () => ({
    ...jest.requireActual('../userService'),
    sendEmail: jest.fn() // Mock only the external email service
}));

// ✅ Mock with realistic behavior
const mockDatabase = {
    findUser: jest.fn(),
    createUser: jest.fn(),
    updateUser: jest.fn()
};

mockDatabase.findUser.mockImplementation((id) => {
    const users = { 1: { id: 1, name: 'John' } };
    return Promise.resolve(users[id] || null);
});
```

### 4. Test Data Management

#### Problem: Test Data Pollution
```javascript
// ❌ Tests affecting each other
let globalUser = { id: 1, name: 'John' };

test('should update user name', () => {
    globalUser.name = 'Jane';
    expect(updateUser(globalUser)).toMatchObject({ name: 'Jane' });
});

test('should have original user name', () => {
    expect(globalUser.name).toBe('John'); // Fails because previous test modified it
});
```

#### Solution: Isolated Test Data
```javascript
// ✅ Factory functions for fresh data
function createTestUser(overrides = {}) {
    return {
        id: Math.random(),
        name: 'John Doe',
        email: 'john@example.com',
        created_at: new Date().toISOString(),
        ...overrides
    };
}

// ✅ Database seeding and cleanup
beforeEach(async () => {
    await seedTestDatabase();
});

afterEach(async () => {
    await cleanupTestDatabase();
});

// ✅ Test-specific data setup
describe('User Service', () => {
    let testUser;
    
    beforeEach(() => {
        testUser = createTestUser();
    });
    
    test('should update user', () => {
        const updated = updateUser(testUser, { name: 'Jane' });
        expect(updated.name).toBe('Jane');
        expect(testUser.name).toBe('John Doe'); // Original unchanged
    });
});
```

### 5. Testing Performance Issues

#### Problem: Slow Test Suite
```javascript
// ❌ Tests taking too long
describe('Heavy computation tests', () => {
    test('should calculate complex result', () => {
        const result = heavyComputation(largeDataset); // Takes 30 seconds
        expect(result).toBeDefined();
    });
});

// ❌ Unnecessary database calls in unit tests
test('should validate email format', async () => {
    const user = await createUserInDatabase({ email: 'invalid-email' });
    expect(validateEmail(user.email)).toBe(false);
});
```

#### Solution: Optimize Test Performance
```javascript
// ✅ Use smaller datasets for unit tests
test('should calculate result', () => {
    const result = heavyComputation(smallTestDataset);
    expect(result).toBeDefined();
});

// ✅ Unit tests without external dependencies
test('should validate email format', () => {
    expect(validateEmail('invalid-email')).toBe(false);
    expect(validateEmail('valid@email.com')).toBe(true);
});

// ✅ Parallel test execution
// jest.config.js
module.exports = {
    maxWorkers: '50%', // Use half of available CPU cores
    testTimeout: 10000, // Set reasonable timeout
    
    // Run fast tests first
    testSequencer: './custom-sequencer.js'
};

// ✅ Test grouping for efficiency
describe('Database operations', () => {
    beforeAll(async () => {
        await setupDatabaseConnection(); // Once per suite
    });
    
    afterAll(async () => {
        await closeDatabaseConnection();
    });
    
    // Multiple tests share setup
});
```

### 6. Integration Test Issues

#### Problem: External Service Dependencies
```javascript
// ❌ Tests depending on external APIs
test('should fetch user data', async () => {
    const userData = await fetch('https://api.external-service.com/user/123');
    expect(userData).toBeDefined(); // Fails if service is down
});

// ❌ Database state assumptions
test('should find existing user', async () => {
    const user = await User.findById(123); // Assumes user exists
    expect(user.name).toBe('John');
});
```

#### Solution: Controlled Integration Testing
```javascript
// ✅ Use test doubles for external services
// __mocks__/external-api.js
module.exports = {
    fetchUserData: jest.fn(() => Promise.resolve({
        id: 123,
        name: 'Test User',
        email: 'test@example.com'
    }))
};

// ✅ Database test fixtures
beforeEach(async () => {
    await User.create({
        id: 123,
        name: 'John',
        email: 'john@test.com'
    });
});

// ✅ Contract testing for API dependencies
describe('External API Contract', () => {
    test('should match expected user schema', async () => {
        const mockResponse = getMockApiResponse();
        expect(mockResponse).toMatchSchema(userSchema);
    });
});
```

### 7. Test Coverage Issues

#### Problem: False Coverage Confidence
```javascript
// ❌ High coverage, poor quality tests
function calculateDiscount(price, userType) {
    if (userType === 'premium') {
        return price * 0.2;
    } else if (userType === 'regular') {
        return price * 0.1;
    }
    return 0; // This line is never tested
}

test('should calculate discount', () => {
    expect(calculateDiscount(100, 'premium')).toBe(20);
    expect(calculateDiscount(100, 'regular')).toBe(10);
    // Missing test for default case and edge cases
});
```

#### Solution: Meaningful Coverage
```javascript
// ✅ Comprehensive test cases
describe('calculateDiscount', () => {
    test('should give 20% discount for premium users', () => {
        expect(calculateDiscount(100, 'premium')).toBe(20);
    });
    
    test('should give 10% discount for regular users', () => {
        expect(calculateDiscount(100, 'regular')).toBe(10);
    });
    
    test('should give no discount for unknown user types', () => {
        expect(calculateDiscount(100, 'unknown')).toBe(0);
        expect(calculateDiscount(100, null)).toBe(0);
        expect(calculateDiscount(100, undefined)).toBe(0);
    });
    
    test('should handle edge cases', () => {
        expect(calculateDiscount(0, 'premium')).toBe(0);
        expect(calculateDiscount(-100, 'premium')).toBe(-20);
    });
});

// ✅ Coverage analysis
// package.json
{
    "scripts": {
        "test:coverage": "jest --coverage --coverageThreshold='{\"global\":{\"branches\":80,\"functions\":80,\"lines\":80,\"statements\":80}}'"
    }
}
```

### 8. E2E Test Troubleshooting

#### Problem: Flaky Browser Tests
```javascript
// ❌ Flaky element selection
test('should login user', async () => {
    await page.click('#login-button'); // Element might not be ready
    await page.type('#email', 'user@example.com');
    expect(await page.textContent('.welcome')).toBe('Welcome!');
});
```

#### Solution: Robust E2E Testing
```javascript
// ✅ Wait for elements and stable state
test('should login user', async () => {
    // Wait for element to be available and stable
    await page.waitForSelector('#login-button', { state: 'visible' });
    await page.waitForLoadState('networkidle');
    
    await page.fill('#email', 'user@example.com');
    await page.fill('#password', 'password123');
    await page.click('#login-button');
    
    // Wait for navigation and content
    await page.waitForURL('/dashboard');
    await expect(page.locator('.welcome')).toHaveText('Welcome!');
});

// ✅ Page Object Model for maintainability
class LoginPage {
    constructor(page) {
        this.page = page;
        this.emailInput = page.locator('#email');
        this.passwordInput = page.locator('#password');
        this.loginButton = page.locator('#login-button');
    }
    
    async login(email, password) {
        await this.emailInput.fill(email);
        await this.passwordInput.fill(password);
        await this.loginButton.click();
        await this.page.waitForURL('/dashboard');
    }
}
```

### 9. Debugging Test Failures

#### Debug Configuration
```javascript
// jest.config.js - Debug mode
module.exports = {
    // Keep tests open for debugging
    detectOpenHandles: true,
    forceExit: false,
    
    // Verbose output
    verbose: true,
    
    // Custom reporter for better debugging
    reporters: [
        'default',
        ['jest-html-reporters', {
            publicPath: './test-reports',
            filename: 'test-report.html'
        }]
    ]
};

// VS Code debug configuration
// .vscode/launch.json
{
    "configurations": [
        {
            "name": "Debug Jest Tests",
            "type": "node",
            "request": "launch",
            "program": "${workspaceFolder}/node_modules/.bin/jest",
            "args": ["--runInBand", "--testNamePattern=specific test"],
            "console": "integratedTerminal",
            "internalConsoleOptions": "neverOpen"
        }
    ]
}
```

#### Test Debugging Utilities
```javascript
// Custom test utilities for debugging
function debugTest(testName, testFn) {
    test(testName, async () => {
        console.log(`🐛 Starting debug test: ${testName}`);
        
        try {
            await testFn();
            console.log(`✅ Debug test passed: ${testName}`);
        } catch (error) {
            console.log(`❌ Debug test failed: ${testName}`);
            console.log('Error details:', error);
            console.log('Stack trace:', error.stack);
            throw error;
        }
    });
}

// Snapshot testing for complex objects
expect(complexObject).toMatchSnapshot();

// Custom matchers for better assertions
expect.extend({
    toBeValidUser(received) {
        const pass = received && 
                     typeof received.id === 'number' &&
                     typeof received.email === 'string' &&
                     received.email.includes('@');
        
        return {
            message: () => `expected ${received} to be a valid user object`,
            pass
        };
    }
});
```

Questa guida aiuta a identificare e risolvere i problemi più comuni nei test del progetto finale, migliorando la reliability e l'efficacia della test suite.
