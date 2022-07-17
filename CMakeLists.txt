cmake_minimum_required(VERSION 3.16)
add_executable(RPI_UART_Demo main.cpp PIUART.cpp PIUART.h)
target_link_libraries(RPI_UART_Demo PRIVATE project_options project_warnings)

target_link_system_libraries(RPI_UART_Demo PRIVATE pigpio)
include(FetchContent)

# Not ideal to use this global variable, but necessary to make sure
# that tooling and projects use the same version
set(CMAKE_CXX_STANDARD 17)

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS OFF)

# Add project_options v0.17.0
# https://github.com/cpp-best-practices/project_options
FetchContent_Declare(_project_options
        URL https://github.com/cpp-best-practices/project_options/archive/refs/tags/v0.17.0.zip)
FetchContent_MakeAvailable(_project_options)
include(${_project_options_SOURCE_DIR}/Index.cmake)

# Set the project name and language
project(RPI_UART_Demo LANGUAGES CXX C)

project_options(
        #    ENABLE_CACHE
        #    ENABLE_CPPCHECK
        #    ENABLE_CLANG_TIDY
        # ENABLE_CONAN
        ENABLE_INTERPROCEDURAL_OPTIMIZATION
        ENABLE_NATIVE_OPTIMIZATION
        # ENABLE_DOXYGEN
        # ENABLE_COVERAGE
        # ENABLE_SANITIZER_ADDRESS
        # ENABLE_SANITIZER_LEAK
        # ENABLE_SANITIZER_UNDEFINED_BEHAVIOR
        # ENABLE_SANITIZER_THREAD
        # ENABLE_SANITIZER_MEMORY
        # ENABLE_PCH
        # PCH_HEADERS
        # WARNINGS_AS_ERRORS
        # ENABLE_INCLUDE_WHAT_YOU_USE
        # ENABLE_USER_LINKER
        # ENABLE_BUILD_WITH_TIME_TRACE
        # ENABLE_UNITY
        # CONAN_OPTIONS
)

target_compile_features(project_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

################################################################################
### Find the pigpio shared libraries.
################################################################################

# Find the path to the pigpio includes.
find_path(pigpio_INCLUDE_DIR
        NAMES pigpio.h pigpiod_if.h pigpiod_if2.h
        HINTS /usr/local/include)

# Find the pigpio libraries.
find_library(pigpio_LIBRARY
        NAMES libpigpio.so
        HINTS /usr/local/lib)
find_library(pigpiod_if_LIBRARY
        NAMES libpigpiod_if.so
        HINTS /usr/local/lib)
find_library(pigpiod_if2_LIBRARY
        NAMES libpigpiod_if2.so
        HINTS /usr/local/lib)

# Set the pigpio variables to plural form to make them accessible for
# the paramount cmake modules.
set(pigpio_INCLUDE_DIRS ${pigpio_INCLUDE_DIR})
set(pigpio_INCLUDES     ${pigpio_INCLUDE_DIR})

# Handle REQUIRED, QUIET, and version arguments
# and set the <packagename>_FOUND variable.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(pigpio
        DEFAULT_MSG
        pigpio_INCLUDE_DIR pigpio_LIBRARY pigpiod_if_LIBRARY pigpiod_if2_LIBRARY)