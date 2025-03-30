/**
 * @file DenseMap.hpp
 * @brief A cache-friendly associative container optimized for fast iteration.
 *
 * DenseMap provides O(1) insertions, lookups, and removals while maintaining
 * data in a contiguous memory layout for better cache performance during iteration.
 * It's particularly useful for storing and accessing component data.
 */
#ifndef DENSEMAP_HPP
#define DENSEMAP_HPP

#include <vector>
#include <unordered_map>
#include <cstddef>
#include "Debug.hpp"

namespace ecs {

    template <typename Key, typename Value = Key>
    class DenseMap
    {
        std::unordered_map<Key, std::size_t> m_keyToIndex;  // Maps keys to their index in the dense array
        std::vector<Key>                     m_indexToKey;  // Maps indices to their keys
        std::vector<Value>                   m_data;        // The actual data, tightly packed

    public:
        DenseMap() = default;

        /**
         * @brief Inserts a key using the key as its value.
         * @param key The key to insert.
         */
        void Insert(const Key& key) {
            Insert(key, key); // Assumes Value is Key or implicitly convertible
        }

        /**
         * @brief Inserts a key-value pair or updates if the key already exists.
         * @param key The key to insert or update.
         * @param value The value to associate with the key.
         */
        void Insert(const Key& key, const Value& value) {
            Debug::Assert(!m_keyToIndex.contains(key),
                "DenseMap::Insert - Key already exists.");

            m_keyToIndex[key] = m_data.size();
            m_indexToKey.push_back(key);
            m_data.push_back(value);
        }

        /**
         * @brief Updates the value for an existing key.
         * @param key The key to update.
         * @param value The new value.
         */
        void Update(const Key& key, const Value& value)
        {
            Debug::Assert(m_keyToIndex.contains(key),
                "DenseMap::Update - Key does not exists.");

            std::size_t indexOfUpdated = m_keyToIndex.at(key);
            m_data[indexOfUpdated] = value;
        }

        /**
         * @brief Removes a key-value pair.
         * @param key The key to remove.
         *
         * Uses the "swap and pop" technique to maintain contiguous storage.
         */
        void Erase(const Key& key)
        {
            Debug::Assert(m_keyToIndex.contains(key),
                "DenseMap::Erase - Key does not exists.");

            std::size_t indexOfRemoved   = m_keyToIndex.at(key);
            std::size_t indexOfLast      = m_data.size() - 1;
            Key keyOfLast                = m_indexToKey[indexOfLast];
            m_data[indexOfRemoved]       = m_data[indexOfLast];
            m_indexToKey[indexOfRemoved] = keyOfLast;
            m_keyToIndex[keyOfLast]      = indexOfRemoved;
            m_keyToIndex.erase(key);
            m_indexToKey.pop_back();
            m_data.pop_back();
        }

        /**
         * @brief Checks if a key exists in the map.
         * @param key The key to check.
         * @return True if the key exists, false otherwise.
         */
        bool Contains(const Key& key) const {
            return m_keyToIndex.contains(key);
        }

        /**
         * @brief Gets the value associated with a key (const version).
         * @param key The key to look up.
         * @return Const reference to the value.
         */
        const Value& GetValue(const Key& key) const {
            Debug::Assert(Contains(key),
                "DenseMap::GetValue(const) - Key does not exists.");

             return m_data[m_keyToIndex.find(key)->second];
        }

        /**
         * @brief Gets the value associated with a key.
         * @param key The key to look up.
         * @return Reference to the value.
         */
        Value& GetValue(const Key& key) {
            Debug::Assert(Contains(key),
                "DenseMap::GetValue - Key does not exists.");

            return m_data[m_keyToIndex.find(key)->second];
        }

        /**
         * @brief Gets the underlying data vector (const version).
         * @return Const reference to the data vector.
         */
        const std::vector<Value>& GetDataVector() const {
            return m_data;
        }

        /**
         * @brief Gets the underlying data vector.
         * @return Reference to the data vector.
         */
        std::vector<Value>& GetDataVector() {
            return m_data;
        }

        /**
         * @brief Checks if the map is empty.
         * @return True if empty, false otherwise.
         */
        bool IsEmpty() const { return m_data.empty(); }

        /**
         * @brief Gets the number of elements in the map.
         * @return Size of the map.
         */
        std::size_t Size() const { return m_data.size(); }

        /**
         * @brief Clears all elements from the map.
         */
        void Clear() {
             m_data.clear();
             m_keyToIndex.clear();
             m_indexToKey.clear();
        }

        // Pair structure used for iteration
        struct Pair {
            const Key& first;  // Key reference
            Value&     second; // Value reference
        };

        // Iterator implementation for the DenseMap
        class Iterator
        {
        public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = Pair;
            using pointer           = Pair*;
            using reference         = Pair;

            Iterator(DenseMap* container, std::size_t index)
                : m_container(container), m_index(index) { }

            Iterator& operator++() { ++m_index; return *this; }
            Iterator operator++(int) { Iterator temp = *this; ++(*this); return temp; }

            bool operator==(const Iterator& other) const {
                return (m_container == other.m_container) && (m_index == other.m_index);
            }

            bool operator!=(const Iterator& other) const {
                return !(*this == other);
            }

            Pair operator*() const {
                Debug::Assert(m_index < m_container->Size(),
                    "DenseMap>Iterator::Pair operator* - Iterator out of bounds");

                return Pair {
                    m_container->m_indexToKey.at(m_index),
                    m_container->m_data.at(m_index)
                };
            }

        private:
            DenseMap* m_container;  // Pointer to the container
            std::size_t m_index;    // Current index in the vectors
        };

        /**
         * @brief Returns an iterator to the beginning of the map.
         */
        Iterator begin() { return Iterator(this, 0); }

        /**
         * @brief Returns an iterator to the end of the map.
         */
        Iterator end() { return Iterator(this, m_data.size()); }
    };

} // namespace ecs

#endif //DENSEMAP_HPP