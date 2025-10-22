# Project: Integrate the Unity Test Framework and lunch first simple unit test

## Table of Contents
1. [Introduction](#1-introduction)  
2. [Requirements](#2-requirements)  
3. [Downloading Unity](#3-downloading-unity)  
4. [Project Setup](#4-project-setup)  
5. [Writing Your First Test](#5-writing-your-first-test)  
6. [Creating a Test Runner](#6-creating-a-test-runner)  
7. [Building and Running Tests with CMake](#7-building-and-running-tests-with-cmake)  
8. [Next Steps](#8-next-steps)  

---

## 1. Introduction
This guide shows how to integrate the Unity Test Framework into the Light App project.
Unity is a lightweight C test framework, ideal for embedded applications.

The project implements a layered embedded application inspired by the AUTOSAR architecture and simples tests.  
The codebase is organized into layers: **MCAL**, **BSW**, **RTE**, **APP**, and **ProjectConfig**, to maintain a structured architecture and allow future expansion, testing and launching on board (Nucleo).

It allows run simple tasks, such as controlling an LED.  

This project was created as a learning aid for the course *"C for Advanced Users"* by **UCEGOSU**: [https://cdlazaawansowanych.pl/](https://cdlazaawansowanych.pl/)   
The concept of application layers is based on:  
[https://yoginsavani.com/understanding-autosar-architecture-a-guide-to-automotive-software-integration/](https://yoginsavani.com/understanding-autosar-architecture-a-guide-to-automotive-software-integration/)

---

## 2. Requirements
Make sure you have the following tools installed:
- C compiler (gcc / clang / MinGW)
- CMake (≥ 3.16)
- Ninja or Make as a build backend
You can check how to lunch this tools on:
1) https://github.com/bartekzone/build_simple_app_gcc_make_part1
2) https://github.com/bartekzone/build_simple_app_gcc_make_part2
3) https://github.com/bartekzone/cmake_ninja_build_simple_app

Clone or download the repository containing the Lights application code:
    git clone https://github.com/yourusername/lights-app.git
Change current director:
    cd lightsAppUnity

---

## 3. Downloading Unity

Clone the Unity framework (or copy the source files into your project):
    git clone https://github.com/ThrowTheSwitch/Unity.git
You mainly need files: 
    Unity/src/unity.c  
    Unity/src/unity.h  
    Unity/src/unity_internals.h

---

## 4. Project Setup
Inside the project root, create a new folder for tests:
    mkdir Testing
Inside the Testing director, create a new subfolder:
    mkdir Unity
<pre lang="markdown"> <code> ``` 
Example structure:
LightAppUnity/
│
├── APP/
├── BSW/
├── MCAL/
├── RTE/
├── ProjectConfig/
├── Testing/
│   ├── test_gpio_unity.c
│   ├── unity/
│   │   ├── unity.c
│   │   ├── unity.h
│   │   └── unity_internals.h
├── main.c
└── CMakeLists.txt
``` </code> </pre>

---

## 5. Writing Your First Test
Create testing/test_gpio_unity.c with the following content:
#include "unity.h"  
#include "Gpio.h"  
#include "Gpio_Cfg.h"  
#include "ErrorHandler.h"  

// Example test: check if LED can be set correctly  
void test_gpio_set_valid_led(void) {  
    bool result = gpio_set(GPIO_SIGNAL_LED);  
    TEST_ASSERT_TRUE(result);  
}  
Explanation:  
We include unity.h to use Unity macros.  
TEST_ASSERT_TRUE(expr) checks if the given expression is true.  
Each test is a void function prefixed with test_.  
Unity automatically registers and runs these functions through the test runner (step 6).  

---

## 6. Creating a Test Runner
Add following content to test_gpio_unity.c

void setUp(void) {  
    // This function runs before each test.  
    // Use it to initialize or reset variables/hardware stubs.  
}  

void tearDown(void) {  
    // This function runs after each test.  
    // Use it to clean up.  
}  

int main(void) {  
    UNITY_BEGIN(); // Start Unity test session  

    RUN_TEST(test_gpio_set_valid_led); // Run our test function

    return UNITY_END(); // Finish and report results
}

Explanation:

UNITY_BEGIN() starts the test runner.  
RUN_TEST(test_fn) calls the test and logs pass/fail.  
UNITY_END() prints a summary and returns exit code.  
setUp() / tearDown() are hooks for preparing and cleaning test state.  

---

## 7. Building and Running Tests with CMake
Use CMakeLists.txt file at the root of your project:  
Change the project name:  

    project(MinimalUnityTests C) 
    
In this case main function is in test_gpio_unity.c. 

Update exatuable files to:  
    # Create executable "main" from source files  
        add_executable(app_test_unity  
        testing/unity/unity.c  
        testing/test_gpio_unity.c  
        BSW/GPIO/Gpio.c  
        BSW/GPIO/Gpio_Cfg.c  
        BSW/DET/ErrorHandler.c  
        MCAL/Dio.c  
        )  

Please update also header directories to the include path:  
    target_include_directories(app_test_unity PRIVATE  
        APP BSW/GPIO BSW/DET MCAL RTE ProjectConfig  
        testing/unity testing  
    )  

Create build and run the tests in MINGW terminal:  
    cmake -S . -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Debug  

Build the test executable:  
    cmake --build build  

Run the tests:
    ./build/app_test_unity  

Check test result on terminal "test_gpio_set_valid_led:PASS  
-----------------------  
1 Tests 0 Failures 0 Ignored  
OK"   

---

## 8. Next Steps
Add more tests for gpio module
