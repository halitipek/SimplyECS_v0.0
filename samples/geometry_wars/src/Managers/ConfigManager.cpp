/**
 * @file ConfigManager.cpp
 * @brief Implementation of the ConfigManager.
 */
#include "ConfigManager.hpp"

#include <fstream>
#include <iostream>
#include <cassert>
#include <stdexcept>
bool ConfigManager::LoadConfig(const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) // Check if file opened successfully
    {
        std::cerr << "Error: Config file cannot be opened: " << filePath << "\n";
        return false;
    }

    json configJson;
    try
    {
        file >> configJson; // Parse the JSON data from the file stream
    }
    catch (json::parse_error& e)
    {
        std::cerr << "Error: JSON parsing error in file " << filePath << ":\n"
                  << e.what() << "\nat byte " << e.byte << std::endl;
        return false;
    }
    auto parseColor = [](const json& colorJson) -> sf::Color {
        return sf::Color(
            colorJson.value("r", 255),
            colorJson.value("g", 255),
            colorJson.value("b", 255),
            colorJson.value("a", 255)
        );
    };
    const auto& winJson = configJson.at("window");
    WindowConfig configWindow = {
        .width = winJson.at("width").get<unsigned int>(),
        .height = winJson.at("height").get<unsigned int>(),
        .fps = winJson.at("fps").get<unsigned int>(),
        .title = winJson.at("title").get<std::string>()
    };
    const auto& playerJson = configJson.at("player");
    PlayerConfig configPlayer = {
        .shapeRadius = playerJson.at("shapeRadius").get<float>(),
        .collisionRadius = playerJson.at("collisionRadius").get<float>(),
        .speed = playerJson.at("speed").get<float>(),
        .fillColor = parseColor(playerJson.at("fillColor")),
        .outlineColor = parseColor(playerJson.at("outlineColor")),
        .outlineThickness = playerJson.at("outlineThickness").get<float>(),
        .pointCount = playerJson.at("pointCount").get<int>(),
        .rot = playerJson.at("rot").get<float>()
    };
    const auto& enemyJson = configJson.at("enemy");
    const auto& enemyOCJson = enemyJson.at("outlineColor");
    EnemyConfig configEnemy = {
        .shapeRadius = enemyJson.at("shapeRadius").get<float>(),
        .collisionRadius = enemyJson.at("collisionRadius").get<float>(),
        .speedMin = enemyJson.at("speed").at("min").get<float>(),
        .speedMax = enemyJson.at("speed").at("max").get<float>(),
        .fillColor = parseColor(enemyJson.at("fillColor")),
        .outlineColor = {
            parseColor(enemyOCJson.at("3")),
            parseColor(enemyOCJson.at("4")),
            parseColor(enemyOCJson.at("5")),
            parseColor(enemyOCJson.at("6"))
        },
        .outlineThickness = enemyJson.at("outlineThickness").get<float>(),
        .pointCountMin = enemyJson.at("pointCount").at("min").get<int>(),
        .pointCountMax = enemyJson.at("pointCount").at("max").get<int>(),
        .pointProbabilities = enemyJson.at("pointProbabilities").get<std::vector<int>>(),
        .spawnInterval = enemyJson.at("spawnInterval").get<float>(),
        .maxEnemyCount = enemyJson.at("maxEnemyCount").get<int>(),
        .rotMin = enemyJson.at("rot").at("min").get<float>(),
        .rotMax = enemyJson.at("rot").at("max").get<float>(),
        .advancedEnemy = enemyJson.value("advancedEnemy", json::object()).get<std::unordered_map<std::string, float>>(),
        .spawnDistanceToPlayer = enemyJson.at("spawnDistanceToPlayer").get<float>()
    };
    const auto& particleJson = configJson.at("particle");
    ParticleConfig configParticle = {
        .shapeRadius = particleJson.at("shapeRadius").get<float>(),
        .speed = particleJson.at("speed").get<float>(),
        .fillColor = parseColor(particleJson.at("fillColor")),
        .outlineThickness = particleJson.at("outlineThickness").get<float>(),
        .lifeSpan = particleJson.at("lifeSpan").get<float>(),
        .rot = particleJson.at("rot").get<float>()
    };
    const auto& bulletJson = configJson.at("bullet");
    BulletConfig configBullet = {
        .shapeRadius = bulletJson.at("shapeRadius").get<float>(),
        .collisionRadius = bulletJson.at("collisionRadius").get<float>(),
        .speed = bulletJson.at("speed").get<float>(),
        .fillColor = parseColor(bulletJson.at("fillColor")),
        .outlineColor = parseColor(bulletJson.at("outlineColor")),
        .outlineThickness = bulletJson.at("outlineThickness").get<float>(),
        .pointCount = bulletJson.at("pointCount").get<std::size_t>(),
        .interval = bulletJson.at("spawnInterval").get<float>(),
        .lifeSpan = bulletJson.at("lifeSpan").get<float>()
    };
    const auto& sonarJson = configJson.at("sonar");
    SonarConfig configSonar = {
        .interval = sonarJson.at("interval").get<float>(),
        .timer = sonarJson.at("timer").get<float>(),
        .power = sonarJson.at("power").get<float>(),
        .minRadius = sonarJson.at("minRadius").get<float>(),
        .maxRadius = sonarJson.at("maxRadius").get<float>(),
        .lifeSpan = sonarJson.at("lifeSpan").get<float>(),
        .segments = sonarJson.at("segments").get<int>(),
        .color = parseColor(sonarJson.at("color"))
    };
    m_config = std::make_unique<GameConfig>(GameConfig{
        .window = configWindow,
        .player = configPlayer,
        .enemy = configEnemy,
        .bullet = configBullet,
        .particle = configParticle,
        .sonar = configSonar,
    });

    return true; // Loading successful
}
const GameConfig& ConfigManager::GetGameConfig() const
{
    assert(m_config != nullptr && "ConfigManager::GetGameConfig() called before successful LoadConfig().");
    if (!m_config) {
        throw std::runtime_error("Configuration not loaded.");
    }

    return *m_config;
}
ConfigManager gConfig;