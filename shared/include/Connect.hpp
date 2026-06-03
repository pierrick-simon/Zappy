/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Connect
*/

#ifndef CONNECT_HPP
    #define CONNECT_HPP

#include <vector>
#include "SharedException.hpp"

namespace Shared {
    class Connect {
        public:
            Connect(int port);
            Connect(int port, std::string ip);

            ~Connect();

            int getFd() const {return _fd;}

            int acceptClient();
            void addClient(int fd);
            void removeClient(int fd);

            std::vector<int> infoToRead();

            template<typename T>
            static void send(int fd, const T msg)
            {
                if (write(fd, &msg, sizeof(T)) < 0)
                    throw SendException();
            }

            template<typename T>
            static T receive(int fd)
            {
                T buf = {};
                if (read(fd, &buf, sizeof(T)) <= 0)
                    throw CloseException();
                return buf;
            }

            static void receiveChunk(int fd, std::string &str, std::size_t = 4096);

            class ConnectException : public SharedException {
                public:
                    ConnectException(std::string str)
                        : SharedException("Connect Error: " + str) {};
            };

            class SocketException : public ConnectException {
                public:
                    SocketException() : ConnectException("Socket Failed!") {};
            };

            class BindException : public ConnectException {
                public:
                    BindException() : ConnectException("Bind Failed!") {};
            };

            class ListenException : public ConnectException {
                public:
                    ListenException() : ConnectException("Listen Failed!") {};
            };

            class ConnectionException : public ConnectException {
                public:
                    ConnectionException() : ConnectException("Connection Failed!") {};
            };

            class AcceptException : public ConnectException {
                public:
                    AcceptException() : ConnectException("Accept Failed!") {};
            };

            class PollException : public ConnectException {
                public:
                    PollException() : ConnectException("Poll Failed!") {};
            };

            class SendException : public ConnectException {
                public:
                    SendException() : ConnectException("Send Failed!") {};
            };

            class CloseException : public ConnectException {
                public:
                    CloseException() : ConnectException("Close Connection!") {};
            };

        private:
            void initSocket();
            void initBind(int port);
            void initListen();
            void connectToServer(int port, std::string ip);

            int _fd = -1;
            std::vector<struct pollfd> _fds;

            static constexpr int QUEUE_LENGTH = 10;
    };
};

#endif