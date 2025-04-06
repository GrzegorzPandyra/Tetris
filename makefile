#
# Makefile created based on auto-generated makefile from arduino IDE
# (c) Grzegorz Pandyra 2025
#

#folders
PROJECT_ROOT=.
OUT_DIR	 = $(PROJECT_ROOT)/out
SRC_DIR  = $(PROJECT_ROOT)/src

#assemble list of source files
SRC_LIST += $(wildcard $(SRC_DIR)/*.c)
SRC_LIST += $(wildcard $(SRC_DIR)/ui/*.c)
SRC_LIST += $(wildcard $(SRC_DIR)/input/*.c)
SRC_LIST += $(wildcard $(SRC_DIR)/log/*.c)
SRC_LIST += $(wildcard $(SRC_DIR)/engine/*.c)

#assemble list of include directories
INCLUDE_DIR += -I $(SRC_DIR)
INCLUDE_DIR += -I $(SRC_DIR)/ui
INCLUDE_DIR += -I $(SRC_DIR)/input
INCLUDE_DIR += -I $(SRC_DIR)/log
INCLUDE_DIR += -I $(SRC_DIR)/engine

#compiler
CC=gcc
CFLAGS= -Wall -O0 -ggdb -std=c2x 
LIB= -lncurses
DEFINES = 	-D DUMMY_DEFINE_1 \
			-D _POSIX_C_SOURCE=200809L \

#default rule
all: clean tetris print_ok

#compile project Minisumo IV into .elf file
tetris: 
	$(info  ********************************************************************************************************* )
	$(info 	Building target: $@)
	$(info List of file to be build:)
	$(foreach file, $(SRC_LIST),  $(info $(file)))
	@$(CC) $(SRC_LIST) $(LIB) $(INCLUDE_DIR) $(CFLAGS) $(DEFINES) -o $(OUT_DIR)/$@
	$(info OK	Finished building target: $@)


#compile project Minisumo IV into .elf file
debug: 
	$(info  ********************************************************************************************************* )
	$(info 	Building target: $@)
	$(info List of file to be build:)
	$(foreach file, $(SRC_LIST),  $(info $(file)))
	@$(CC) $(SRC_LIST) $(LIB) $(INCLUDE_DIR) $(CFLAGS) $(DEFINES) -D _DEBUG -o $(OUT_DIR)/$@
	$(info OK	Finished building target: $@)

#make clean
clean:
	@rm -f $(OUT_DIR)/*
	$(info ### Clean finished! ###)

#just decoration
print_ok:
	@echo '					              ____'
	@echo '					            /____ `\'
	@echo '					           ||_  _`\ \'
	@echo '					     .-.   `|O, O  ||'
	@echo '					     | |    (/    -)\'
	@echo '					     | |    |`- ` |\`'
	@echo '					  __/  |    | _/  |'
	@echo '					 (___) \.  _.\__. `\___'
	@echo '					 (___)  )\/  \    _/  ~\.'
	@echo '					 (___) . \   `--  _   `\	'
	@echo '					  (__)-    ,/        (   |'
	@echo '					       `--~|         |   |'
	@echo '					           |         |   |'
	@echo '				******                             ******'
	@echo '				****  Finished building all targets  ****'
	@echo '				******                             ******'


