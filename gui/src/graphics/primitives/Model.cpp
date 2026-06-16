/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Model.hpp"

#include <iostream>

namespace Graphics {
    Model::Model(const std::string &path) :
        raylib::Model(::LoadModel(path.c_str())), _path(path)
    {
    }

    void Model::draw() const
    {
        auto [axis, angle] = this->getRotation().ToAxisAngle();
        this->Draw(this->getPosition(), axis, angle, this->getScale());
    }

    void Model::loadAnimations(const std::optional<std::string> &path)
    {
        int count;
        ModelAnimation *anims =
            ::LoadModelAnimations(path.value_or(this->_path).c_str(), &count);
        this->_animations.clear();
        this->_animations.reserve(count);
        for (unsigned i = 0; i < count; ++i)
            this->_animations.emplace_back(anims[i]);
    }

    void Model::playAnimation(size_t index)
    {
        if (index >= this->_animations.size())
            throw std::out_of_range("Animation index incorrect");
        this->_currentAnimationFrame = 0;
        this->_currentAnimationIndex = index;
    }

    void Model::update(float dt)
    {
        auto currentAnimation = this->getCurrentAnimation();
        if (!currentAnimation)
            return;
        this->_currentAnimationFrame = (this->_currentAnimationFrame + 1) %
            currentAnimation->get().keyframeCount;
        this->UpdateAnimation(currentAnimation->get(),
            static_cast<float>(this->_currentAnimationFrame));
    }

    std::optional<std::reference_wrapper<ModelAnimation>>
    Model::getCurrentAnimation()
    {
        std::optional<std::reference_wrapper<ModelAnimation>> result;
        if (this->_currentAnimationIndex)
            result.emplace(this->_animations[*this->_currentAnimationIndex]);
        return result;
    }
} // namespace Graphics
