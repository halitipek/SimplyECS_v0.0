include(FetchContent)

# Only attempt to download dependencies if requested
if(SIMPLYECS_FETCH_DEPENDENCIES)
    # Set FetchContent to use quiet mode to avoid excessive output
    set(FETCHCONTENT_QUIET OFF)

    # For samples, we need SFML
    if(SIMPLYECS_BUILD_SAMPLES)
        message(STATUS "Setting up SFML dependency")

        # Allow specifying custom SFML location
        if(NOT DEFINED SFML_DIR)
            # By default, we'll download and build SFML
            FetchContent_Declare(
                    SFML
                    GIT_REPOSITORY https://github.com/SFML/SFML.git
                    GIT_TAG 2.6.1
                    GIT_SHALLOW TRUE
            )

            # SFML options
            set(SFML_BUILD_AUDIO FALSE CACHE BOOL "")
            set(SFML_BUILD_NETWORK FALSE CACHE BOOL "")
            set(SFML_BUILD_EXAMPLES FALSE CACHE BOOL "")
            set(SFML_BUILD_DOC FALSE CACHE BOOL "")
            set(SFML_BUILD_GRAPHICS TRUE CACHE BOOL "")
            set(SFML_BUILD_WINDOW TRUE CACHE BOOL "")
            set(SFML_BUILD_SYSTEM TRUE CACHE BOOL "")

            # On Windows, make sure we prefer shared libraries to easily copy DLLs
            if(WIN32)
                set(BUILD_SHARED_LIBS TRUE CACHE BOOL "Build shared libraries")
            endif()

            FetchContent_MakeAvailable(SFML)
        else()
            message(STATUS "Using user-specified SFML_DIR: ${SFML_DIR}")
            find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
        endif()
    endif()
else()
    # If not auto-fetching, we need to manually check for dependencies
    if(SIMPLYECS_BUILD_SAMPLES)
        find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
    endif()
endif()