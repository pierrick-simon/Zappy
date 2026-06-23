/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Players
*/

#ifndef PLAYERS_HPP_
    #define PLAYERS_HPP_

    #include <Model.hpp>

    #include "Assets.hpp"
    #include "Info.hpp"
    #include "NewPlayerEvent.hpp"
    #include "Player.hpp"
    #include "Team.hpp"
    #include "graphics/IDrawable3D.hpp"

namespace Zappy {
    class Players : public Graphics::IDrawable3D {
    public:
        Players(std::ofstream &logFile);

        bool addPlayer(const Shared::NewPlayerEvent::NewPlayer &player);

        [[nodiscard]] std::map<Info::ResourceName, std::size_t>
        getTotalResources() const
        {
            return _totalResources;
        }

        [[nodiscard]] Player &getPlayer(std::size_t id);
        void updateTotalResources(
            const std::map<Info::ResourceName, std::size_t> &before,
            std::map<Info::ResourceName, std::size_t> after);

        [[nodiscard]] std::size_t getNbPlayer();
        [[nodiscard]] std::size_t getFirstPlayerId();
        [[nodiscard]] std::array<std::size_t, Team::NB_LEVEL> getTeamPlayers(
            const std::string &team) const;
        [[nodiscard]] std::size_t getNbTilePlayers(
            std::size_t tile, std::size_t width) const;
        [[nodiscard]] std::optional<std::size_t> getNextPlayer(
            InfoBox::Action dir, std::size_t player) const;

        void draw3D() const override;

    private:
        std::map<std::size_t, Player> _players;
        std::map<Info::ResourceName, std::size_t> _totalResources =
            Info::INIT_RESOUCES;

        std::ofstream &_logFile;
        inline static const std::string PLAYER_MODEL_PATH =
            Assets::getResource("players/player.glb");
        raylib::Model _model {LoadModel(PLAYER_MODEL_PATH.c_str())};
    };
} // namespace Zappy

#endif /* !Players_HPP_ */
