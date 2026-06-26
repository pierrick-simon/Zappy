##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## AI list
##

from typing import Any

from src.algorithms.Ejector import EjectorAi
from src.algorithms.Randomizer import RandomizerAi
from src.algorithms.Layer import LayerAi
from src.algorithms.Survivor import SurvivalAI
from src.algorithms.Human import HumanAI
from src.algorithms.Villager import Villager
from src.algorithms.common import CommonAI
from src.algorithms.Worker import WorkerAi


AI_LIST: dict[str, Any] = {
    "common": CommonAI,
    "villager": Villager,
    "survivor": SurvivalAI,
    "human": HumanAI,
    "layer": LayerAi,
    "randomizer": RandomizerAi,
    "worker": WorkerAi,
    "ejector": EjectorAi,
}
