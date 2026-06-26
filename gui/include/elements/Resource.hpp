/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Resource
*/

#ifndef RESOURCE_HPP_
    #define RESOURCE_HPP_

    #include <Vector3.hpp>
    #include "Info.hpp"
#include "graphics/Transformable3D.hpp"

namespace Zappy {
    class Resource : public Graphics::Transformable3D {
    public:
        Resource(Info::ResourceName resource, raylib::Vector3 pos, float scale,
            float rotation);

    private:
        Info::ResourceName _resource;
    };
} // namespace Zappy

#endif /* !RESOURCE_HPP_ */
