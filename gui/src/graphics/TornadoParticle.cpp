/*
** EPITECH PROJECT, 2026
** gui
** File description:
** TornadoParticle
*/

#include "TornadoParticle.hpp"
#include <algorithm>
#include "Utils.hpp"

namespace Graphics {
    TornadoParticle::TornadoParticle(std::size_t &timeUnit, raylib::Color color,
        float fade, std::array<raylib::Vector2, NBPARAMETER> parameters,
        float emitRate) :
        _color(color),
        _fade(fade),
        _parameters(parameters),
        _timeUnit(timeUnit),
        _emitRate(emitRate)
    {
        if (_fade == 0.f)
            _fade = 0.01f;
    }

    void TornadoParticle::updateParticle(float dt, Particle &particle)
    {
        float dx = _position.x - particle.sphere.getPosition().x;
        float dz = _position.z - particle.sphere.getPosition().z;
        particle.velocity.x += dx * 2.0f * dt;
        particle.velocity.z += dz * 2.0f * dt;
        float oldVx = particle.velocity.x;
        float oldVz = particle.velocity.z;
        particle.velocity.x += -oldVz * 1.5f * dt;
        particle.velocity.z += oldVx * 1.5f * dt;
        particle.velocity.x =
            std::clamp(particle.velocity.x, -MAX_VELOCITY, MAX_VELOCITY);
        particle.velocity.z =
            std::clamp(particle.velocity.z, -MAX_VELOCITY, MAX_VELOCITY);
        auto &pos = particle.sphere.getPosition();
        pos.x += particle.velocity.x * dt * 0.01f;
        pos.y += particle.velocity.y * dt;
        pos.z += particle.velocity.z * dt * 0.01f;

        float ratio = particle.current / particle.start;
        particle.sphere.getColor().a =
            (unsigned char) (255.f * std::min(ratio / _fade, 1.f));
    }

    void TornadoParticle::update(float dt)
    {
        if (_timeUnit == 0)
            _timeUnit = 1;
        for (auto iter = _particles.begin(); iter != _particles.end();) {
            iter->current -= dt;
            if (iter->current <= 0.f)
                iter = _particles.erase(iter);
            else {
                updateParticle(float(_timeUnit) * dt, *iter);
                iter++;
            }
        }
        emit(dt);
    }

    void TornadoParticle::spawnParticle()
    {
        auto &particle = _particles.emplace_back();
        float angle = Shared::Utils::fRandRange(0.f, 2.f * PI);
        float radius = getValue(RADIUS);
        particle.sphere.setPosition({_position.x + cosf(angle) * radius,
            _position.y + 0,
            _position.z + sinf(angle) * radius});
        float spinSpeed = getValue(SPINSPEED);
        particle.velocity = raylib::Vector3 {-sinf(angle) * spinSpeed,
            getValue(ELEVATIONSPEED),
            cosf(angle) * spinSpeed};
        particle.start = getValue(TIME);
        particle.current = particle.start;
        particle.sphere.getRadius() = getValue(SIZE);
        particle.sphere.getColor() =
            raylib::Color {(unsigned char) std::clamp(
                               int(_color.r) + int(getValue(COLOR)), 0, 255),
                (unsigned char) std::clamp(
                    int(_color.g) + int(getValue(COLOR)), 0, 255),
                (unsigned char) std::clamp(
                    int(_color.b) + int(getValue(COLOR)), 0, 255),
                (unsigned char) 255};
    }

    float TornadoParticle::getValue(Parameter range)
    {
        return Shared::Utils::fRandRange(
            _parameters[range].x, _parameters[range].y);
    }

    void TornadoParticle::draw3D() const
    {
        for (const auto &particle : _particles)
            particle.sphere.draw3D();
    }

    void TornadoParticle::emit(float dt)
    {
        _emitAccumulator += dt * _emitRate;
        while (_emitAccumulator >= 1.f) {
            spawnParticle();
            _emitAccumulator -= 1.f;
        }
    }

    const std::array<raylib::Vector2, TornadoParticle::NBPARAMETER>
        TornadoParticle::DEFAULT_VALUE = {
            raylib::Vector2 {15, 20},
            {0.60f, 1.00f},
            {0.60f, 1.20f},
            {25.0f, 40.0f},
            {0.10f, 0.18f},
            {-30.f, 30.f},
    };
} // namespace Graphics
