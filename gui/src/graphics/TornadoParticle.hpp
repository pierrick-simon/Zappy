/*
** EPITECH PROJECT, 2026
** gui
** File description:
** TornadoParticle
*/

#ifndef TORNADOPARTICLE_HPP_
    #define TORNADOPARTICLE_HPP_

    #include <array>
    #include <vector>
    #include "graphics/GameObject.hpp"
    #include "graphics/primitives/Sphere.hpp"

namespace Graphics {
    class TornadoParticle : public GameObject {
    public:
        enum Parameter {
            RADIUS,
            SPINSPEED,
            ELEVATIONSPEED,
            TIME,
            SIZE,
            COLOR,
            NBPARAMETER
        };

        TornadoParticle(raylib::Color color = raylib::Color::White(),
            float fade = 0.3f,
            std::array<raylib::Vector2, NBPARAMETER> parameters =
                DEFAULT_VALUE);

        void update(float dt) override;
        void draw3D() const override;
        void emit(std::size_t nbNewParticle);

        [[nodiscard]]bool isEmpty() const
        {
            return _particles.empty();
        }

    private:
        struct Particle {
            raylib::Vector3 velocity = {0, 0, 0};
            float current = 0;
            float start = 0;
            Sphere sphere = {};
        };

        void spawnParticle();
        void updateParticle(float dt, Particle &particle);
        float getValue(Parameter range);

        raylib::Color _color;
        float _fade;
        std::vector<Particle> _particles;
        std::array<raylib::Vector2, NBPARAMETER> _parameters;

        static const std::array<raylib::Vector2, NBPARAMETER> DEFAULT_VALUE;
    };
} // namespace Graphics

#endif /* !TORNADOPARTICLE_HPP_ */
