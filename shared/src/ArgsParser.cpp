/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ArgParser
*/

#include "ArgsParser.hpp"

namespace Parser {

    void ArgsParser::checkStream(const std::istringstream &stream,
        const std::string &flag)
    {
        if (stream.fail() || !stream.eof())
            throw ArgsParserError("incorect value after " + flag + " option");
    }

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

    std::size_t ArgsParser::getArgSize(
            std::reference_wrapper<std::vector<std::string>> args,
            const std::string &flag)
    {
        long long value = ArgsParser::getArg<long long>(args, flag);

        if (value <= 0)
            throw ArgsParserError(flag + " should have a positive value");
        return value;
    }

    std::size_t ArgsParser::getArgSize(
            std::reference_wrapper<std::vector<std::string>> args,
            const std::string &flag, std::size_t fallBack)
    {
        long long value = ArgsParser::getArg<long long>(args, flag, fallBack);

        if (value <= 0)
            throw ArgsParserError(flag + " should have a positive value");
        return value;
    }
} // namespace RayTracer
