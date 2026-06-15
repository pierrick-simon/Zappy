/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Resource
*/

#ifndef RESOURCE_HPP_
    #define RESOURCE_HPP_

    #include "Info.hpp"

namespace Zappy {
    class Resource {
    public:
        Resource(Info::ResourceName resource);

    private:
        Info::ResourceName _resource;
    };
} // namespace Zappy

#endif /* !RESOURCE_HPP_ */
