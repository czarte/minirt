SRC = main.c
OBJ = $(SRC:.cpp=.o)
CC = clang
RM = rm -f
CPPFLAGS = -Wall -Wextra -Werror -g3 -pedantic #-fsanitize=address

NAME = miniRT

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re