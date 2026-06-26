/*
** EPITECH PROJECT, 2026
** gui
** File description:
** SkyBox
*/

#include "SkyBox.hpp"
#include <iostream>
#include <stdexcept>
#include "rlgl.h"

namespace Graphics {

    SkyBox::SkyBox(const std::string &imgSkyboxPath,
        const std::string &skyboxVSPath, const std::string &skyboxFSPath,
        const std::string &cubemapVSPath, const std::string &cubemapFSPath) :
        _skyboxShader(skyboxVSPath, skyboxFSPath),
        _cubemapShader(cubemapVSPath, cubemapFSPath),
        _modelbox(raylib::Mesh::Cube(1.0f, 1.0f, 1.0f))
    {
        _modelbox.materials[0].shader = _skyboxShader;
        int envMap = MATERIAL_MAP_CUBEMAP;
        int doGamma = 0;
        int vflipped = 0;
        int equiMap = 0;
        _skyboxShader.SetValue(_skyboxShader.GetLocation("environmentMap"),
            &envMap,
            SHADER_UNIFORM_INT);
        _skyboxShader.SetValue(
            _skyboxShader.GetLocation("doGamma"), &doGamma, SHADER_UNIFORM_INT);
        _skyboxShader.SetValue(_skyboxShader.GetLocation("vflipped"),
            &vflipped,
            SHADER_UNIFORM_INT);
        _cubemapShader.SetValue(
            _cubemapShader.GetLocation("equirectangularMap"),
            &equiMap,
            SHADER_UNIFORM_INT);
        raylib::Image img(imgSkyboxPath);
        if (img.GetFormat() != PIXELFORMAT_UNCOMPRESSED_R8G8B8A8)
            img.Format(PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
        _texture.Load(img, CUBEMAP_LAYOUT_AUTO_DETECT);
        _modelbox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = _texture;
    }

    void SkyBox::draw3D() const
    {
        rlDisableBackfaceCulling();
        rlDisableDepthMask();
        _modelbox.Draw({0.0f, 0.0f, 0.0f});
        rlEnableDepthMask();
        rlEnableBackfaceCulling();
    }

} // namespace Graphics
