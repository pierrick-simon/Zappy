/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef GAMEOBJECT_HPP
    #define GAMEOBJECT_HPP
    #include <SFML/Graphics/RenderWindow.hpp>

    #include "IGameObject.hpp"
    #include "../maths/Quaternion.hpp"
    #include "../maths/Vector.hpp"

namespace Graphics {
    class GameObject : public IGameObject {
    public:
        explicit GameObject(sf::RenderWindow &window);
        void render() const override;
        Maths::Vector3D &getPosition() override;
        Maths::Quaternion &getRotation() override;
        Maths::Vector3D &getScale() override;
        [[nodiscard]] const Maths::Vector3D &getPosition() const override;
        [[nodiscard]] const Maths::Quaternion &getRotation() const override;
        [[nodiscard]] const Maths::Vector3D &getScale() const override;
        [[nodiscard]] Maths::Vector3D getForward() const;

    protected:
        Maths::Vector3D _position;
        Maths::Quaternion _rotation;
        Maths::Vector3D _scale{1, 1, 1};
        sf::RenderWindow &_window;
    };
} // Graphics

#endif
