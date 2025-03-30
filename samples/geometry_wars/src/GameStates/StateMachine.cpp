/**
* @file StateMachine.cpp
 * @brief Implementation of the StateMachine.
 */
#include "StateMachine.hpp"

void StateMachine::ChangeState(std::unique_ptr<State> newState)
{
    if (m_currentState)
        m_currentState->OnExit();

    m_currentState = std::move(newState);

    if (m_currentState)
        m_currentState->OnEnter();
}

void StateMachine::HandleEvent(sf::Event &event) const
{
    if(m_currentState)
        m_currentState->HandleEvent(event);
}

void StateMachine::Update(const float dt) const
{
    if(m_currentState)
        m_currentState->Update(dt);
}

void StateMachine::Render(const float dt, sf::RenderWindow &window) const
{
    if(m_currentState)
        m_currentState->Render(dt, window);
}
