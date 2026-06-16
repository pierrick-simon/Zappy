/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Info
*/

#include "Info.hpp"

namespace Zappy {
    Info::ResourceName Info::getResource(const std::string &name)
    {
        for (const auto &[type, resource] : resources) {
            if (resource.str == name)
                return type;
        }
        throw ResourceNotFoundException();
    }

    Info::ResourceName Info::getResource(std::size_t nb)
    {
        for (const auto &[type, resource] : resources) {
            if (resource.nb == nb)
                return type;
        }
        throw ResourceNotFoundException();
    }

    Info::Direction Info::getDirection(std::size_t nb)
    {
        for (const auto &[type, direction] : directions) {
            if (direction.nb == nb)
                return type;
        }
        throw DirectionNotFoundException();
    }

    const std::unordered_map<Info::ResourceName, Info::Resource>
        Info::resources = {
            {ResourceName::Food, {0.5, "food", 0}},
            {ResourceName::Linemate, {0.3, "linemate", 1}},
            {ResourceName::Deraumere, {0.15, "deraumere", 2}},
            {ResourceName::Sibur, {0.1, "sibur", 3}},
            {ResourceName::Mendiane, {0.1, "mendiane", 4}},
            {ResourceName::Phiras, {0.08, "phiras", 5}},
            {ResourceName::Thystame, {0.05, "thystame", 6}},
    };

    const std::map<Info::ResourceName, std::size_t> Info::INIT_RESOUCES = {
        {ResourceName::Food, 0},
        {ResourceName::Linemate, 0},
        {ResourceName::Deraumere, 0},
        {ResourceName::Sibur, 0},
        {ResourceName::Mendiane, 0},
        {ResourceName::Phiras, 0},
        {ResourceName::Thystame, 0},
    };

    const std::map<Info::Direction, Info::Dir> Info::directions = {
        {Direction::North, {0, -1, "North", 1}},
        {Direction::East, {1, 0, "East", 2}},
        {Direction::South, {0, 1, "South", 3}},
        {Direction::West, {-1, 0, "West", 4}}};

    const std::unordered_map<std::size_t, Info::Elevation> Info::elevations = {
        {1, {1, {{ResourceName::Linemate, 1}}}},
        {2,
            {2,
                {{ResourceName::Linemate, 1},
                    {ResourceName::Deraumere, 1},
                    {ResourceName::Sibur, 1}}}},
        {3,
            {2,
                {{ResourceName::Linemate, 2},
                    {ResourceName::Phiras, 2},
                    {ResourceName::Sibur, 1}}}},
        {4,
            {4,
                {{ResourceName::Linemate, 1},
                    {ResourceName::Deraumere, 1},
                    {ResourceName::Sibur, 2},
                    {ResourceName::Phiras, 2}}}},
        {5,
            {4,
                {{ResourceName::Linemate, 1},
                    {ResourceName::Deraumere, 2},
                    {ResourceName::Sibur, 1},
                    {ResourceName::Mendiane, 3}}}},
        {6,
            {6,
                {{ResourceName::Linemate, 1},
                    {ResourceName::Deraumere, 2},
                    {ResourceName::Sibur, 3},
                    {ResourceName::Phiras, 1}}}},
        {7,
            {6,
                {{ResourceName::Linemate, 2},
                    {ResourceName::Deraumere, 2},
                    {ResourceName::Sibur, 2},
                    {ResourceName::Mendiane, 2},
                    {ResourceName::Phiras, 2},
                    {ResourceName::Thystame, 1}}}},
    };
} // namespace Zappy
