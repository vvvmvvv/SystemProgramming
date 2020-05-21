NAME = system_programming_lab1_task1.out

SRC_DIR = src

SRC = $(shell find $(SRC_DIR) -type f -name "*.c")

INC = -I include/

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

CFLAGS = -c $(FLAGS)

all: $(NAME)

obj: $(OBJ)

$(NAME) : $(OBJ)
	gcc $(FLAGS) $^ -o $(NAME)

%.o: %.c
	gcc $(CFLAGS) $(INC) -o $@ $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
