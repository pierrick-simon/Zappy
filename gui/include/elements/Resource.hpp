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

namespace Zappy {
    class Resource {
    public:
        Resource(Info::ResourceName resource, raylib::Vector3 pos, float scale,
            float rotation);

        [[nodiscard]] raylib::Vector3 getPos() const;
        [[nodiscard]] float getScale() const;
        [[nodiscard]] float getRotation() const;

    private:
        Info::ResourceName _resource;
        raylib::Vector3 _pos;
        float _scale;
        float _rotation;
    };
} // namespace Zappy

#endif /* !RESOURCE_HPP_ */
