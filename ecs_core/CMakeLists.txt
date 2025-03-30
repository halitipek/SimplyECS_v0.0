#cmake ecs core
set(ECS_CORE_SOURCES
        src/EntityManager.cpp
        src/SystemManager.cpp
        src/Coordinator.cpp
        src/ComponentManager.cpp
        src/System.cpp
        src/EventBus.cpp
        include/ecs/Debug.hpp
        include/ecs/DenseMap.hpp
)

add_library(ecs_core STATIC ${ECS_CORE_SOURCES})

target_include_directories(ecs_core
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
