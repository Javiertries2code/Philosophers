NAME := philo

DIR_UTILS := utils/
#DIR_SUPPORT := support/
DIR_HANDLERS := handlers/
#DIR_VALIDATE := val_exit/
DIR_SIMULATION := simulation/
DIR_INIT := init/
DIR_TIMING := timing/
DIR_PARSERS := parsers/
DIR_EXITING := exiting/

# ------------------ DEBUG ------------------
# Para debug de memoria (leaks, out-of-bounds, etc):
# $ make debug_leaks ARGS="4 310 200 200"
#
# Para debug de race conditions (mutex mal usado, accesos paralelos):
# $ make debug_races ARGS="4 310 200 200"
# ------------------------------------------

#-------------
#-------------
# DIR_TEST := test/
# TEST_FILES := 
# TESTS := $(addprefix $(DIR_TEST), $(TEST_FILES))
#-------------
#-------------
EXITING_FILES = exiting.c ending.c error_printer.c
TIMING_FILES = timing.c  get_time.c synchro.c
INIT_FILES =  init.c
SIMULATION_FILES = simulation.c routines.c
#VALIDATE_FILES = validate.c exiting.c
UTILS_FILES = utils.c utils_support.c
#SUPPORT_FILES = support.c
PARSERS_FILES = parse_argv.c 
HANDLERS_FILES = safe_mutex.c 

OBJECTS = $(UTILS:.c=.o) $(HANDLERS:.c=.o)  $(INITS:.c=.o) $(PARSERS:.c=.o) $(TIMING:.c=.o)
#$(VALIDATES:.c=.o) $(SUPPORT:.c=.o) 

UTILS := $(addprefix $(DIR_UTILS), $(UTILS_FILES))
#SUPPORT := $(addprefix $(DIR_SUPPORT),  $(SUPPORT_FILES))
HANDLERS := $(addprefix $(DIR_HANDLERS), $(HANDLERS_FILES))
PARSERS := $(addprefix $(DIR_PARSERS), $(PARSERS_FILES))
#VALIDATES := $(addprefix $(DIR_VALIDATE), $(VALIDATE_FILES))
SIMULATIONS := $(addprefix $(DIR_SIMULATION), $(SIMULATION_FILES))
INITS := $(addprefix $(DIR_INIT), $(INIT_FILES))
TIMINGS := $(addprefix $(DIR_TIMING), $(TIMING_FILES))
EXITING := $(addprefix $(DIR_EXITING), $(EXITING_FILES))

CC = cc
CFLAGS = -Wall -Wextra -Werror

ifeq ($(DEBUG), 1)
	CFLAGS += -g -O0
endif

all : $(NAME)

$(NAME):$(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) main.c $(UTILS) $(HANDLERS) \
	 $(PARSERS) $(SIMULATIONS) $(INITS) $(TIMINGS) $(EXITING)

clean:
	rm -rf  $(NAME) $(OBJECTS)

fclean: clean

re: fclean all

# Debug con Valgrind Memcheck (leaks, accesos inválidos, etc.)
debug_leaks:
	$(MAKE) fclean
	$(MAKE) DEBUG=1
	valgrind --leak-check=full --track-origins=yes ./$(NAME) $(ARGS)

# Debug con Valgrind Helgrind (data races)
debug_races:
	$(MAKE) fclean
	$(MAKE) DEBUG=1
	valgrind --tool=helgrind ./$(NAME) $(ARGS)

.PHONY: all clean fclean re debug_leaks debug_races
