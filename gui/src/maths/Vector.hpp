/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef VECTOR3_HPP
    #define VECTOR3_HPP

    #include <algorithm>
    #include <cmath>
    #include <type_traits>

    #include "Matrix.hpp"

namespace Maths {
    template<typename T>
    concept Scalar = std::is_arithmetic_v<std::remove_cvref_t<T>>;

    template<std::size_t Dim, typename Type>
    class Vector : public Matrix<Dim, 1, Type> {
    public:
        template<typename... Args>
            requires(sizeof...(Args) == Dim)
        explicit constexpr Vector(Args &&...args) :
            Matrix<Dim, 1, Type> {static_cast<Type>(args)...}
        {
        }

        explicit constexpr Vector() :
            Matrix<Dim, 1, Type>(0)
        {
        }

        Vector(const Matrix<Dim, 1, Type> &matrix) :
            Matrix<Dim, 1, Type>(matrix.getMatrix())
        {
        }

        const Type &operator[](size_t index) const
        {
            return (*this)(index, 0);
        }

        Type &operator[](size_t index)
        {
            return (*this)(index, 0);
        }

        template<typename OtherType>
            requires Scalar<OtherType>
        Vector operator*(const OtherType &other) const
        {
            Vector result;
            for (size_t i = 0; i < Dim; ++i)
                result[i] = (*this)[i] * other;
            return result;
        }

        Vector operator*(const Vector &other) const
        {
            Vector result;
            for (size_t i = 0; i < Dim; ++i)
                result[i] = (*this)[i] * other[i];
            return result;
        }

        [[nodiscard]] double norm() const
        {
            double sum = 0;

            for (size_t i = 0; i < Dim; ++i)
                sum += (*this)[i] * (*this)[i];

            return std::sqrt(sum);
        }

        [[nodiscard]] double norm_squared() const
        {
            double sum = 0;

            for (size_t i = 0; i < Dim; ++i)
                sum += (*this)[i] * (*this)[i];

            return sum;
        }

        [[nodiscard]] Vector normalized() const
        {
            Vector normalized = *this;
            double length = this->norm();

            if (length == 0.0)
                return Vector {};

            normalized /= length;
            return normalized;
        }

        [[nodiscard]] double distance(const Vector &rhs) const
        {
            Vector delta = rhs - *this;
            return delta.norm();
        }

        [[nodiscard]] double dot(const Vector &rhs) const
        {
            double result = 0;

            for (size_t i = 0; i < Dim; ++i)
                result += (*this)[i] * rhs[i];
            return result;
        }

        [[nodiscard]] double getAngle(const Vector &other) const
        {
            double denom = this->norm() * other.norm();
            if (denom <= std::numeric_limits<double>::epsilon())
                return 0.0;

            double cosv = this->dot(other) / denom;
            cosv = std::clamp(cosv, -1.0, 1.0);
            return std::acos(cosv);
        }

        static Vector lerp(const Vector &min, const Vector &max, double t)
        {
            return min * (1.0 - t) + max * t;
        }

        static Vector clampedLerp(
            const Vector &min, const Vector &max, double t)
        {
            return lerp(min, max, std::clamp(t, 0.0, 1.0));
        }

        [[nodiscard]] Vector crossProduct(const Vector &rhs) const
            requires(Dim == 3)
        {
            return Vector((*this)[1] * rhs[2] - (*this)[2] * rhs[1],
                (*this)[2] * rhs[0] - (*this)[0] * rhs[2],
                (*this)[0] * rhs[1] - (*this)[1] * rhs[0]);
        }

        Vector operator-() const
        {
            Vector result;

            for (size_t i = 0; i < Dim; ++i)
                result[i] = -(*this)[i];
            return result;
        }

        Vector operator-(const Vector &rhs) const
        {
            return Matrix<Dim, 1, Type>::operator-(rhs);
        }

        [[nodiscard]] const Type &getX() const
            requires(Dim >= 1 && Dim <= 4)
        {
            return (*this)[0];
        }

        Type &getX()
            requires(Dim >= 1 && Dim <= 4)
        {
            return (*this)[0];
        }

        [[nodiscard]] const Type &getY() const
            requires(Dim >= 2 && Dim <= 4)
        {
            return (*this)[1];
        }

        Type &getY()
            requires(Dim >= 2 && Dim <= 4)
        {
            return (*this)[1];
        }

        [[nodiscard]] const Type &getZ() const
            requires(Dim == 3 || Dim == 4)
        {
            return (*this)[2];
        }

        Type &getZ()
            requires(Dim == 3 || Dim == 4)
        {
            return (*this)[2];
        }

        [[nodiscard]] const Type &getW() const
            requires(Dim == 4)
        {
            return (*this)[3];
        }

        Type &getW()
            requires(Dim == 4)
        {
            return (*this)[3];
        }

        inline static const Vector ZERO {};
    };

    template<typename Type>
    using Vector3 = Vector<3, Type>;

    using Vector3D = Vector3<double>;
    using Vector3U = Vector3<unsigned int>;
    using Vector3I = Vector3<int>;

    static const Vector3D FORWARD {0, 0, 1};
    static const Vector3D BACKWARD {0, 0, -1};
    static const Vector3D LEFT {-1, 0, 0};
    static const Vector3D RIGHT {1, 0, 0};
    static const Vector3D UP {0, 1, 0};
    static const Vector3D DOWN {0, -1, 0};

    template<typename Type>
    using Vector2 = Vector<2, Type>;

    using Vector2D = Vector2<double>;
    using Vector2U = Vector2<unsigned int>;
    using Vector2I = Vector2<int>;
} // namespace Maths

#endif
