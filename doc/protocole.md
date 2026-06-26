# Zappy Communication Protocol

## Part 1 — GUI / Server Communication

### Connection Handshake

Server sends WELCOME, client responds with team name:
```
<- WELCOME\n
    -> GRAPHIC\n
```

### Commands List (Client → Server)

```
msz                                    -> request map size

bct [X] [Y]                            -> request content of tile at (X, Y)

mct                                    -> request content of all tiles

tna                                    -> request name of all teams

ppo #[n]                               -> request player position

plv #[n]                               -> request player level

pin #[n]                               -> request player inventory

sgt                                    -> request current time unit

sst [T]                                -> set time unit to T
```
### Server Responses (Server → Client)
```
Map
    msz ->
        <- msz X Y\n
    
    bct X Y ->
        <- bct X Y q0 q1 q2 q3 q4 q5 q6\n

    mct ->
        <- bct X Y q0 q1 q2 q3 q4 q5 q6\n  (repeated for each tile)
Teams
    tna ->
        <- tna N\n  (repeated for each team)

Players
    ppo #n ->
        <- ppo #n X Y O\n

    plv #n ->
        <- plv #n L\n

    pin #n ->
        <- pin #n X Y q0 q1 q2 q3 q4 q5 q6\n

Time
    sgt ->
        <- sgt T\n

    sst T ->
    <- sst T\n
```

### Server Push Events (unsolicited, Server → Client)

```
Player events
    <- pnw #n X Y O L N\n              -> new player connection

    <- pex #n\n                        -> player expulsion

    <- pbc #n M\n                      -> player broadcast

    <- pdi #n\n                        -> player death

    <- pfk #n\n                        -> player laying egg

    <- pdr #n i\n                      -> player dropped resource i

    <- pgt #n i\n                      -> player collected resource i

Incantation events
    <- pic X Y L #n #n ...\n           -> incantation started

    <- pie X Y R\n                     -> incantation ended (R: 0=fail, 1=success)

Egg events
    <- enw #e #n X Y\n                 -> egg laid by player

    <- ebo #e\n                        -> egg hatched (player connected)

    <- edi #e\n                        -> egg destroyed

Game events
    <- seg N\n                         -> end of game, team N wins

    <- smg M\n                         -> server message

Errors
    <- suc\n                           -> unknown command

    <- sbp\n                           -> bad command parameters
```

### Symbol Reference
```
X, Y        map width / height or tile coordinates

n           player number (prefixed with #)

e           egg number (prefixed with #)

O           orientation: 1(N), 2(E), 3(S), 4(W)

L           player or incantation level (1–8)

T           time unit (frequency f)

N           team name

R           incantation result: 0=failure, 1=success

M           message string

i           resource index (0=food, 1=linemate, 2=deraumere,

3=sibur, 4=mendiane, 5=phiras, 6=thystame)

q0..q6      quantity of each resource on a tile
```

---

## Part 2 — AI Client / Server Communication

### Connection Handshake
```
<- WELCOME\n
    -> TEAM-NAME\n
    <- CLIENT-NUM\n
    <- X Y\n
```

*CLIENT-NUM is the number of available slots for the team. X and Y are the world dimensions.*

### Commands List (Client → Server)

```
Movement
    Forward                            -> move forward one tile

    Right                              -> turn 90° right

    Left                               -> turn 90° left

Vision & Info
    Look                               -> look around (returns visible tiles)

    Inventory                          -> show current inventory

    Connect_nbr                        -> number of available team slots

Resources
    Take [object]                      -> pick up an object from current tile

    Set [object]                       -> drop an object on current tile

Communication
    Broadcast [text]                   -> send message to all players

Reproduction
    Fork                               -> lay an egg (adds a team slot)

    Eject                              -> push all players off current tile

Elevation
    Incantation                        -> start the elevation ritual
```
### Server Responses (Server → Client)
```
Movement
    Forward / Right / Left ->
        <- ok\n

Vision & Info
    Look ->
        <- [tile0_content, tile1_content, ...]\n

    Inventory ->
        <- [food n, linemate n, deraumere n, sibur n, mendiane n, phiras n, thystame n]\n

    Connect_nbr ->
        <- value\n

Resources
    Take / Set ->
        <- ok\n
        <- ko\n

Communication
    Broadcast ->
        <- ok\n

Reproduction
    Fork ->
        <- ok\n

    Eject ->
        <- ok\n
        <- ko\n

Elevation
    Incantation ->
        <- Elevation underway\n
        <- Current level: k\n
        <- ko\n

Death
    (no command) ->
        <- dead\n

Incoming events (while playing)
    <- dead\n                          -> player died
    
    <- message K, text\n               -> broadcast received from tile direction K

    <- eject: K\n                      -> ejected from tile, coming from direction K

Errors
    <- ko\n                            -> unknown or bad command
```
### Command Timing Reference
```
action              command         time cost

move forward        Forward         7 / f

turn right          Right           7 / f

turn left           Left            7 / f

look around         Look            7 / f

inventory           Inventory       1 / f

broadcast           Broadcast text  7 / f

fork                Fork            42 / f

eject               Eject           7 / f

take object         Take object     7 / f

set object down     Set object      7 / f

incantation         Incantation     300 / f
```

*f is the frequency parameter passed to the server at launch. Default: f=100.*

### Notes

- All commands end with \n
- The client may queue up to 10 commands without waiting for responses
- Commands beyond 10 in the queue are discarded by the server
- The server executes commands in the order received
- A command only blocks the player who issued it, not the server
- Bad or unknown commands always return ko\n