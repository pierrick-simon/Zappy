/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Resources
*/

#ifndef RESOURCES_HPP_
    #define RESOURCES_HPP_

    #include <vector>
    #include "Info.hpp"
    #include "ResourceInfo.hpp"
    #include "graphics/IDrawable2D.hpp"

namespace Zappy {
    class Resources : public Graphics::IDrawable2D {
    public:
        Resources(Font &font);

        void draw2D() const override;
        void update(const std::map<Info::ResourceName, std::size_t> &map,
            const std::map<Info::ResourceName, std::size_t> &players);

    private:
        std::map<Info::ResourceName, ResourceInfo> _resources;

        static const std::vector<Info::ResourceName> INIT;
    };
} // namespace Zappy

#endif /* !RESOURCES_HPP_ */
