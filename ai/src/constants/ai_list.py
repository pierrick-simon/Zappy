##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## AI list
##
from src.algorithms.test import Joiner, Broadcaster
from src.algorithms.common import CommonAI
from src.algorithms.Survivor import SurvivalAI


AI_LIST = {
    "survivor": SurvivalAI,
    "common": CommonAI,
    "join": Joiner,
    "brod": Broadcaster
}
