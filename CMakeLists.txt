# Version 3.16 is a safe choice.
cmake_minimum_required(VERSION 3.16)

# Name of the project "MinimalUnityTests" and specify the language C.
project(MinimalUnityTests C)

# Set the C language standard
# The first line: require at least C99.
# The second line: make this requirement mandatory.
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Create executable from source files
add_executable(app_test_unity
    testing/unity/unity.c
    testing/test_gpio_unity.c
    BSW/GPIO/Gpio.c
    BSW/GPIO/Gpio_Cfg.c
    BSW/DET/ErrorHandler.c
    MCAL/Dio.c
)

# Add header directories to the include path.
# PRIVATE means these include directories are only for this target.
target_include_directories(app_test_unity PRIVATE
    APP BSW/GPIO BSW/DET MCAL RTE ProjectConfig
    testing/unity testing
)

# target_compile_options() adds extra compilation options.
# -Wall and -Wextra enable common warnings that help catch bugs.
target_compile_options(app_test_unity PRIVATE -Wall -Wextra)
