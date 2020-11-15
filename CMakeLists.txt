cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(ToyMC)
set(CMAKE_CXX_FLAGS "-Wall")
set (ToyMC_VERSION_MAJOR 0)
set (ToyMC_VERSION_MINOR 9)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE debug)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

if (NOT ROOT_FOUND)
    message(WARNING "ROOT was not found with CMAKE_PREFIX_PATH...")
    list(APPEND CMAKE_MODULE_PATH $ENV{ROOTSYS}/etc/cmake)
    find_package(ROOT REQUIRED)
endif ()

if (ROOT_USE_FILE)
    message("-- ROOT_USE_FILE ${ROOT_USE_FILE}")
    include(${ROOT_USE_FILE})
endif()

add_executable(generate src/generate.cc src/generator.cc src/phi_generator.cc src/efficiency.cc src/pt_generator.cc)
target_link_libraries(generate ${ROOT_LIBRARIES})
