/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include <SFML/Graphics/Drawable.hpp>

#include "Transformable3D.hpp"

namespace Graphics {
    class GameObject : public Transformable3D, public sf::Drawable {
    protected:
        void applyTransform() const;
    };
} // namespace Graphics

#endif
