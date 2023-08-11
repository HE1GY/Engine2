#include "Vector.h"

#include <valarray>

namespace Engine {

    namespace Math {
        ////////////////////////////////////////////////
        /**Vector2*/
        ///////////////////////////////////////////////
        Vector2 Vector2::operator-() const {
            return {-x, -y};
        }
        float Vector2::Length() const {
            return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
        }

        Vector2 operator+(const Vector2& a, const Vector2& b) {
            return {a.x + b.x, a.y + b.y};
        }

        Vector2 operator-(const Vector2& a, const Vector2& b) {
            return a + (-b);
        }
        float Dot(const Vector2& a, const Vector2& b) {
            return a.x * b.x + a.y * b.y;
        }


        ////////////////////////////////////////////////
        /**Vector3*/
        ///////////////////////////////////////////////


        float Vector3::Length() const {
            return static_cast<float>(std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2)));
        }
        Vector3 Vector3::operator-() const {
            return {-x, -y, -z};
        }
        Vector3 operator+(const Vector3& a, const Vector3& b) {
            return {a.x + b.x, a.y + b.y, a.z + b.z};
        }
        Vector3 operator-(const Vector3& a, const Vector3& b) {
            return a + (-b);
        }
        float Dot(const Vector3& a, const Vector3& b) {
            return a.x * b.x + a.y * b.y + a.z + b.z;
        }
        Vector3 Cross(const Vector3& a, const Vector3& b) {
            return {
                a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x,
            };
        }
    } // namespace Math
} // namespace Engine
