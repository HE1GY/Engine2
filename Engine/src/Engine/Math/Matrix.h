#pragma once


#include "Vector.h"
#include <array>

namespace Engine {

    namespace Math {

        class Matrix4 {
            Matrix4();
            Matrix4& Scale(const Vector3& vector);
            Matrix4& Translate(const Vector3& vector);
            Matrix4& Rotate(const Vector3& vector, float radiant);
            Matrix4& ToIdentity();

        private:
            // Diagonals
            static constexpr size_t k_diagonal1 = 0;
            static constexpr size_t k_diagonal2 = 5;
            static constexpr size_t k_diagonal3 = 10;
            static constexpr size_t k_diagonal4 = 15;
            // Last in row
            static constexpr size_t k_last_row1 = 3;
            static constexpr size_t k_last_row2 = 7;
            static constexpr size_t k_last_row3 = 11;

            std::array<float, 4 * 4> m_values;
        };
    } // namespace Math
} // namespace Engine
