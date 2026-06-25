# Zappy (v0.1)

### Development

By *Pierrick Simon*(pierrick.simon@epitech.eu), *Natan Pereira*(natan.pereira@epitech.eu), *Armand Lecomte*(armand.lecomte@epitech.eu), *Ryan Ouerdane*(ryan.ouerdane@epitech.eu) & *Ariel Amriou*(ariel.amriou@epitech.eu).

## Context

This project has been done as the final project of the second year at Epitech. If you with to see the specifications document, take a look at the [Documentation](#documentation)

## Objective

The objective of this project is to create a complexe simulation of a planet and it's inhabitant, the trantorian. The goal of the trantorian is to make their team win by passing level 8 (level incrementation is done by doing an incentation to ascend, requiring ressources and team members)

Zappy is divided in 3 distincts but interdependant parts:
- Server: The server orchestrate the two following parts, handling connections and server simulation.
- IA: The IA client, when connected to the server, makes an egg on the map hatch and take control of the given player, using differents strategys to ascend to level 8 and win the game
- GUI: This part allow the user, when connected to the server, to see what is happening on the map, with a lot of usfull information.

## Getting Started

### Prerequisites

This project requires the following dependencies:

- **Programming Language:** Python & c++
- **Package Manager:** pip
- **Compilation Manager:** make & Cmake

### Installation for Linux

1. **Clone the repository:**

```sh
git clone git@github.com:pierrick-simon/Zappy.git 
```

2. **Navigate to the project directory:**

```sh
cd Zappy
```

### Usage


1. **Compile the project and install depedencies:**

```sh
make
```

2. **To know what parameters can be used for each binary:**

```sh
./zappy_server --help
```

```sh
./zappy_gui --help
```

```sh
./zappy_ia --help
```

#### Master Mode

1. **Launch the server using master mode:**

```sh
./zappy_server -m
```

#### Manual Mode

1. **Launch the server using manual mode:**

```sh
./zappy_server
```

2. **Launch as many IA clients as you wish:**

```sh
./zappy_ia
```

2. **Launch the GUI client:**

```sh
./zappy_gui
```


## Documentation

[Specifications](doc/G-YEP-400_zappy.pdf) \
[GUI protocol specification](doc/G-YEP-400_zappy_GUI_protocol.pdf)

## License

This project is licensed under the **MIT License**.

![START TREK License : MIT](https://img.shields.io/badge/License-MIT-blue.svg)
