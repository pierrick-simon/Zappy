##
## EPITECH PROJECT, 2026
## Zappy
## File description:
## AI list
##
from src.algorithms.common import CommonAI
from src.algorithms.Survivor import SurvivalAI
from src.algorithms.Human import HumanAI


AI_LIST = {
    "survivor": SurvivalAI,
    "common": CommonAI,
}
