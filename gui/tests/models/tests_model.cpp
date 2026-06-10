/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** test_init
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <filesystem>
#include <iostream>

#include "graphics/primitives/model/Model.hpp"

static const auto DIRECTORY =
    std::filesystem::path(__FILE__).parent_path() / "files/";

Test(model_parsing, vertex_empty)
{
    cr_assert_any_throw(
        { Graphics::Model model(DIRECTORY / "vertex_empty.obj"); });
}

Test(model_parsing, vertex_only_x)
{
    cr_assert_any_throw(
        { Graphics::Model model(DIRECTORY / "vertex_only_x.obj"); });
}

Test(model_parsing, vertex_no_z)
{
    cr_assert_any_throw(
        { Graphics::Model model(DIRECTORY / "vertex_no_z.obj"); });
}

Test(model_parsing, vertex_simple)
{
    Graphics::Model::VertexType expected {1, 2, 3};

    cr_assert_none_throw({
        Graphics::Model model(DIRECTORY / "vertex_simple.obj");
        cr_assert_eq(model.getVertices().front(), expected);
    });
}

Test(model_parsing, vertex_w)
{
    Graphics::Model::VertexType expected {1, 2, 3};
    expected *= 4;
    cr_assert_none_throw({
        Graphics::Model model(DIRECTORY / "vertex_w.obj");
        cr_assert_eq(model.getVertices().front(), expected);
    });
}
Test(model_parsing, texture_pos_empty)
{
    cr_assert_any_throw(
        { Graphics::Model model(DIRECTORY / "texture_pos_empty.obj"); });
}

Test(model_parsing, texture_pos_only_x)
{
    Graphics::Model::TexturePosType expected {1, 0, 0};
    cr_assert_none_throw({
        Graphics::Model model(DIRECTORY / "texture_pos_only_x.obj");
        cr_assert_eq(model.getTexturePos().front(), expected);
    });
}

Test(model_parsing, texture_pos_simple)
{
    Graphics::Model::TexturePosType expected {1, 2, 0};
    cr_assert_none_throw({
        Graphics::Model model(DIRECTORY / "texture_pos_simple.obj");
        cr_assert_eq(model.getTexturePos().front(), expected);
    });
}

Test(model_parsing, texture_pos_3d)
{
    Graphics::Model::TexturePosType expected {1, 2, 3};

    cr_assert_none_throw({
        Graphics::Model model(DIRECTORY / "texture_pos_3d.obj");
        cr_assert_eq(model.getTexturePos().front(), expected);
    });
}

Test(model_parsing, empty_normal)
{
    cr_assert_any_throw(
        { Graphics::Model model(DIRECTORY / "normal_empty.obj"); });
}

Test(model_parsing, almost_normal)
{
    cr_assert_any_throw(
        { Graphics::Model model(DIRECTORY / "normal_almost.obj"); });
}

Test(model_parsing, simple_normal)
{
    Graphics::Model::NormalType expected {1, 2, 3};

    cr_assert_none_throw({
        Graphics::Model model(DIRECTORY / "normal_simple.obj");
        cr_assert_eq(model.getNormals().front(), expected);
    });
}
