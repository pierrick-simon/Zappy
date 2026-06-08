/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef CAMERA_H
    #define CAMERA_H
    #include "GameObject.hpp"

namespace Graphics
{
class Camera : public GameObject
{
public:
    explicit Camera(sf::RenderWindow &window);
};
} // namespace Graphics

#endif
