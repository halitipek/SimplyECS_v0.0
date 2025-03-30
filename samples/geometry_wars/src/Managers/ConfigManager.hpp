/**
 * @file ConfigManager.hpp
 * @brief Manages game configuration loaded from JSON files.
 *
 * The ConfigManager loads and stores configuration settings for various
 * game elements such as window properties, player attributes, enemy behavior,
 * and visual effects.
 */
#ifndef CONFIGMANAGER_HPP
#define CONFIGMANAGER_HPP

#include <memory>
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <SFML/Graphics/Color.hpp>
#include "../Core/json.hpp"

using json = nlohmann::json;

/**
 * @brief Window configuration settings.
 */
struct WindowConfig
{
    unsigned int width;   // Window width in pixels
    unsigned int height;  // Window height in pixels
    unsigned int fps;     // Target frames per second
    std::string title;    // Window title
};

/**
 * @brief Player entity configuration settings.
 */
struct PlayerConfig
{
    float shapeRadius;           // Visual radius of player shape
    float collisionRadius;       // Collision detection radius
    float speed;                 // Movement speed
    sf::Color fillColor;         // Fill color of player shape
    sf::Color outlineColor;      // Outline color of player shape
    float outlineThickness;      // Outline thickness in pixels
    int pointCount;              // Number of points/vertices (also used as initial health)
    float rot;                   // Rotation speed
};

/**
 * @brief Enemy entity configuration settings.
 */
struct EnemyConfig
{
    float shapeRadius;                             // Visual radius of enemy shape
    float collisionRadius;                         // Collision detection radius
    float speedMin;                                // Minimum movement speed
    float speedMax;                                // Maximum movement speed
    sf::Color fillColor;                           // Fill color of enemy shape
    std::array<sf::Color, 4> outlineColor;         // Outline colors for different enemy tiers
    float outlineThickness;                        // Outline thickness in pixels
    int pointCountMin;                             // Minimum vertices (also min health)
    int pointCountMax;                             // Maximum vertices (also max health)
    std::vector<int> pointProbabilities;           // Probability distribution for point counts
    float spawnInterval;                           // Time between enemy spawns
    int maxEnemyCount;                             // Max number of enemies allowed on screen
    float rotMin;                                  // Minimum rotation speed
    float rotMax;                                  // Maximum rotation speed
    std::unordered_map<std::string, float> advancedEnemy;  // Advanced enemy behavior parameters
    float spawnDistanceToPlayer;                   // Minimum spawn distance from player
};

/**
 * @brief Bullet entity configuration settings.
 */
struct BulletConfig
{
    float shapeRadius;           // Visual radius of bullet shape
    float collisionRadius;       // Collision detection radius
    float speed;                 // Movement speed
    sf::Color fillColor;         // Fill color of bullet shape
    sf::Color outlineColor;      // Outline color of bullet shape
    float outlineThickness;      // Outline thickness in pixels
    std::size_t pointCount;      // Number of vertices for the bullet shape
    float interval;              // Cooldown between firing bullets
    float lifeSpan;              // How long the bullet exists before disappearing
};

/**
 * @brief Particle effect configuration settings.
 */
struct ParticleConfig
{
    float shapeRadius;           // Visual radius of particle shape
    float speed;                 // Movement speed
    sf::Color fillColor;         // Fill color of particle shape
    float outlineThickness;      // Outline thickness in pixels
    float lifeSpan;              // How long the particle exists before disappearing
    float rot;                   // Rotation speed
};

/**
 * @brief Sonar/sound wave configuration settings.
 */
struct SonarConfig
{
    float interval;              // Cooldown for the sonar ability
    float timer;                 // Initial timer value
    float power;                 // How strongly it pushes enemies
    float minRadius;             // Starting radius of the wave
    float maxRadius;             // Maximum radius the wave reaches
    float lifeSpan;              // How long the wave effect lasts
    int segments;                // Number of vertices for the wave's shape
    sf::Color color;             // Color of the wave visual
};

/**
 * @brief Complete game configuration.
 */
struct GameConfig
{
    WindowConfig window;     // Window settings
    PlayerConfig player;     // Player entity settings
    EnemyConfig enemy;       // Enemy entity settings
    BulletConfig bullet;     // Bullet entity settings
    ParticleConfig particle; // Particle effect settings
    SonarConfig sonar;       // Sonar ability settings
};

/**
 * @brief Manages loading and accessing game configuration.
 */
class ConfigManager
{
public:
    ConfigManager() = default;

    /**
     * @brief Loads configuration from a JSON file.
     * @param filePath Path to the configuration file.
     * @return True if loading was successful, false otherwise.
     */
    bool LoadConfig(const std::string &filePath);

    /**
     * @brief Gets the loaded game configuration.
     * @return Reference to the game configuration.
     * @throws std::runtime_error if configuration was not loaded.
     */
    const GameConfig& GetGameConfig() const;

private:
    std::unique_ptr<GameConfig> m_config;  // Loaded configuration data
};

// Global instance of the configuration manager
extern ConfigManager gConfig;

#endif //CONFIGMANAGER_HPP