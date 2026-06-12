##
## EPITECH PROJECT, 2026
## makefile
## File description:
## root makefile
##

NAME_AI = zappy_ai

AI_DIR = ai/zappy_ai.py

CMAKE_DIRECTORY := ./build
CMAKE_DIRECTORY_DEBUG := ./build_debug

CMAKE := $(shell which cmake)

CMAKE_MAKEFILE := $(CMAKE_DIRECTORY)/Makefile
CMAKE_MAKEFILE_DEBUG := $(CMAKE_DIRECTORY_DEBUG)/Makefile

CMAKE_ARGS = -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang \
 			-DCMAKE_BUILD_TYPE="Release"

all:	lib	$(CMAKE_MAKEFILE) $(NAME_AI)
	$(CMAKE) --build $(CMAKE_DIRECTORY)

debug:	lib $(CMAKE_MAKEFILE_DEBUG) $(NAME_AI)
	$(CMAKE) --build $(CMAKE_DIRECTORY_DEBUG)

$(CMAKE_MAKEFILE):
	mkdir -p $(CMAKE_DIRECTORY)
	cd $(CMAKE_DIRECTORY) && $(CMAKE) -S .. $(CMAKE_ARGS)

$(CMAKE_MAKEFILE_DEBUG):
	mkdir $(CMAKE_DIRECTORY_DEBUG)
	cd $(CMAKE_DIRECTORY_DEBUG) && $(CMAKE) -S .. -DCMAKE_BUILD_TYPE="Debug"

$(NAME_AI):
	ln -s $(AI_DIR) $(NAME_AI)

clean:
	$(RM) $(NAME_AI)
	$(CMAKE) --build $(CMAKE_DIRECTORY) --target clean

fclean: clean
	$(RM) -r $(CMAKE_DIRECTORY)
	$(RM) -r $(CMAKE_DIRECTORY_DEBUG)

%: $(CMAKE_MAKEFILE)
	$(CMAKE) --build $(CMAKE_DIRECTORY) --target $@

lib:
	$(CMAKE) --build $(CMAKE_DIRECTORY) --target shared

.PHONY: all debug clean fclean lib
