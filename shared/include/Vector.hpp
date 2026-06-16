/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Vector
*/

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

namespace Shared {

    template<typename T>
    class Vector2 {
    public:
        T x;
        T y;

        Vector2() = default;
        Vector2(const T &x, const T &y) :
            x(x), y(y) {};

        template<typename VT>
        Vector2<T> &operator+=(const Vector2<VT> &v)
        {
            x += v.x;
            y += v.y;
            return *this;
        };
        template<typename VT>
        Vector2<T> operator*(const VT &v)
        {
            return Vector2<T>(x * v, y * v);
        };
    };

} // namespace Shared

#endif /* !VECTIR_HPP_ */
