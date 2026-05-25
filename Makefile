##
## EPITECH PROJECT, 2026
## makefile
## File description:
## root makefile
##

NAME_AI = zappy_ai

AI_DIR = ai/zappy_ai.py

CMAKE_DIRECTORY := ./build

CMAKE := $(shell which cmake)

CMAKE_MAKEFILE := $(CMAKE_DIRECTORY)/Makefile

all:	$(CMAKE_MAKEFILE) $(NAME_AI)
	$(CMAKE) --build $(CMAKE_DIRECTORY)

$(CMAKE_MAKEFILE):
	mkdir $(CMAKE_DIRECTORY)
	cd $(CMAKE_DIRECTORY) && $(CMAKE) -S ..

$(NAME_AI):
	ln -s $(AI_DIR) $(NAME_AI)

clean:
	$(RM) $(NAME_AI)
	$(CMAKE) --build $(CMAKE_DIRECTORY) --target clean
	$(RM) -rf $(CMAKE_DIRECTORY)

%: $(CMAKE_MAKEFILE)
	$(CMAKE) --build $(CMAKE_DIRECTORY) --target $@

.PHONY: all clean
