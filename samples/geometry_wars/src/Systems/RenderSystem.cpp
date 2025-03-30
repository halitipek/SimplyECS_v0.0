/**
* @file RenderSystem.cpp
 * @brief Implementation of the RenderSystem.
 */
#include "RenderSystem.hpp"

#include <cmath>
#include <random>

#include "Components/GlowComponent.hpp"
#include "Components/LightAuraComponent.hpp"
#include "Components/ShapeComponent.hpp"
#include "Components/SonarWeaponComponent.hpp"
#include "Components/TransformComponent.hpp"
#include "Core/Helpers.hpp"

RenderSystem::RenderSystem(sf::RenderWindow& window, ecs::Coordinator& coordinator)
: m_window(window)
, m_coordinator(coordinator)
{
}

void RenderSystem::Update(const float dt)
{
    for (auto [e, v] : m_entities)
    {
        auto& transform = m_coordinator.GetComponent<TransformComponent>(e);
        auto& shapeData = m_coordinator.GetComponent<ShapeComponent>(e);

        if (m_coordinator.HasComponent<GlowComponent>(e))
        {
            auto& glowData = m_coordinator.GetComponent<GlowComponent>(e);
            glowData.timer -= dt;

            if (glowData.timer <= 0.f)
            {
                glowData.hue += 5.f;
                if (glowData.hue >= 360.f)
                    glowData.hue -= 360.f;

                glowData.fillColor  = Helpers::HSVtoRGB(glowData.hue, 1.0f, 1.0f, static_cast<sf::Uint8>(125.f));
                glowData.timer      = glowData.interval;

                if(m_coordinator.HasComponent<SonarWeaponComponent>(e))
                {
                    auto& sComp = m_coordinator.GetComponent<SonarWeaponComponent>(e);
                    if(sComp.timer <= 0.f)
                    {
                        glowData.fillColor = sf::Color::White;
                    }
                }
            }

            sf::CircleShape circle(glowData.radius, shapeData.points);
            circle.setFillColor(glowData.fillColor);
            circle.setOutlineColor(glowData.fillColor);
            circle.setOutlineThickness(glowData.outlineThickness);
            circle.setOrigin(glowData.originX, glowData.originY);

            circle.setPosition(transform.position.x, transform.position.y);
            circle.setRotation(transform.rotation);

            m_window.draw(circle);
        }

        if (m_coordinator.HasComponent<LightAuraComponent>(e))
        {
            auto& auraComp = m_coordinator.GetComponent<LightAuraComponent>(e);

            auraComp.timer -= dt;

            if (auraComp.timer <= 0.f)
            {
                auraComp.hue += 5.f;
                if (auraComp.hue >= 360.f)
                    auraComp.hue -= 360.f;

                auraComp.color  = Helpers::HSVtoRGB(auraComp.hue, 1.0f, 1.0f, 90.f);
                auraComp.timer  = auraComp.interval;
            }

            sf::VertexArray aura = CreateVertexCircleGradient(transform.position.x, transform.position.y,
                auraComp.radius, auraComp.color, auraComp.segments, auraComp.color.a, 0, 8.f);
            m_window.draw(aura);
        }

        if (shapeData.shapeType == ShapeType::Circle)
        {
            sf::CircleShape circle(shapeData.radius, shapeData.points);
            circle.setFillColor(shapeData.fillColor);
            circle.setOutlineColor(shapeData.outlineColor);
            circle.setOutlineThickness(shapeData.outlineThickness);
            circle.setOrigin(shapeData.originX, shapeData.originY);

            circle.setPosition(transform.position.x, transform.position.y);
            circle.setRotation(transform.rotation);

            m_window.draw(circle);
        }

        if (shapeData.shapeType == ShapeType::Vertex)
        {
            auto& [ segments, color, radius ] = shapeData.vertexShapeData;
            sf::VertexArray soundWave = CreateVertexCircleGradient(transform.position.x, transform.position.y,
                radius, color, segments, 0, color.a, 12.f);
            m_window.draw(soundWave);
        }
    }
}

float randomRadius(float baseRadius, float variance)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(baseRadius - variance, baseRadius + variance);
    return dist(gen);
}

sf::VertexArray RenderSystem::CreateVertexCircleGradient(float positionX, float positionY, float radius, sf::Color color, int segments, int startAlpha, int endAlpha, float variance)
{
    sf::VertexArray vertices(sf::TriangleFan, segments + 2);

    vertices[0].position.x = positionX;
    vertices[0].position.y = positionY;
    vertices[0].color = sf::Color(color.r, color.g, color.b, startAlpha);

    for (int i = 0; i <= segments; ++i)
    {
        float angle = i * 2 * 3.14159265f / segments;

        float variedRadius = randomRadius(radius, variance);

        float x = positionX + std::cos(angle) * variedRadius;
        float y = positionY + std::sin(angle) * variedRadius;

        vertices[i + 1].position = sf::Vector2f(x, y);
        vertices[i + 1].color = sf::Color(color.r, color.g, color.b, endAlpha);
    }

    return vertices;
}