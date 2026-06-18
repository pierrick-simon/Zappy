/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Connect
*/

#include "Connect.hpp"
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

namespace Shared {
    Connect::Connect(int port)
    {
        initSocket();
        initBind(port);
        initListen();
        addClient(_fd);
    }

    Connect::Connect(int port, const std::string &ip)
    {
        initSocket();
        connectToServer(port, ip);
        addClient(_fd);
    }

    Connect::~Connect()
    {
        while (!_fds.empty())
            removeClient(_fds[0].fd);
    }

    void Connect::initSocket()
    {
        _fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (_fd == -1)
            throw SocketException();
    }

    void Connect::initBind(int port) const
    {
        struct sockaddr_in server_addr = {};
        int opt = 1;

        setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        server_addr.sin_addr.s_addr = INADDR_ANY;
        if (bind(_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) ==
            -1)
            throw BindException();
    }

    void Connect::initListen() const
    {
        if (listen(_fd, QUEUE_LENGTH) == -1)
            throw ListenException();
    }

    void Connect::connectToServer(int port, const std::string &ip) const
    {
        struct sockaddr_in server_addr = {};

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        server_addr.sin_addr.s_addr = inet_addr(ip.c_str());
        if (connect(_fd,
                (struct sockaddr *) &server_addr,
                sizeof(server_addr)) == -1)
            throw ConnectionException();
    }

    int Connect::acceptClient() const
    {
        struct sockaddr_in client_addr = {};
        socklen_t client_len = sizeof(client_addr);
        int client_fd =
            accept(_fd, (struct sockaddr *) &client_addr, &client_len);
        if (client_fd == -1)
            throw AcceptException();
        return client_fd;
    }

    void Connect::addClient(int fd)
    {
        struct pollfd structFd = {};

        structFd.fd = fd;
        structFd.events = POLLIN;
        _fds.emplace_back(structFd);
    }

    std::vector<int> Connect::infoToRead(int timeout)
    {
        std::vector<int> info;

        if (poll(_fds.data(), _fds.size(), timeout) < 0) {
            if (errno == EINTR)
                return info;
            throw PollException();
        }
        for (auto &pfd : _fds) {
            if (pfd.revents & (POLLIN | POLLHUP | POLLERR))
                info.push_back(pfd.fd);
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

    void Connect::send(int fd, const std::string &msg)
    {
        if (write(fd, msg.c_str(), msg.size()) < 0)
            throw SendException();
    }

    void Connect::receiveChunk(int fd, std::string &str, std::size_t size)
    {
        char buf[size];
        ssize_t n = read(fd, buf, sizeof(buf));
        if (n <= 0)
            throw Shared::Connect::CloseException();
        str.append(buf, n);
    }

    std::string Connect::getIp()
    {
        std::string ip;
        struct ifaddrs *interfaces = {};
        struct ifaddrs *ifa = {};
        if (getifaddrs(&interfaces) == -1)
            throw GetAddrsException();
        for (ifa = interfaces; ifa != nullptr; ifa = ifa->ifa_next) {
            if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET) {
                auto *addr = (struct sockaddr_in *) ifa->ifa_addr;
                ip = inet_ntoa(addr->sin_addr);
            }
        }
        freeifaddrs(interfaces);
        return ip;
    }
} // namespace Shared
