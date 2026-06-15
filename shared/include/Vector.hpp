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

            Vector2(const T &x, const T &y): x(x), y(y) {};

            Vector2<T> &operator+=(const Vector2 &v) { x += v.x; y += v.y; return *this; };
            Vector2<T> operator*(const T &v) { return Vector2<T>(x * v, y * v); };

    };

}

#endif /* !VECTIR_HPP_ */
