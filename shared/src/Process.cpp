/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Process
*/

#include "Process.hpp"
#include <unistd.h>

namespace Shared {
    Process::~Process()
    {
        for (pid_t pid : pids) {
            kill(pid, SIGTERM);
            waitpid(pid, nullptr, 0);
        }
    }

    void Process::add(
        const std::string &program, const std::vector<std::string> &args)
    {
        pid_t pid = fork();

        if (pid < 0)
            throw ForkException();
        if (pid == 0) {
            std::vector<char *> av;
            av.push_back(const_cast<char *>(program.c_str()));
            for (const auto &a : args)
                av.push_back(const_cast<char *>(a.c_str()));
            av.push_back(nullptr);
            if (execvp(program.c_str(), av.data()) == -1)
                throw ExecvpException();
            _exit(0);
        }
        pids.push_back(pid);
    }

    void Process::wait()
    {
        for (pid_t pid : pids)
            waitpid(pid, nullptr, 0);
        pids.clear();
    }
} // namespace Shared
