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

        TornadoParticle(std::size_t &timeUnit,
            raylib::Color color = raylib::Color::White(), float fade = 0.3f,
            std::array<raylib::Vector2, NBPARAMETER> parameters = DEFAULT_VALUE,
            float emitRate = 250);

        void update(float dt) override;
        void draw3D() const override;
        void emit(float dt);

        [[nodiscard]] bool isEmpty() const
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

        float _emitAccumulator = 0.f;
        float _emitRate;

        raylib::Color _color;
        float _fade;
        std::vector<Particle> _particles;
        std::array<raylib::Vector2, NBPARAMETER> _parameters;

        std::size_t &_timeUnit;

        static const std::array<raylib::Vector2, NBPARAMETER> DEFAULT_VALUE;
        static constexpr float MAX_VELOCITY = 20.0f;
    };
} // namespace Graphics

#endif /* !TORNADOPARTICLE_HPP_ */
