cmake_minimum_required(VERSION 3.10)

project(conan-examples)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out)

set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost REQUIRED COMPONENTS filesystem)
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "Boost_VERSION: ${Boost_VERSION}")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts)

# 如果有和特定平台相关的配置，可以在这里添加
if (${HOST_PLATFORM} STREQUAL "macos-arm64")
    set(MACOSX_DEPLOYMENT_TARGET 12.0)
    set(CMAKE_OSX_DEPLOYMENT_TARGET 12.0)
    message(STATUS "building for macos-arm64")
elseif (${HOST_PLATFORM} STREQUAL "macos-x86_64")
    set(MACOSX_DEPLOYMENT_TARGET 12.0)
    set(CMAKE_OSX_DEPLOYMENT_TARGET 12.0)
    message(STATUS "building for macos-x86_64")
elseif (${HOST_PLATFORM} STREQUAL "linux-x86_64")
    message(STATUS "building for linux-x86_64")
elseif (${HOST_PLATFORM} STREQUAL "linux-arm64")
    message(STATUS "building for linux-arm64")
elseif (${HOST_PLATFORM} STREQUAL "windows-x86_64")
    message(STATUS "building for windows-x86_64")
endif()

add_executable(test_boost src/test_boost.cpp)
target_link_libraries(test_boost PRIVATE Boost::filesystem)

add_executable(test_qt src/test_qt.cpp)
target_link_libraries(test_qt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)