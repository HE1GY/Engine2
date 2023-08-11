#pragma once

namespace Engine {

    namespace Math {
        struct Vector2 {
            float x, y;
            float Length() const;
            Vector2 operator-() const;
        };

        Vector2 operator+(const Vector2& a, const Vector2& b);
        Vector2 operator-(const Vector2& a, const Vector2& b);
        float Dot(const Vector2& a, const Vector2& b);


        struct Vector3 {
            float x, y, z;
            float Length() const;
            Vector3 operator-() const;
        };

        Vector3 operator+(const Vector3& a, const Vector3& b);
        Vector3 operator-(const Vector3& a, const Vector3& b);
        float Dot(const Vector3& a, const Vector3& b);
        Vector3 Cross(const Vector3& a, const Vector3& b);
    } // namespace Math
} // namespace Engine
