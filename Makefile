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

VM_DIR = corewar
AS_DIR = asm

CC = gcc
ECHO=echo

ifeq ($(shell uname -s), Linux)
	ECHO := echo -e
endif

COVERAGE = --coverage
TEST_FLAGS = $(COVERAGE) -lcriterion
TESTING_MACRO = -D__COREWAR_TEST

C_SOURCES = $(foreach C,$(SOURCES),$(wildcard $(C)/*.c))

L_SOURCES = $(wildcard $(LIBRARY_DIR)/*.c)
L_OBJECTS = $(patsubst %.c,%.o,$(L_SOURCES))
L_DEPS = $(patsubst %.c,%.d,$(L_SOURCES))

TEST_SOURCES = $(wildcard tests/*.c)
TEST_OBJECTS = $(patsubst %.c,%.o,$(TEST_SOURCES))
T_DEPS = $(patsubst %.c,%.d,$(TEST_SOURCES))

CRITERION = $(C_SOURCES:.c=.gcda) $(C_SOURCES:.c=.gcno)
CRITERION += $(L_SOURCES:.c=.gcda) $(L_SOURCES:.c=.gcno)
CRITERION += $(TEST_SOURCES:.c=.gcda) $(TEST_SOURCES:.c=.gcno)

RST = \033[0m
CYAN = \033[36m
PINK = \033[37;1m
GREEN = \033[0;32m
CORAL = \033[0;31m
ORANGE = \033[0;33m
MAGENTA = \033[0;35m

all: $(BINARY)

$(BINARY): $(LIBRARY)
	@$(ECHO) "- $(CYAN)Building $(ORANGE)$(BINARY) $(CYAN)binary$(RST)"
	@$(MAKE) -C $(AS_DIR)
	@$(MAKE) -C $(VM_DIR)

$(LIBRARY): $(L_OBJECTS)
	@$(ECHO) "- $(CYAN)Building library $(ORANGE)$(LIBRARY) \
	$(CYAN)archive$(RST)"
	@ar rc $@ $^

$(LIBRARY_DIR)/%.o: $(LIBRARY_DIR)/%.c
	@$(CC) $(C_FLAGS) -c -o $@ $<;

clean:
	@$(ECHO) "- $(CORAL)Cleaning objects + deps$(RST)"
	@$(MAKE) -C $(AS_DIR) clean
	@$(MAKE) -C $(VM_DIR) clean

fclean:
	@$(ECHO) "- $(PINK)Cleaning objects + deps + binary + library$(RST)"
	@rm -rf $(TEST_BINARY) $(TEST_OBJECTS) $(CRITERION) $(LIBRARY) \
	$(L_OBJECTS)  $(L_DEPS) $(T_DEPS)
	@$(MAKE) -C $(AS_DIR) fclean
	@$(MAKE) -C $(VM_DIR) fclean

re: fclean all

unit_tests:
	$(MAKE) fclean

$(TEST_BINARY): $(TEST_OBJECTS) $(LIBRARY)
	@$(ECHO) "- $(ORANGE)Running tests$(RST)"
	@$(CC) -o $@ $^ $(TEST_FLAGS)
	@./$@
	@rm -rf $(L_OBJECTS) $(L_DEPS)

visualize:
	@gcovr --exclude tests --exclude library --html --output=index.html

.PHONY: all $(BINARY) clean fclean re $(TEST_BINARY)
