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

        Vector2() = default;
        Vector2(const T &x, const T &y) :
            x(x), y(y) {};
        
        T norm() const
        {
            return std::sqrt(x * x + y * y);
        }

        template<typename VT>
        T angle(const Vector2<VT> &v) const
        {
            return std::acos((*this * v) / (norm() * v.norm()));
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

        template<typename VT>
        T operator*(const Vector2<VT> &v) const
        {
            return std::sqrt(x * v.x + y * v.y);
        };
    };

} // namespace Shared

#endif /* !VECTIR_HPP_ */
