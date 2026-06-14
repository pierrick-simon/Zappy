/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** GUIEvents
*/

#ifndef GUIEVENTS_HPP
    #define GUIEVENTS_HPP

    #include "BroadcastEvent.hpp"
    #include "EggLaidEvent.hpp"
    #include "EndIncantationEvent.hpp"
    #include "GUICommunication.hpp"
    #include "IdEvent.hpp"
    #include "MapSizeEvent.hpp"
    #include "NbEvent.hpp"
    #include "NewPlayerEvent.hpp"
    #include "PlayerInventoryEvent.hpp"
    #include "PlayerLevelEvent.hpp"
    #include "PlayerPositionEvent.hpp"
    #include "ResourceEvent.hpp"
    #include "StartIncantationEvent.hpp"
    #include "TeamNameEvent.hpp"
    #include "TileInfoEvent.hpp"

namespace Shared {

    namespace ServerCmd = Shared::GUICommunication::Server;

    class PlayerExpulsionEvent : public IdEvent {
    public:
        PlayerExpulsionEvent(std::size_t id) :
            IdEvent(ServerCmd::PEX, id) {};
        PlayerExpulsionEvent() :
            IdEvent(ServerCmd::PEX) {};
    };

    class EggLayingEvent : public IdEvent {
    public:
        EggLayingEvent(std::size_t id) :
            IdEvent(ServerCmd::PFK, id) {};
        EggLayingEvent() :
            IdEvent(ServerCmd::PFK) {};
    };

    class PlayerDeathEvent : public IdEvent {
    public:
        PlayerDeathEvent(std::size_t id) :
            IdEvent(ServerCmd::PDI, id) {};
        PlayerDeathEvent() :
            IdEvent(ServerCmd::PDI) {};
    };

    class EggHatchedEvent : public IdEvent {
    public:
        EggHatchedEvent(std::size_t id) :
            IdEvent(ServerCmd::EBO, id) {};
        EggHatchedEvent() :
            IdEvent(ServerCmd::EBO) {};
    };

    class EggDestroyEvent : public IdEvent {
    public:
        EggDestroyEvent(std::size_t id) :
            IdEvent(ServerCmd::EDI, id) {};
        EggDestroyEvent() :
            IdEvent(ServerCmd::EDI) {};
    };

    class SetResourceEvent : public ResourceEvent {
    public:
        SetResourceEvent(std::size_t id, std::size_t nb) :
            ResourceEvent(ServerCmd::PDR, id, nb) {};
        SetResourceEvent() :
            ResourceEvent(ServerCmd::PDR) {};
    };

    class TakeResourceEvent : public ResourceEvent {
    public:
        TakeResourceEvent(std::size_t id, std::size_t nb) :
            ResourceEvent(ServerCmd::PGT, id, nb) {};
        TakeResourceEvent() :
            ResourceEvent(ServerCmd::PGT) {};
    };

    class GetTimeUnit : public NbEvent {
    public:
        GetTimeUnit(std::size_t id) :
            NbEvent(ServerCmd::SGT, id) {};
        GetTimeUnit() :
            NbEvent(ServerCmd::SGT) {};
    };

    class SetTimeUnit : public NbEvent {
    public:
        SetTimeUnit(std::size_t id) :
            NbEvent(ServerCmd::SST, id) {};
        SetTimeUnit() :
            NbEvent(ServerCmd::SST) {};
    };
} // namespace Shared

#endif
