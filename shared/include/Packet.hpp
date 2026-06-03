/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Packet
*/

#ifndef PACKET_HPP
    #define PACKET_HPP

    #include <cstring>
    #include <stdexcept>
    #include <stdint.h>
    #include "SharedException.hpp"

namespace Shared {
    template<std::size_t S>
    class Packet {
        public:
            template<typename T>
            Packet &operator<<(const T &val)
            {
                if (_writePos + sizeof(T) > S)
                    throw FullException();
                std::memcpy(_data + _writePos, &val, sizeof(T));
                _writePos += sizeof(T);
                return *this;
            }

            template<typename T>
            Packet &operator>>(T &val)
            {
                if (_readPos + sizeof(T) > _writePos)
                    throw NotEnoughException();
                std::memcpy((void*)&val, _data + _readPos, sizeof(T));
                _readPos += sizeof(T);
                return *this;
            }

            class PacketException : public SharedException {
                public:
                    PacketException(std::string str)
                        : SharedException("Packet Error: " + str) {};
            };

            class FullException : public PacketException {
                public:
                    FullException() : PacketException("Buffer full.") {};
            };

            class NotEnoughException : public PacketException {
                public:
                    NotEnoughException() : PacketException("Not enough data.") {};
            };

        private:
            uint8_t _data[S] = {};
            std::size_t _writePos = 0;
            std::size_t _readPos  = 0;
    };
}

#endif