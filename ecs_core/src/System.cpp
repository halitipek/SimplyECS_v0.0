/**
* @file System.cpp
 * @brief Implementation of the System class.
 */
#include <ecs/System.hpp>

namespace ecs {
    bool System::HasEntity(const Entity entity)
    {
        return m_entities.Contains(entity);
    }

    void System::AddEntity(const Entity entity)
    {
        if(m_entities.Contains(entity))
        {
            return;
        }

        m_entities.Insert(entity);
    }

    void System::RemoveEntity(const Entity entity)
    {
        if(!m_entities.Contains(entity))
        {
            return;
        }

        m_entities.Erase(entity);
    }
}