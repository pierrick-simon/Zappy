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
            static const Command FWD("forward");
            static const Command RGT("right");
            static const Command LFT("left");
            static const Command LK("look");
            static const Command IVT("inventory");
            static const Command BDT("broadcast");
            static const Command CNT("connect_nbr");
            static const Command FRK("fork");
            static const Command EJT("eject");
            static const Command TKO("take object");
            static const Command STO("set object");
            static const Command ICT("incantation");
        };

        namespace Server {
            static const Command OK("ok");
            static const Command KO("ko");
            static const Command DEAD("dead");
        };
   };
}

#endif
