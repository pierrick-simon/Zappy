/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Connect
*/

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include "Connect.hpp"

namespace Shared {
    Connect::Connect(int port)
    {
        initSocket();
        initBind(port);
        initListen();
        addClient(_fd);
    }

    Connect::Connect(int port, std::string ip)
    {
        initSocket();
        connectToServer(port, ip);
        addClient(_fd);
    }

    Connect::~Connect()
    {
        if (_fd != -1)
            close(_fd);
    }

    void Connect::initSocket()
    {
        _fd = socket(AF_INET, SOCK_STREAM, 0);
        if (_fd == -1)
            throw SocketException();
    }

    void Connect::initBind(int port)
    {
        struct sockaddr_in server_addr = {};
        int opt = 1;

        setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        server_addr.sin_addr.s_addr = INADDR_ANY;
        if (bind(_fd, (struct sockaddr *)&server_addr,
                sizeof(server_addr)) == -1)
            throw BindException();
    }

    void Connect::initListen()
    {
        if (listen(_fd, QUEUE_LENGTH) == -1)
            throw ListenException();
    }

    void Connect::connectToServer(int port, std::string ip)
    {
        struct sockaddr_in server_addr;

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        server_addr.sin_addr.s_addr = inet_addr(ip.c_str());
        if (connect(_fd, (struct sockaddr *)&server_addr,
                sizeof(server_addr)) == -1)
            throw ConnectionException();
    }

    int Connect::acceptClient()
    {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(_fd,
            (struct sockaddr *)&client_addr, &client_len);
        if (client_fd == -1)
            throw AcceptException();
        return client_fd;
    }

    void Connect::addClient(int fd)
    {
        struct pollfd structFd;

        structFd.fd = fd;
        structFd.events = POLLIN;
        _fds.emplace_back(structFd);
    }

    std::vector<int> Connect::infoToRead()
    {
        std::vector<int> info;

        if (poll(_fds.data(), _fds.size(), 0) < 0)
            throw PollException();
        for (std::size_t i = 0; i < _fds.size(); ++i) {
            if (_fds[i].revents & POLLIN)
                info.push_back(_fds[i].fd);
        }
        return info;
    }

    void Connect::removeClient(int fd)
    {
        for (auto iter = _fds.begin(); iter < _fds.end(); iter++) {
            if (iter->fd == fd) {
                close(iter->fd);
                _fds.erase(iter);
                break;
            }
        }
    }
}
