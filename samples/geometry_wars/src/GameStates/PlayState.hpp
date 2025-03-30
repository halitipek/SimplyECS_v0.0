/**
 * @file PlayState.hpp
 * @brief Game state for the main gameplay.
 * 
 * The PlayState manages the active gameplay, including the player,
 * enemies, scoring, and game over condition detection.
 */
#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include <SFML/Graphics.hpp>
#include <ecs/Coordinator.hpp>
#include <ecs/EventBus.hpp>

#include "State.hpp"

#include "Events/PlayerDeadEvent.hpp"

class StateMachine;

class PlayState final : public State
{
public:
    /**
     * @brief Constructs the play state.
     * @param machine Reference to the state machine for state transitions.
     * @param window Reference to the SFML window.
     * @param coordinator Reference to the ECS coordinator.
     * @param eventBus Reference to the event bus.
     * @param font Reference to the font used for text rendering.
     */
    PlayState(StateMachine& machine, sf::RenderWindow& window, ecs::Coordinator& coordinator, ecs::EventBus& eventBus, sf::Font& font);

    /**
     * @brief Handles player death events.
     * @param event The player dead event data.
     */
    void OnPlayerDead(const PlayerDeadEvent& event);
    
    void OnEnter() override;
    void OnExit() override;
    void HandleEvent(sf::Event& event) override;
    void Update(float dt) override;
    void Render(float dt, sf::RenderWindow& window) override;

private:
    StateMachine&       m_stateMachine;      // Reference to the state machine
    sf::RenderWindow&   m_window;            // Reference to the SFML window
    ecs::Coordinator&   m_coordinator;       // Reference to the ECS coordinator
    ecs::EventBus&      m_eventBus;          // Reference to the event bus
    sf::Font&           m_font;              // Font used for text rendering
    sf::Sprite          m_background;        // Background sprite
    sf::Texture         m_texture;           // Background texture
    int                 m_currentFrame;      // Current animation frame
    int                 m_frameCount;        // Total animation frames
    float               m_frameDuration;     // Time each frame is displayed
    float               m_elapsedTime;       // Time since last frame change
    sf::RectangleShape  m_blackOverlay;      // Semi-transparent overlay
    sf::Text            m_scoreText;         // Score display text
    int                 m_score;             // Current player score
    bool                m_gameOver;          // Flag indicating game over
    bool                m_paused;            // Flag indicating pause state
    ecs::Entity         m_playerEntity;      // Reference to the player entity

    std::array<ecs::ListenerID, 3> m_listenerIDArr {};  // Event listener IDs
};

#endif //PLAYSTATE_HPP