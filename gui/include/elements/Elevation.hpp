/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Elevation
*/

#ifndef ELEVATION_HPP_
    #define ELEVATION_HPP_

    #include <map>

namespace Zappy {
    class Elevation {
    public:
        Elevation(std::size_t x, std::size_t y, std::size_t level,
            std::map<std::size_t, bool> players);

        void end(bool success);

        void setFinish(bool finish);

        [[nodiscard]] std::size_t getX() const
        {
            return _x;
        }
        [[nodiscard]] std::size_t getY() const
        {
            return _y;
        }
        [[nodiscard]] bool getFinish() const
        {
            return _finish;
        }
        [[nodiscard]] const std::map<std::size_t, bool> &getPlayers() const
        {
            return _players;
        }
        [[nodiscard]] std::map<std::size_t, bool> &getPlayers()
        {
            return _players;
        }

    private:
        std::size_t _x;
        std::size_t _y;
        std::size_t _level;
        bool _finish = false;
        bool _success = false;
        std::map<std::size_t, bool> _players;
    };
} // namespace Zappy

#endif /* !ELEVATION_HPP_ */
