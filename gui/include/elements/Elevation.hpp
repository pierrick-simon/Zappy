/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Elevation
*/

#ifndef ELEVATION_HPP_
    #define ELEVATION_HPP_

    #include <vector>

namespace Zappy {
    class Elevation {
    public:
        Elevation(std::size_t x, std::size_t y, std::size_t level,
            std::vector<std::size_t> players);

    private:
        std::size_t _x;
        std::size_t _y;
        std::size_t _level;
        std::vector<std::size_t> _players;
    };
} // namespace Zappy

#endif /* !ELEVATION_HPP_ */
