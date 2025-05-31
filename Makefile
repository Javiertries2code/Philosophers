NAME := philo

DIR_UTILS := utils/
DIR_HANDLERS := handlers/
DIR_SIMULATION := simulation/
DIR_INIT := init/
DIR_TIMING := timing/
DIR_PARSERS := parsers/
DIR_EXITING := exiting/

EXITING_FILES = exiting.c ending.c error_printer.c
TIMING_FILES = timing.c  get_time.c synchro.c timing_support.c
INIT_FILES =  init.c init_assistants.c asist_one.c asist_two.c asist_three.c asist_four.c asist_five.c asist_six.c
SIMULATION_FILES = simulation.c routines.c simulation_support.c
UTILS_FILES = utils.c utils_support.c
PARSERS_FILES = parse_argv.c 
HANDLERS_FILES = safe_mutex.c 

OBJECTS = $(UTILS:.c=.o) $(HANDLERS:.c=.o)  $(INITS:.c=.o) $(PARSERS:.c=.o) $(TIMING:.c=.o)
UTILS := $(addprefix $(DIR_UTILS), $(UTILS_FILES))
HANDLERS := $(addprefix $(DIR_HANDLERS), $(HANDLERS_FILES))
PARSERS := $(addprefix $(DIR_PARSERS), $(PARSERS_FILES))
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

# Debug con Valgrind Memcheck make debug_leaks ARGS="4 410 200 200"
debug_leaks:
	$(MAKE) fclean
	$(MAKE) DEBUG=1
	valgrind --leak-check=full --track-origins=yes ./$(NAME) $(ARGS)

# Debug con Valgrind Helgrind make debug_races ARGS="4 410 200 200"
debug_races:
	$(MAKE) fclean
	$(MAKE) DEBUG=1
	valgrind --tool=helgrind ./$(NAME) $(ARGS)

.PHONY: all clean fclean re debug_leaks debug_races
