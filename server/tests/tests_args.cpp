/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** test_init
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <fcntl.h>

#include "Server.hpp"
#include "ArgsParser.hpp"

// #define test_throw(x, ex) try {x;cr_assert_eq(true, false);} catch (const ex &) {cr_assert_eq(true, true);} catch (const std::exception &e) {std::cout<< e.what() << std::endl;}

Test(correct, testArgs)
{
    std::vector<std::string> args = {"-p", "8092", "-x", "10", "-y", "10", "-n", "TEST", "TEST1", "-f", "100", "-c", "10"};
    cr_assert_none_throw(Zappy::Server tmp(args));
}

Test(helpPort, testArgs)
{
    std::vector<std::string> args = {"-p", "-x", "10", "-y", "10", "-n", "TEST", "TEST1", "-f", "100", "-c", "10"};
    cr_assert_throw(Zappy::Server tmp(args), Parser::Help);
}

Test(helpX, testArgs)
{
    std::vector<std::string> args = {"-p", "8081", "-x", "-y", "10", "-n", "TEST", "TEST1", "-f", "100", "-c", "10"};
    cr_assert_throw(Zappy::Server tmp(args), Parser::Help);
}

Test(helpY, testArgs)
{
    std::vector<std::string> args = {"-p", "8082", "-x", "10", "-y", "-n", "TEST", "TEST1", "-f", "100", "-c", "10"};
    cr_assert_throw(Zappy::Server tmp(args), Parser::Help);
}

Test(helpNames, testArgs)
{
    std::vector<std::string> args = {"-p", "8083", "-x", "10", "-y", "10", "-n", "-f", "100", "-c", "10"};
    cr_assert_throw(Zappy::Server tmp(args), Parser::ArgsParserError);
}

Test(helpNamesSame, testArgs)
{
    std::vector<std::string> args = {"-p", "8090", "-x", "10", "-y", "10", "-n", "TEST", "TEST", "-f", "100", "-c", "10"};
    cr_assert_throw(Zappy::Server tmp(args), Parser::ArgsParserError);
}

Test(helpNamesGraph, testArgs)
{
    std::vector<std::string> args = {"-p", "8091", "-x", "10", "-y", "10", "-n", "GRAPHIC", "-f", "100", "-c", "10"};
    cr_assert_throw(Zappy::Server tmp(args), Parser::ArgsParserError);
}

Test(helpF, testArgs)
{
    std::vector<std::string> args = {"-p", "8084", "-x", "10", "-y", "10", "-n", "TEST", "TEST1", "-f", "-c", "10"};
    cr_assert_throw(Zappy::Server tmp(args), Parser::Help);
}

Test(helpC, testArgs)
{
    std::vector<std::string> args = {"-p", "8085", "-x", "10", "-y", "10", "-n", "TEST", "TEST1", "-f", "100", "-c"};
    cr_assert_throw(Zappy::Server tmp(args), Parser::Help);
}

Test(BasicX, testArgs)
{
    std::vector<std::string> args = {"-p", "8094", "-y", "10", "-n", "TEST", "TEST1", "-f", "100", "-c", "10"};
    cr_assert_none_throw(Zappy::Server tmp(args));
}

Test(BasicY, testArgs)
{
    std::vector<std::string> args = {"-p", "8095", "-x", "10", "-n", "TEST", "TEST1", "-f", "100", "-c", "10"};
    cr_assert_none_throw(Zappy::Server tmp(args));
}

Test(BasicN, testArgs)
{
    std::vector<std::string> args = {"-p", "8096", "-x", "10", "-y", "10", "-f", "100", "-c", "10"};
    cr_assert_none_throw(Zappy::Server tmp(args));
}

Test(BasicF, testArgs)
{
    std::vector<std::string> args = {"-p", "8097", "-x", "10", "-y", "10", "-n", "TEST", "TEST1", "-c", "10"};
    cr_assert_none_throw(Zappy::Server tmp(args));
}

Test(BasicC, testArgs)
{
    std::vector<std::string> args = {"-p", "8098", "-x", "10", "-y", "10", "-n", "TEST", "TEST1", "-f", "100"};
    cr_assert_none_throw(Zappy::Server tmp(args));
}

Test(BasicAll, testArgs)
{
    std::vector<std::string> args = {};
    cr_assert_none_throw(Zappy::Server tmp(args));
}