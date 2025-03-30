/**
 * @file EventBus.tpp
 * @brief Template implementation of EventBus methods.
 */
#pragma once

#include <functional>
#include <any>
#include <typeindex>
#include <utility>
#include <algorithm>
#include <vector>

namespace ecs {

    template<typename EventType>
    ListenerID EventBus::AddListener(std::function<void(const EventType&)> listener)
    {
        // Get the type index for this event type
        std::type_index eventTypeIndex(typeid(EventType));

        // Assign a unique ID to this listener
        ListenerID newListenerID = m_nextListenerID++;

        // Create a type-erased callback that will cast the std::any back to the correct type
        ItemListener listenerItem(
            newListenerID,
            [fn = std::move(listener)](const std::any& ev) { // Capture listener by move
                fn(std::any_cast<const EventType&>(ev));
            }
        );

        // Add to the listeners for this event type
        auto& listenerList = m_listeners[eventTypeIndex];
        listenerList.push_back(std::move(listenerItem)); // Move the ItemListener

        return newListenerID;
    }

    template<typename EventType>
    void EventBus::RemoveListener(const ListenerID listenerID)
    {
        const std::type_index eventTypeIndex(typeid(EventType));
        const auto it = m_listeners.find(eventTypeIndex);

        Debug::Assert(it != m_listeners.end(),
            "EventBus::RemoveListener - No listener exist for this event type: Type = %s, ListenerID = %zu",
            eventTypeIndex.name(), listenerID);

        auto listenerVec = it->second;

        auto newEnd = std::remove_if(listenerVec.begin(), listenerVec.end(),
            [listenerID](const ItemListener &l){ return l.id == listenerID; });

        Debug::Assert(newEnd != listenerVec.end(),
            "EventBus::RemoveListener - Listener does not exist: Type = %s, ListenerID = %zu",
            eventTypeIndex.name(), listenerID);

        listenerVec.erase(newEnd, listenerVec.end());

        // Clean up empty listener vectors
        if (listenerVec.empty()) {
            m_listeners.erase(it);
        }
    }

    template<typename EventType>
    void EventBus::Emit(const EventType &event, const bool fast)
    {
        std::type_index eventTypeIndex(typeid(EventType));
        ItemEvent item(eventTypeIndex, event);

        if(fast)
        {
            // Process the event immediately
            ProcessEvent(item);
        }
        else
        {
            // Queue the event for later processing
            m_eventQueue.push_back(std::move(item));
        }
    }
}