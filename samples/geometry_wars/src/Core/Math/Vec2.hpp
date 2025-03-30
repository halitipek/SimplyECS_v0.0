/**
 * @file Vec2.hpp
 * @brief 2D vector class with common vector operations.
 *
 * Provides a templated 2D vector implementation with methods for
 * vector math, normalization, rotation, and other common operations.
 */
#ifndef VEC2_HPP
#define VEC2_HPP

#include <cmath>
#include <algorithm>

constexpr float PI_F = 3.14159265358979323846f;
constexpr float DegToRad(const float degrees) { return degrees * PI_F / 180.0f; }
constexpr float RadToDeg(const float radians) { return radians * 180.0f / PI_F; }

/**
 * @brief A 2D vector class with comprehensive vector operations.
 * @tparam T The numeric type for vector components (typically float).
 */
template<class T>
class Vec2 {
public:
    T x, y;  // Vector components

    /**
     * @brief Constructs a vector with optional components.
     * @param xin X component value.
     * @param yin Y component value.
     */
    Vec2(const T xin = T(), const T yin = T())
    : x(xin)
    , y(yin)
    {
    };

    // Comparison operators
    bool operator==(const Vec2<T>& rhs) const { return x == rhs.x && y == rhs.y; }
    bool operator!=(const Vec2<T>& rhs) const { return !(*this == rhs); }

    // Assignment operators
    Vec2<T>& operator+=(const Vec2<T>& rhs) { x += rhs.x; y += rhs.y; return *this; }
    Vec2<T>& operator-=(const Vec2<T>& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
    Vec2<T>& operator*=(const T scalar)     { x *= scalar; y *= scalar; return *this; }
    Vec2<T>& operator/=(const T scalar)     {
        assert(scalar != T(0) && "Division by zero in Vec2::operator/=");
        x /= scalar; y /= scalar; return *this;
    }

    // Unary operators
    Vec2<T> operator-() const { return Vec2<T>(-x, -y); }

    // Binary operators (defined as friend functions)
    friend Vec2<T> operator+(Vec2<T> lhs, const Vec2<T>& rhs) { lhs += rhs; return lhs; }
    friend Vec2<T> operator-(Vec2<T> lhs, const Vec2<T>& rhs) { lhs -= rhs; return lhs; }
    friend Vec2<T> operator*(Vec2<T> lhs, const T scalar)     { lhs *= scalar; return lhs; }
    friend Vec2<T> operator*(const T scalar, Vec2<T> rhs)     { rhs *= scalar; return rhs; }
    friend Vec2<T> operator/(Vec2<T> lhs, const T scalar)     { lhs /= scalar; return lhs; }

    /**
     * @brief Calculates the squared length of the vector.
     * @return The squared length value.
     */
    float LengthSquared() const { return static_cast<float>(x * x + y * y); }

    /**
     * @brief Calculates the length of the vector.
     * @return The length value.
     */
    float Length() const { return std::sqrt(LengthSquared()); }

    /**
     * @brief Calculates the squared distance to another vector.
     * @param target The target vector.
     * @return The squared distance value.
     */
    float DistanceSquared(const Vec2<T>& target) const {
        T dx = x - target.x;
        T dy = y - target.y;
        return static_cast<float>(dx * dx + dy * dy);
    }

    /**
     * @brief Calculates the distance to another vector.
     * @param target The target vector.
     * @return The distance value.
     */
    float Distance(const Vec2<T>& target) const {
        return std::sqrt(DistanceSquared(target));
    }

    /**
     * @brief Clamps the vector components to be within specified bounds.
     * @param min The minimum bound vector.
     * @param max The maximum bound vector.
     */
    void Clamp(const Vec2<T>& min, const Vec2<T>& max) {
        x = std::clamp(x, min.x, max.x);
        y = std::clamp(y, min.y, max.y);
    }

    /**
     * @brief Returns a clamped copy of this vector.
     * @param min The minimum bound vector.
     * @param max The maximum bound vector.
     * @return The clamped vector.
     */
    Vec2<T> Clamped(const Vec2<T>& min, const Vec2<T>& max) const {
        Vec2<T> result(*this);
        result.Clamp(min, max);
        return result;
    }

    /**
     * @brief Normalizes this vector to unit length.
     */
    void Normalize() {
        float len = Length();
        if (len > T(0)) // Check against T(0)
        {
            float invLen = 1.0f / len;
            x = static_cast<T>(x * invLen);
            y = static_cast<T>(y * invLen);
        }
    }

    /**
     * @brief Returns a normalized copy of this vector.
     * @return The normalized vector.
     */
    Vec2<T> Normalized() const {
        Vec2<T> result(*this);
        result.Normalize();
        return result;
    }

    /**
     * @brief Rotates this vector by the specified angle in degrees.
     * @param degrees The rotation angle in degrees.
     */
    void RotateDegrees(const float degrees) {
        RotateRadians(DegToRad(degrees));
    }

    /**
     * @brief Rotates this vector by the specified angle in radians.
     * @param radians The rotation angle in radians.
     */
    void RotateRadians(const float radians) {
        const float c = std::cos(radians);
        const float s = std::sin(radians);
        const T newX = static_cast<T>(c * x - s * y);
        const T newY = static_cast<T>(s * x + c * y);
        x = newX;
        y = newY;
    }

    /**
     * @brief Returns a copy of this vector rotated by the specified angle in degrees.
     * @param degrees The rotation angle in degrees.
     * @return The rotated vector.
     */
    Vec2<T> RotatedDegrees(const float degrees) const {
        return RotatedRadians(DegToRad(degrees));
    }

    /**
     * @brief Returns a copy of this vector rotated by the specified angle in radians.
     * @param radians The rotation angle in radians.
     * @return The rotated vector.
     */
    Vec2<T> RotatedRadians(const float radians) const {
        Vec2<T> result(*this);
        result.RotateRadians(radians);
        return result;
    }

    /**
     * @brief Calculates the dot product with another vector.
     * @param other The other vector.
     * @return The dot product value.
     */
    float Dot(const Vec2<T>& other) const {
        return static_cast<float>(x * other.x + y * other.y);
    }

    /**
     * @brief Calculates the angle between this vector and another vector.
     * @param other The other vector.
     * @return The angle in radians.
     */
    float Angle(const Vec2<T>& other) const {
        float dot = Dot(other);
        float lenSq1 = LengthSquared();
        float lenSq2 = other.LengthSquared();
        if (lenSq1 == 0 || lenSq2 == 0) return 0.0f;
        float cosTheta = dot / std::sqrt(lenSq1 * lenSq2);
        cosTheta = std::clamp(cosTheta, -1.0f, 1.0f);
        return std::acos(cosTheta);
    }
};

#endif //VEC2_HPP