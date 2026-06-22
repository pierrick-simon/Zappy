/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Environement
*/

#ifndef GUI_ENVIRONEMENT_HPP_
    #define GUI_ENVIRONEMENT_HPP_

    #include <functional>
    #include <optional>
    #include <queue>
    #include <string_view>
    #include <unordered_map>
    #include <vector>
    #include "Connect.hpp"
    #include "Egg.hpp"
    #include "Elevations.hpp"
    #include "GUIException.hpp"
    #include "Map.hpp"
    #include "Overlay.hpp"
    #include "Players.hpp"
    #include "graphics/AShadered.hpp"
    #include "graphics/ColorGenerator.hpp"
    #include "graphics/IDrawable2D.hpp"
    #include "graphics/IDrawable3D.hpp"
    #include "graphics/IObject.hpp"
    #include "graphics/IUpdatable.hpp"

namespace Zappy {
    class Environement : public Graphics::IDrawable3D,
                         public Graphics::IUpdatable,
                         public Graphics::IDrawable2D,
                         public Graphics::IObject,
                         public Graphics::AShadered {
    public:
        Environement(int port, const std::string &ip, std::ofstream &logFile,
            bool &isConnect);

        bool updateFromServer();

        void update(float dt) override;

        void setShader(Graphics::Shader &shader) override;

        void draw3D() const override;

        void draw2D() const override;

    private:
        using Event = std::function<void(Environement &, std::istringstream)>;

        struct Message {
            std::size_t id;
            std::string message;
        };

        bool connect();
        bool infoToRead();
        void handleEvents();
        void loading();

        void mapSize(std::istringstream stream);
        void updateTile(std::istringstream stream);
        void teamName(std::istringstream stream);
        void newPlayer(std::istringstream stream);
        void playerPosition(std::istringstream stream);
        void playerLevel(std::istringstream stream);
        void playerInventory(std::istringstream stream);
        void playerExpulsion(std::istringstream stream);
        void playerBroadcast(std::istringstream stream);
        void startIncantate(std::istringstream stream);
        void endIncantate(std::istringstream stream);
        void eggLaying(std::istringstream stream);
        void takeResource(std::istringstream stream);
        void setResource(std::istringstream stream);
        void deadPlayer(std::istringstream stream);
        void eggLaid(std::istringstream stream);
        void eggHatched(std::istringstream stream);
        void deadEgg(std::istringstream stream);
        void timeUnitRequest(std::istringstream stream);
        void timeUnitModification(std::istringstream stream);
        void endOfGame(std::istringstream stream);
        void serverMsg(std::istringstream stream);
        void unknowCommand(std::istringstream stream);
        void badCommandParameter(std::istringstream stream);

        void playersEndIncantate(
            std::vector<std::size_t> &players, bool success);

        Map _map;
        Players _players;
        std::unordered_map<std::size_t, Egg> _eggs;
        std::unordered_map<std::string, Color> _teams;
        std::size_t _timeUnit;
        std::string _winingTeam;

        bool _end = false;
        Shared::Connect _connect;
        std::string _buffer;
        bool _loading = false;
        std::queue<std::string> _events;

        std::optional<std::size_t> _selectPlayer;

        Graphics::ColorGenerator _colorGenerator;
        Overlay _overlay;
        Elevations _elevations;

        bool &_isConnect;
        std::ofstream &_logFile;
        static const std::unordered_map<std::string, Event> EVENTS;

        static constexpr std::string_view WELCOME = "WELCOME";
        static constexpr std::string_view TEAM = "GRAPHIC";
        static constexpr std::size_t SMALL_SLEEP = 100;
    };
} // namespace Zappy

#endif /* GUI_ENVIRONEMENT_HPP_ */
