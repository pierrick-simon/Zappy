/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** AICommunication
*/

#ifndef AICOMMUNICATION_HPP
    #define AICOMMUNICATION_HPP

    #include "Command.hpp"

namespace Shared {
    namespace AICommunication {
        namespace Client {
            static const Command FWD("Forward");
            static const Command RGT("Right");
            static const Command LFT("Left");
            static const Command LK("Look");
            static const Command IVT("Inventory");
            static const Command BDT("Broadcast");
            static const Command CNT("Connect_nbr");
            static const Command FRK("Fork");
            static const Command EJT("Eject");
            static const Command TKO("Take");
            static const Command STO("Set");
            static const Command ICT("Incantation");
        }; // namespace Client

        namespace Server {
            static const Command OK("ok");
            static const Command KO("ko");
            static const Command EJT("eject");
            static const Command MSG("message");
            static const Command EU("Elevation underway");
            static const Command CL("Current level");
            static const Command DEAD("dead");
        }; // namespace Server
    }; // namespace AICommunication
} // namespace Shared

#endif
