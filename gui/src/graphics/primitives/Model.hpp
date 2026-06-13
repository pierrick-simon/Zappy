/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef MODEL_HPP
    #define MODEL_HPP
    #include <raylib-cpp.hpp>

    #include "graphics/GameObject.hpp"

namespace Graphics {
    class Model : public raylib::Model, public GameObject {
    public:
        using raylib::Model::Model;
        void draw() const override;
    };

} // namespace Graphics

#endif
