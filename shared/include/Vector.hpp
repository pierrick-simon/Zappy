/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Vector
*/

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <cmath>

namespace Shared {

    template<typename T>
    class Vector2 {
    public:
        T x;
        T y;

        Vector2() :
            x(0), y(0) {};
        Vector2(const T &x, const T &y) :
            x(x), y(y) {};

        [[nodiscard]] double norm() const
        {
            return std::sqrt(x * x + y * y);
        }

        template<typename VT>
        [[nodiscard]] double dot(const Vector2<VT> &v) const
        {
            return x * v.x + y * v.y;
        };

        template<typename VT>
        [[nodiscard]] double det(const Vector2<VT> &v) const
        {
            return x * v.y - y * v.x;
        };

        template<typename VT>
        [[nodiscard]] double angle(const Vector2<VT> &v) const
        {
            return std::atan2(det(v), dot(v));
        }

        template<typename VT>
        Vector2<T> &operator+=(const Vector2<VT> &v)
        {
            x += v.x;
            y += v.y;
            return *this;
        };

        template<typename VT>
        Vector2<T> operator*(const VT &v) const
        {
            return Vector2<T>(x * v, y * v);
        };

        Vector2<T> operator[](std::size_t nbQuarters) const
        {
            Shared::Vector2<T> r(x, y);

            for (std::size_t i = 0; i < nbQuarters; ++i)
                r = Shared::Vector2<T>(r.y, -r.x);
            return r;
        };
    };

} // namespace Shared

#endif /* !VECTIR_HPP_ */
