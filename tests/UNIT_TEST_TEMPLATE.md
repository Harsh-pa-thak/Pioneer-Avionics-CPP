# Unit Test Template and Guidelines

This file describes a minimal template and guidelines for adding unit tests for ARK modules.

Purpose:
- Provide a reproducible, reviewable test that can be run locally by contributors.
- Prefer small, fast unit tests that do not depend on hardware; mock hardware interfaces.

Guidelines:
1. Create a descriptive test filename: `module_feature_test.cpp` or `module_feature_test.md`.
2. Keep tests self-contained and deterministic.
3. Add the test file under `tests/` and link it in the README or CI config if needed.
4. If a test requires hardware, mark it as `integration` and do not run it in the default CI.

Example (pseudocode C++ test):

```cpp
// tests/sample_sensor_test.cpp
// Minimal structure; adapt to your test framework (Catch2, GoogleTest, doctest, etc.).
#include "gtest/gtest.h"
#include "ARK/modules/bmp/bmp.h" // or the header under test

TEST(BmpInit, ReturnsOkOnValidI2C)
{
    // Arrange: create a mock I2C or stub
    // Act: call Bmp::Init(mockI2C)
    // Assert: expect ResultCode::OK
}
```

How to run tests (host-side):
- This project doesn't enforce a specific test framework. If you add a framework, update
  this document with `cmake` and `make` instructions.

Submit tests in your feature branch and ensure they pass before opening a PR against `workingiteration1`.
