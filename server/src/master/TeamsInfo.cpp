/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** TeamsInfo
*/

#include "TeamsInfo.hpp"
#include "Init.hpp"

namespace Zappy {
    TeamsInfo::TeamsInfo(sf::Font &font,
        const std::map<std::string, std::string> &ais, AddProcess &process,
        std::unordered_map<std::string, std::size_t> &teams) :
        _playTexture(SfmlUtils::SfmlUtils::loadTextureFromFile(PLAY.data())),
        _pauseTexture(SfmlUtils::SfmlUtils::loadTextureFromFile(PAUSE.data())),
        _emptyTexture(SfmlUtils::SfmlUtils::loadTextureFromFile(EMPTY.data())),
        _checkTexture(SfmlUtils::SfmlUtils::loadTextureFromFile(CHECK.data())),
        _process(process),
        _teams(teams)
    {
        _rec.setSize({Init::TEAM_BOX_X, Init::TEAM_BOX_Y});
        _rec.setPosition(
            {Init::BOX_GAP * 2.f + Init::AI_BOX_X, Init::TOOLBAR_SIZE_Y});
        _rec.setFillColor(Init::BACKGROUND_COLOR);
        TextureMap map({{Init::Play, _playTexture},
            {Init::Pause, _pauseTexture},
            {Init::Empty, _emptyTexture},
            {Init::Check, _checkTexture}});
        for (const auto &[name, _] : _teams)
            _teamsBox.insert({name, {{font, name, map, ais}, SLEEP}});
        float height = 0;
        for (auto &[_, team] : _teamsBox) {
            team.box.setHeight(
                Init::TOOLBAR_SIZE_Y + Init::BOX_GAP + height - _scroll);
            height += team.box.getHeight() + Init::BOX_GAP;
        }
        _totalHeight = height;
        _clock = std::chrono::steady_clock::now();
    }

    void TeamsInfo::draw(sf::RenderWindow &win)
    {
        auto now = std::chrono::steady_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::milliseconds>(now - _clock);
        _clock = now;
        win.draw(_rec);
        for (auto &[name, team] : _teamsBox) {
            team.box.draw(win, _teams.at(name));
            if (team.sleep.count() > 0)
                team.sleep -= elapsed;
            if (team.box.getFill() && _teams.at(name) > 0 &&
                team.sleep.count() <= 0) {
                _process.addAi(name, team.box.getSelected());
                team.sleep = SLEEP;
            }
        }
    }

    void TeamsInfo::event(sf::Event &event, sf::Vector2f mousePos)
    {
        if (_rec.getGlobalBounds().contains(mousePos) &&
            event.type == sf::Event::MouseWheelMoved) {
            _scroll -= float(event.mouseWheel.delta) * Init::SCROLL;
            auto max = _totalHeight - Init::AI_BOX_Y + Init::BOX_GAP;
            if (max <= 0)
                _scroll = 0;
            else
                _scroll = std::clamp(_scroll, 0.f, max);
            std::size_t i = 0;
            float height = 0;
            for (auto &[_, team] : _teamsBox) {
                team.box.setHeight(Init::TOOLBAR_SIZE_Y + Init::BOX_GAP +
                    float(i) * Init::BOX_GAP + height - _scroll);
                height += team.box.getHeight();
                i++;
            }
        }
        for (auto &[name, team] : _teamsBox) {
            auto algo = team.box.event(event, mousePos);
            if (algo && _teams.at(name) > 0)
                _process.addAi(name, *algo);
        }
    }
} // namespace Zappy
