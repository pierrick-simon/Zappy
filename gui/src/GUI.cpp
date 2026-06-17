/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** GUI
*/

#include "GUI.hpp"
#include "ArgsParser.hpp"
#include "Utils.hpp"

namespace Zappy {
    GUI::GUI(std::vector<std::string> args) :
        _env(Parser::ArgsParser::getArg<int>(args, "-p", DEFAULT_PORT),
            Parser::ArgsParser::getArg<std::string>(
                args, "-h", DEFAULT_HOST.data()),
            _logFile, _isConnect),
        _window(_env),
        _logFile(std::string(LOG_FILE))
    {
        Shared::Utils::logMsg(_logFile, "Client GUI Open.");
    }

    GUI::~GUI()
    {
        Shared::Utils::logMsg(_logFile, "Client Closed.");
    }

    void GUI::run()
    {
        while (Graphics::Window::isRunning() && _env.update()) {
            update();
        }
    }

    void GUI::update()
    {
        this->_window.update();
    }
} // namespace Zappy
