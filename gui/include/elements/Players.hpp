/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Players
*/

#ifndef PLAYERS_HPP_
    #define PLAYERS_HPP_

    #include <Model.hpp>
    #include <ModelAnimation.hpp>

    #include "Assets.hpp"
    #include "Info.hpp"
    #include "NewPlayerEvent.hpp"
    #include "Player.hpp"
    #include "Team.hpp"
    #include "graphics/AShadered.hpp"
    #include "graphics/IDrawable3D.hpp"

namespace Zappy {
    class Players : public Graphics::IDrawable3D,
                    public Graphics::IUpdatable,
                    public Graphics::AShadered {
    public:
        Players(std::ofstream &logFile, std::optional<std::size_t> &select,
            std::size_t &frequency);

        std::optional<std::reference_wrapper<Player>> addPlayer(
            const Shared::NewPlayerEvent::NewPlayer &player);

        void initPos(std::size_t width, std::size_t height);

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

        void update(float dt) override;

        void setShader(Graphics::Shader &shader) override;

        void loadAnimations();

        [[nodiscard]] std::map<std::size_t, Player> &getPlayers()
        {
            return _players;
        }

    private:
        std::map<std::size_t, Player> _players;
        std::map<Info::ResourceName, std::size_t> _totalResources =
            Info::INIT_RESOUCES;

        std::ofstream &_logFile;
        inline static const std::string PLAYER_MODEL_PATH =
            Assets::getResource("players/player.glb");
        raylib::Model _model {LoadModel(PLAYER_MODEL_PATH.c_str())};

        std::vector<::ModelAnimation> _modelAnimation;

        bool _changeColor = false;
        float _blink = 0.f;
        std::optional<std::size_t> &_select;
        std::size_t &_frequency;

        static constexpr auto STONE_MAT = 1;
        static constexpr auto GLOWING_MAT = 2;
    };
} // namespace Zappy

#endif /* !Players_HPP_ */
