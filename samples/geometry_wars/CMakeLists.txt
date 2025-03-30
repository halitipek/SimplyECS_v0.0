set(GW_SOURCES
        src/main.cpp
        src/Game.cpp
        src/GameStates/StateMachine.cpp
        src/Managers/ConfigManager.cpp
        src/ECS/GameInit.cpp
        src/GameStates/MenuState.cpp
        src/GameStates/PlayState.cpp
        src/GameStates/GameOverState.cpp
        src/Systems/BoundarySystem.cpp
        src/Systems/CollisionSystem.cpp
        src/Systems/CollisionResponseSystem.cpp
        src/Systems/HealthSystem.cpp
        src/Systems/InputSystem.cpp
        src/Systems/LifespanSystem.cpp
        src/Systems/MovementSystem.cpp
        src/Systems/ParticleSystem.cpp
        src/Factory/EntityFactory.cpp
        src/Systems/RenderSystem.cpp
        src/Core/Helpers.cpp
        src/Systems/ScoreSystem.cpp
        src/Systems/EnemySpawnSystem.cpp
        src/Systems/PlayerSpawnSystem.cpp
        src/Systems/WeaponSystem.cpp
        src/Systems/AdvancedEnemySystem.cpp
)

add_executable(geometry_wars ${GW_SOURCES})

# Define resource directory path
target_compile_definitions(geometry_wars PRIVATE HOME_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(geometry_wars
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(geometry_wars
        PRIVATE
        ecs_core
        sfml-system
        sfml-window
        sfml-graphics
)

# Copy resources directory to output folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Copy SFML DLLs to output directory on Windows
if(WIN32)
    # Add a post-build command that will copy the needed DLLs
    # This is done using generator expressions instead of trying to find DLLs during configure time
    add_custom_command(TARGET geometry_wars POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "Copying SFML DLLs to target directory"

            # For each SFML component we use, try to copy the DLL to the target directory
            # Debug DLLs
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE_DIR:geometry_wars>
    )
endif()