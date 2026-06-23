/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef MODEL_HPP
    #define MODEL_HPP
    #include <functional>
    #include <optional>
    #include <raylib-cpp.hpp>

    #include "graphics/GameObject.hpp"

namespace Graphics {
    class Model : public raylib::Model, public GameObject {
    public:
        explicit Model(const std::string &path);

        void draw3D() const override;
        void loadAnimations(const std::optional<std::string> &path = {});
        void playAnimation(size_t index);
        void update(float dt) override;

        std::optional<std::reference_wrapper<ModelAnimation>>
        getCurrentAnimation();

    private:
        std::string _path;
        std::vector<::ModelAnimation> _animations;
        std::optional<size_t> _currentAnimationIndex;
        int _currentAnimationFrame {0};
    };

} // namespace Graphics

#endif
