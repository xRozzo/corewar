##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## This is just a Makefile but v2
##

BINARY = corewar
TEST_BINARY = tests_run
SOURCES = sources
LIBRARY_DIR = library
INCLUDE = include
LIBRARY = libmy.a

CC = gcc
ECHO=echo

ifeq ($(shell uname -s), Linux)
	ECHO := echo -e
endif

DEP_FLAGS = -MP -MD
C_FLAGS = -Wall -Wextra -g $(foreach F,$(INCLUDE),-I$(F)) $(DEP_FLAGS)

C_SOURCES = $(foreach C,$(SOURCES),$(wildcard $(C)/*.c))

OBJECTS = $(patsubst %.c,%.o,$(C_SOURCES))
DEPS = $(patsubst %.c,%.d,$(C_SOURCES))

RST = \033[0m
CYAN = \033[36m
PINK = \033[37;1m
GREEN = \033[0;32m
CORAL = \033[0;31m
ORANGE = \033[0;33m
MAGENTA = \033[0;35m

all: $(BINARY)

$(BINARY): $(OBJECTS)
	@$(ECHO) "- $(CYAN)Building $(ORANGE)$(BINARY) $(CYAN)binary$(RST)"
	@$(CC) -o $@ $^ -L.. -lmy

%.o: %.c
	@$(ECHO) "- $(MAGENTA)$<$(RST) -> $(GREEN)$@$(RST)"
	@if [ "$(MAKECMDGOALS)" = "$(TEST_BINARY)" ]; then \
		$(CC) $(TESTING_MACRO) $(C_FLAGS) -c -o $@ $< $(COVERAGE); \
	else \
		$(CC) $(C_FLAGS) -c -o $@ $<; \
	fi

clean:
	@$(ECHO) "- $(CORAL)Cleaning objects + deps$(RST)"
	@rm -rf $(OBJECTS) $(DEPS)

fclean:
	@$(ECHO) "- $(PINK)Cleaning objects + deps + binary$(RST)"
	@rm -rf $(BINARY) $(OBJECTS) $(DEPS)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re $(TEST_BINARY)
