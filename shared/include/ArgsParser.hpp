/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** ArgParser
*/

#ifndef ARGPARSER_HPP_
    #define ARGPARSER_HPP_

    #include <exception>
    #include <iomanip>
    #include <optional>
    #include <string>
    #include <vector>

namespace Parser{
    class ArgsParserError : public std::exception {
        public:
            ArgsParserError(const std::string &msg): _msg("Arguments error: " + msg) {};

            [[nodiscard]] const char *what() const noexcept override
            {
                return _msg.data();
            };
        private:
            std::string _msg;
    };

    class MissingArgError : public ArgsParserError {
        public:
            MissingArgError(const std::string &flag): ArgsParserError(flag + " argument is mendatory") {};
    };

    class ArgsParser {
    public:
        static bool isArg(std::reference_wrapper<std::vector<std::string>> args,
            const std::string &flag);

        template<typename T>
        static std::optional<T> get(
            std::reference_wrapper<std::vector<std::string>> args,
            const std::string &flag)
        {
            for (auto arg = args.get().begin(); arg != args.get().end();
                ++arg) {
                if (*arg == flag && arg + 1 != args.get().end()) {
                    T tmp;
                    std::istringstream(*(arg + 1)) >> tmp;
                    args.get().erase(arg);
                    args.get().erase(arg);
                    return tmp;
                }
                if (*arg == flag)
                    throw ArgsParserError(flag);
            }
            return {};
        }

        template<typename T>
        static T getArg(
            std::reference_wrapper<std::vector<std::string>> args,
            const std::string &flag, T fallBack) {
            auto item = get<T>(args, flag);
            auto ret = fallBack;
            if (item.has_value())
                ret = item.value();
            return ret;
        };

        template<typename T>
        static T getArg(
            std::reference_wrapper<std::vector<std::string>> args,
            const std::string &flag) {
            auto item = get<T>(args, flag);
            if (!item.has_value())
                throw MissingArgError(flag);
            return item.value();
        };

        template<typename T>
        static std::vector<T> getArgList(
            std::reference_wrapper<std::vector<std::string>> args,
            const std::string &flag)
        {
            std::vector<T> final;
            auto arg = args.get().begin();
            for (;arg != args.get().end(); ++arg) {
                if (*arg == flag) {
                    args.get().erase(arg);
                    break;
                }
            }
            while (arg != args.get().end()) {
                if (arg->rfind("-", 0) == 0)
                    break;
                T tmp;
                std::istringstream(*(arg)) >> tmp;
                args.get().erase(arg);
                final.emplace_back(tmp);
            }
            return final;
        }
    };
}

#endif /* !ARGPARSER_HPP_ */
