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
            {ResourceName::FOOD, {0.5, "food", 0}},
            {ResourceName::LINEMATE, {0.3, "linemate", 1}},
            {ResourceName::DERAUMERE, {0.15, "deraumere", 2}},
            {ResourceName::SIBUR, {0.1, "sibur", 3}},
            {ResourceName::MENDIANE, {0.1, "mendiane", 4}},
            {ResourceName::PHIRAS, {0.08, "phiras", 5}},
            {ResourceName::THYSTAME, {0.05, "thystame", 6}},
    };

    const std::map<Info::ResourceName, std::size_t> Info::INIT_RESOUCES = {
        {ResourceName::FOOD, 0},
        {ResourceName::LINEMATE, 0},
        {ResourceName::DERAUMERE, 0},
        {ResourceName::SIBUR, 0},
        {ResourceName::MENDIANE, 0},
        {ResourceName::PHIRAS, 0},
        {ResourceName::THYSTAME, 0},
    };

    const std::map<Info::Direction, Info::Dir> Info::directions = {
        {Direction::NORTH, {0, -1, "North", 1}},
        {Direction::EAST, {1, 0, "East", 2}},
        {Direction::SOUTH, {0, 1, "South", 3}},
        {Direction::WEST, {-1, 0, "West", 4}}};

    const std::unordered_map<std::size_t, Info::Elevation> Info::elevations = {
        {1, {1, {{ResourceName::LINEMATE, 1}}}},
        {2,
            {2,
                {{ResourceName::LINEMATE, 1},
                    {ResourceName::DERAUMERE, 1},
                    {ResourceName::SIBUR, 1}}}},
        {3,
            {2,
                {{ResourceName::LINEMATE, 2},
                    {ResourceName::PHIRAS, 2},
                    {ResourceName::SIBUR, 1}}}},
        {4,
            {4,
                {{ResourceName::LINEMATE, 1},
                    {ResourceName::DERAUMERE, 1},
                    {ResourceName::SIBUR, 2},
                    {ResourceName::PHIRAS, 2}}}},
        {5,
            {4,
                {{ResourceName::LINEMATE, 1},
                    {ResourceName::DERAUMERE, 2},
                    {ResourceName::SIBUR, 1},
                    {ResourceName::MENDIANE, 3}}}},
        {6,
            {6,
                {{ResourceName::LINEMATE, 1},
                    {ResourceName::DERAUMERE, 2},
                    {ResourceName::SIBUR, 3},
                    {ResourceName::PHIRAS, 1}}}},
        {7,
            {6,
                {{ResourceName::LINEMATE, 2},
                    {ResourceName::DERAUMERE, 2},
                    {ResourceName::SIBUR, 2},
                    {ResourceName::MENDIANE, 2},
                    {ResourceName::PHIRAS, 2},
                    {ResourceName::THYSTAME, 1}}}},
    };
} // namespace Zappy
