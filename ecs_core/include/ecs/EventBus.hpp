/**
 * @file EventBus.hpp
 * @brief Event system for decoupled communication between systems.
 *
 * The EventBus allows systems to communicate without direct dependencies
 * through a publish-subscribe pattern.
 */
#ifndef EVENTBUS_HPP
#define EVENTBUS_HPP

#include <any>
#include <typeindex>
#include <unordered_map>
#include <functional>
#include <vector>
#include <algorithm>
#include "Types.hpp"
#include "ecs/Debug.hpp"

namespace ecs {

    class EventBus
    {
    public:
        EventBus();
        ~EventBus() = default;

        /**
         * @brief Adds a listener for a specific event type.
         * @tparam EventType The event type to listen for.
         * @param listener The callback function to invoke when event occurs.
         * @return Unique ID for the listener (used for removal).
         */
        template<typename EventType>
        ListenerID AddListener(std::function<void(const EventType&)> listener);

        /**
         * @brief Removes a listener for a specific event type.
         * @tparam EventType The event type the listener was registered for.
         * @param listenerID The ID of the listener to remove.
         */
        template<typename EventType>
        void RemoveListener(ListenerID listenerID);

        /**
         * @brief Emits an event to all registered listeners.
         * @tparam EventType The type of event to emit.
         * @param event The event data to send.
         * @param fast If true, processes the event immediately; otherwise queues it.
         */
        template<typename EventType>
        void Emit(const EventType &event, bool fast = false);

        /**
         * @brief Processes all queued events.
         *
         * This should be called once per frame to ensure events are processed
         * at a controlled time.
         */
        void ProcessEvents();

        /**
         * @brief Removes all event listeners.
         */
        void UnsubscribeAll();

    private:
        /**
         * @brief Internal structure to store listener callbacks.
         */
        struct ItemListener {
            ListenerID id;  // Unique ID for this listener
            std::function<void(const std::any&)> callback;  // Type-erased callback

            ItemListener(const ListenerID id, std::function<void(const std::any&)> cb)
            : id(id)
            , callback(std::move(cb))
            {
            }
        };

        /**
         * @brief Internal structure to store event data.
         */
        struct ItemEvent {
            std::type_index type;  // The type of the event
            std::any event;        // The event data

            ItemEvent(const std::type_index t, std::any e)
            : type(t)
            , event(std::move(e))
            {
            }
        };

        ListenerID m_nextListenerID;  // Next available listener ID
        std::vector<ItemEvent> m_eventQueue;  // Queue of pending events
        std::unordered_map<std::type_index, std::vector<ItemListener>> m_listeners;  // Maps from event type to listeners

        /**
         * @brief Processes a single event.
         * @param item The event to process.
         */
        void ProcessEvent(const ItemEvent& item);
    };

} // namespace ecs
#include "../src/EventBus.tpp"

#endif //EVENTBUS_HPP