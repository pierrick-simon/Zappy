/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** GUICommunication
*/

#ifndef GUICOMMUNICATION_HPP
    #define GUICOMMUNICATION_HPP

    #include "Command.hpp"

namespace Shared {
    namespace GUICommunication {
        namespace Client {
            static const Command MSZ("msz");
            static const Command BCT("bct");
            static const Command MCT("mct");
            static const Command TNA("tna");
            static const Command PPO("ppo");
            static const Command PLV("plv");
            static const Command PIN("pin");
            static const Command SGT("sgt");
            static const Command SST("sst");
        }; // namespace Client

        namespace Server {
            static const Command MSZ("msz");
            static const Command BCT("bct");
            static const Command MCT("mct");
            static const Command TNA("tna");
            static const Command PNW("pnw");
            static const Command PPO("ppo");
            static const Command PLV("plv");
            static const Command PIN("pin");
            static const Command PEX("pex");
            static const Command PBC("pbc");
            static const Command PIC("pic");
            static const Command PIE("pie");
            static const Command PFK("pfk");
            static const Command PDR("pdr");
            static const Command PGT("pgt");
            static const Command PDI("pdi");
            static const Command ENW("enw");
            static const Command EGG("egg");
            static const Command EBO("ebo");
            static const Command EDI("edi");
            static const Command SGT("sgt");
            static const Command SST("sst");
            static const Command SEG("seg");
            static const Command SMG("smg");
            static const Command SUC("suc");
            static const Command SBP("spb");
        }; // namespace Server
    }; // namespace GUICommunication
} // namespace Shared

#endif
