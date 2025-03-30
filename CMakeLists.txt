cmake_minimum_required(VERSION 3.14)
project(SimplyECS VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(SIMPLYECS_BUILD_SAMPLES "Build sample projects" ON)
option(SIMPLYECS_FETCH_DEPENDENCIES "Automatically download dependencies" ON)

# Setup external dependencies
include(cmake/Dependencies.cmake)

# Main ECS core library
add_subdirectory(ecs_core)

# Examples
if(SIMPLYECS_BUILD_SAMPLES)
    add_subdirectory(samples)
endif()

# Main executable (simple test app, optional)
if(SIMPLYECS_BUILD_SAMPLES)
    add_executable(SimplyECS main.cpp)
    target_link_libraries(SimplyECS PRIVATE ecs_core)
endif()

# Install rules for the library
include(GNUInstallDirs)
install(TARGETS ecs_core
        EXPORT SimplyECSTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(DIRECTORY ecs_core/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export targets
install(EXPORT SimplyECSTargets
        FILE SimplyECSTargets.cmake
        NAMESPACE SimplyECS::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SimplyECS)