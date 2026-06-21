/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Process
*/

#ifndef PROCESS_HPP
    #define PROCESS_HPP

    #include <exception>
    #include <string>
    #include <sys/wait.h>
    #include <vector>
    #include "SharedException.hpp"

namespace Shared {
    class Process {
    public:
        Process() = default;
        ~Process();

        Process(const Process &) = delete;
        Process &operator=(const Process &) = delete;

        void add(
            const std::string &program, const std::vector<std::string> &args);
        void wait();

        class ProcessException : public SharedException {
        public:
            ProcessException(const std::string &str) :
                SharedException("Connect Error: " + str) {};
        };

        class ForkException : public ProcessException {
        public:
            ForkException() :
                ProcessException("Fork Failed!") {};
        };

        class ExecvpException : public ProcessException {
        public:
            ExecvpException() :
                ProcessException("Execvp Failed!") {};
        };

    private:
        std::vector<pid_t> pids;
    };
} // namespace Shared

#endif
