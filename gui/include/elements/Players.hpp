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
    #include "graphics/AShadered.hpp"
    #include "graphics/IDrawable3D.hpp"

namespace Zappy {
    class Players : public Graphics::IDrawable3D,
                    public Graphics::IUpdatable,
                    public Graphics::AShadered {
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

        void draw3D() const override;

        void update(float dt) override;

        void setShader(Graphics::Shader &shader) override;

    private:
        std::unordered_map<std::size_t, Player> _players;
        std::map<Info::ResourceName, std::size_t> _totalResources =
            Info::INIT_RESOUCES;

        std::ofstream &_logFile;
        inline static const std::string PLAYER_MODEL_PATH =
            Assets::getResource("players/player.glb");
        raylib::Model _model {LoadModel(PLAYER_MODEL_PATH.c_str())};

        std::vector<raylib::ModelAnimation> _modelAnimation =
            raylib::ModelAnimation::Load(PLAYER_MODEL_PATH);
    };
} // namespace Zappy

#endif /* !Players_HPP_ */
