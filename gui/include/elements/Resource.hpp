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
        Resource(Info::ResourceName resource, Vector3 pos, float scale);

        [[nodiscard]] Vector3 getPos() const;
        [[nodiscard]] float getScale() const;

    private:
        Info::ResourceName _resource;
        Vector3 _pos;
        float _scale;
    };
} // namespace Zappy

#endif /* !RESOURCE_HPP_ */
