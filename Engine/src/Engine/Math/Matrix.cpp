#include "Matrix.h"


namespace Engine {
    namespace Math {
        Matrix4::Matrix4() : m_values{} {
            ToIdentity();
        }
        Matrix4& Matrix4::Scale(const Vector3& vector) {
            m_values[k_diagonal1] *= vector.x;
            m_values[k_diagonal2] *= vector.y;
            m_values[k_diagonal3] *= vector.z;
            return *this;
        }
        Matrix4& Matrix4::Translate(const Vector3& vector) {
            m_values[k_last_row1] += vector.x;
            m_values[k_last_row2] += vector.y;
            m_values[k_last_row3] += vector.z;
            return *this;
        }
        Matrix4& Matrix4::Rotate(const Vector3& vector, float radiant) {


            return *this;
        }
        Matrix4& Matrix4::ToIdentity() {
            m_values.fill(0);
            m_values[k_diagonal1] = 1;
            m_values[k_diagonal2] = 1;
            m_values[k_diagonal3] = 1;
            m_values[k_diagonal4] = 1;
            return *this;
        }
    } // namespace Math
} // namespace Engine
