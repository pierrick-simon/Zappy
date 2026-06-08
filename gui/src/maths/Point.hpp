/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef POINT3_HPP
    #define POINT3_HPP

    #include <cmath>

    #include "Vector.hpp"

namespace Maths {

    template<typename Type>
    using Point3 = Vector3<Type>;
    using Point3D = Point3<double>;
} // namespace Maths

#endif
