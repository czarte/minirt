SRC = main.c
OBJ = $(SRC:.c=.o)
CC = clang
RM = rm -f
CPPFLAGS = -Wall -Wextra -Werror -g3 -pedantic -fsanitize=address

NAME = miniRT

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) mlx/libmlx_Linux.a -lXext -lX11 -o $(NAME)

$(MLX):

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re