/**
 * @file test_gpio_unity.c
 * @brief Unit tests for GPIO functionality using the Unity framework.
 *
 * This file contains test cases for the GPIO module, specifically testing
 * the ability to set a valid LED signal. The Unity test framework is used
 * to execute and validate the tests.
 *
 * @author Bartekzone
 * @date 2025-08-25
 */

#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include "Gpio_Cfg.h"
#include "Gpio.h"
#include "ErrorHandler.h"

/**
 * @brief Set up function required by Unity.
 *
 * This function is called before each test. Use it to initialize
 * mocks or test environment if needed.
 */
void setUp(void)   { /* init/mocks if needed */ }

/**
 * @brief Tear down function required by Unity.
 *
 * This function is called after each test. Use it to clean up
 * resources or reset state if needed.
 */
void tearDown(void){ /* cleanup if needed    */ }

/**
 * @test
 * @brief Test that setting a valid LED returns true.
 *
 * This test checks if the gpio_set function correctly sets a valid
 * LED signal and returns true.
 */
void test_gpio_set_valid_led(void)
{
    bool result = gpio_set(GPIO_SIGNAL_LED);
    TEST_ASSERT_TRUE(result);
}

/**
 * @brief Main function to run Unity tests.
 *
 * Initializes the Unity framework, runs all tests, and returns the
 * test status.
 *
 * @return int Status code from Unity.
 */
int main(void)
{
    UNITY_BEGIN();                        // start Unity
    RUN_TEST(test_gpio_set_valid_led);    // run the test
    return UNITY_END();                 // end Unity and return status
}
