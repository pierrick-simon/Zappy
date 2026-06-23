/*
** EPITECH PROJECT, 2026
** gui
** File description:
** TornadoParticle
*/

#ifndef TORNADOPARTICLE_HPP_
    #define TORNADOPARTICLE_HPP_

    #include <vector>
    #include <array>
    #include "graphics/GameObject.hpp"
    #include "graphics/primitives/Sphere.hpp"

namespace Graphics {
    class TornadoParticle : public GameObject {
        public:
            enum Parameter { RADIUS, SPINSPEED, ELEVATIONSPEED, TIME, SIZE, COLOR, NBPARAMETER };

            TornadoParticle(raylib::Color color, float fade,
                std::array<raylib::Vector2, NBPARAMETER> parameters);

            void update(float dt) override;
            void draw3D() const override;
            void emit(std::size_t nbNewParticle);

            bool isEmpty() const
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
}

#endif /* !TORNADOPARTICLE_HPP_ */
