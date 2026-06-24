/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Resource
*/

#ifndef RESOURCE_HPP_
    #define RESOURCE_HPP_

    #include "Info.hpp"
    #include <Vector3.hpp>

namespace Zappy {
    class Resource {
    public:
        Resource(Info::ResourceName resource, Vector3 pos);

    private:
        Info::ResourceName _resource;
        Vector3 _pos;
    };
} // namespace Zappy

#endif /* !RESOURCE_HPP_ */
