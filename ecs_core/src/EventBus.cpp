/**
* @file EventBus.cpp
 * @brief Implementation of the EventBus class.
 */
#include <ecs/EventBus.hpp>
#include <utility>

namespace ecs
{
    EventBus::EventBus()
    : m_nextListenerID(1) // Start IDs from 1 (0 is reserved as invalid)
    {
    }

    void EventBus::ProcessEvents()
    {
        // Process events in a separate queue to allow for new events to be queued during processing
        auto currentQueue = std::move(m_eventQueue);
        m_eventQueue.clear(); // Clear the main queue

        for(const auto& eventItem : currentQueue)
        {
            ProcessEvent(eventItem);
        }
    }

    void EventBus::UnsubscribeAll()
    {
        m_listeners.clear();
        m_eventQueue.clear();
    }

    void EventBus::ProcessEvent(const ItemEvent& item)
    {
        const auto it = m_listeners.find(item.type);
        Debug::Assert(it != m_listeners.end(),
            "EventBus::RemoveListener - No listener exist for this event type: %s",
            item.type.name());

        // Call all registered listeners
        auto listenersToCall = it->second;
        for(auto &listener : listenersToCall)
        {
            listener.callback(item.event);
        }
    }
}