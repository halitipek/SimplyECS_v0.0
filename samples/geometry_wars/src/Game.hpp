/**
* @file Game.hpp
 * @brief Main game class that coordinates the game loop and state machine.
 *
 * The Game class initializes the ECS framework, manages the game window,
 * and controls the main game loop including event handling, updating, and rendering.
 */
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <ecs/Coordinator.hpp>
#include <ecs/EventBus.hpp>
#include "GameStates/StateMachine.hpp"

class Game
{
public:
    /**
     * @brief Constructor that initializes the game with configuration.
     * @param configPath Path to the game configuration file.
     */
    explicit Game(const std::string& configPath);

    /**
     * @brief Initializes the ECS system and registers components and systems.
     */
    void Init();

    /**
     * @brief Starts the main game loop.
     */
    void Run();

private:
    sf::RenderWindow m_window;     // SFML window for rendering
    ecs::Coordinator m_coordinator; // ECS coordinator
    ecs::EventBus    m_eventBus;    // Event communication system
    StateMachine     m_stateMachine; // Game state management

    sf::Font  m_font;     // Font used for text rendering
    sf::Clock m_fpsClock; // Clock for FPS calculation
    sf::Text  m_fpsText;  // Text displaying current FPS
    int m_fpsCounter;     // Counter for frames per second
    int m_currentFps;     // Current FPS value

    /**
     * @brief Processes window and input events.
     */
    void ProcessEvents();

    /**
     * @brief Updates game logic.
     * @param dt Delta time since last update.
     */
    void Update(float dt);

    /**
     * @brief Renders the current game state.
     * @param dt Delta time since last render.
     */
    void Render(float dt);
};

#endif //GAME_HPP