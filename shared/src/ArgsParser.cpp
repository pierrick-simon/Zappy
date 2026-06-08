/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ArgParser
*/

#include "ArgsParser.hpp"

namespace Parser {
    bool ArgsParser::isArg(
        std::reference_wrapper<std::vector<std::string>> args, const std::string &flag)
    {
        bool ret = false;
        for (auto arg = args.get().begin(); arg != args.get().end(); ++arg) {
            if (*arg == flag) {
                args.get().erase(arg);
                ret = true;
                break;
            }
        }
        return ret;
    }
} // namespace RayTracer
