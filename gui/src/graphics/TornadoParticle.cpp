/*
** EPITECH PROJECT, 2026
** gui
** File description:
** TornadoParticle
*/

#include <algorithm>
#include "TornadoParticle.hpp"
#include "Utils.hpp"

namespace Graphics {
    TornadoParticle::TornadoParticle(raylib::Color color = raylib::Color::White(), float fade = 0.3,
            std::array<raylib::Vector2, NBPARAMETER> parameters = DEFAULT_VALUE)
        : _color(color), _fade(fade) , _parameters(std::move(parameters))
    {
        if (_fade == 0.f)
            _fade = 1.f;
    }

    void TornadoParticle::updateParticle(float dt, Particle &particle)
    {
        auto &pos = particle.sphere.getPosition();
        pos.x += particle.velocity.x * dt;
        pos.y += particle.velocity.y * dt;
        pos.z += particle.velocity.z * dt;
        float ratio = particle.current / particle.start;
        particle.sphere.getColor().a = (unsigned char)(255.f * std::min(ratio / _fade, 1.f));
    }

    void TornadoParticle::update(float dt)
    {
        for (auto iter = _particles.begin(); iter != _particles.end();) {
            iter->current -= dt;
            if (iter->current <= 0.f)
                iter = _particles.erase(iter);
            else {
                updateParticle(dt, *iter);
                iter++;
            }
        }
    }

    void TornadoParticle::spawnParticle()
    {
        auto particle = _particles.emplace_back();
        float angle  = Shared::Utils::fRandRange(0.f, 2.f * PI);
        float radius = getValue(RADIUS);
        particle.sphere.setPosition({
            _position.x + cosf(angle) * radius,
            _position.y + 0,
            _position.z + sinf(angle) * radius
        });
        float spinSpeed = getValue(SPINSPEED);
        particle.velocity = {
            -sinf(angle) * spinSpeed,
            getValue(ELEVATIONSPEED),
            cosf(angle) * spinSpeed
        };
        particle.start = getValue(TIME);
        particle.current = particle.start;
        particle.sphere.getRadius() = getValue(SIZE);
        particle.sphere.getColor() = {
            (unsigned char)std::clamp(int(_color.r) + int(getValue(COLOR)), 0, 255),
            (unsigned char)std::clamp(int(_color.g) + int(getValue(COLOR)), 0, 255),
            (unsigned char)std::clamp(int(_color.b) + int(getValue(COLOR)), 0, 255),
            (unsigned char)255
        };
    }

    float TornadoParticle::getValue(Parameter range)
    {
        return Shared::Utils::fRandRange(_parameters[range].x, _parameters[range].y);
    }

    void TornadoParticle::draw3D() const
    {
        for (const auto &particle : _particles)
            particle.sphere.draw3D();
    }

    void TornadoParticle::emit(std::size_t nbNewParticle)
    {
        for (std::size_t i = 0; i < nbNewParticle; i++)
            spawnParticle();
    }

    const std::array<raylib::Vector2, TornadoParticle::NBPARAMETER> TornadoParticle::DEFAULT_VALUE = {
        raylib::Vector2 {2.f, 2.5f},
        raylib::Vector2 {3.f, 6.f},
        raylib::Vector2 {1.f, 2.5f},
        raylib::Vector2 {0.01f, 0.20f},
        raylib::Vector2 {-30, 30},
    };
}
