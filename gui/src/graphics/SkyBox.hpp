/*
** EPITECH PROJECT, 2026
** gui
** File description:
** SkyBox
*/

#ifndef SKYBOX_HPP_
    #define SKYBOX_HPP_

    #include <raylib-cpp.hpp>
    #include <string_view>
    #include "graphics/IDrawable3D.hpp"

namespace Graphics {
    class SkyBox : public IDrawable3D {
    public:
        SkyBox(const std::string &imgSkyboxPath = IMG,
            const std::string &skyboxVSPath = SKYBOX_VS,
            const std::string &skyboxFSPath = SKYBOX_FS,
            const std::string &cubemapVSPath = CUBEMAP_VS,
            const std::string &cubemapFSPath = CUBEMAP_FS);

        void draw3D() const override;

    private:
        raylib::Shader _skyboxShader;
        raylib::Shader _cubemapShader;
        raylib::Model _modelbox;
        raylib::TextureCubemap _texture;

        static constexpr auto IMG = "gui/resources/sky.png";
        static constexpr auto SKYBOX_VS = "gui/resources/shaders/skybox.vs";
        static constexpr auto SKYBOX_FS = "gui/resources/shaders/skybox.fs";
        static constexpr auto CUBEMAP_VS = "gui/resources/shaders/cubemap.vs";
        static constexpr auto CUBEMAP_FS = "gui/resources/shaders/cubemap.fs";
    };
} // namespace Graphics

#endif /* !SKYBOX_HPP_ */
