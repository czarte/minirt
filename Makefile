SRC 		= main.c src/window.c src/parser.c src/init.c src/ft_spacious.c \
				src/exit.c src/scene.c src/object.c src/colors.c
OBJ 		= $(SRC:.c=.o)
CC 			= clang
RM 			= rm -f
CPPFLAGS 	= -Wall -Wextra -Werror -g3 -pedantic -fsanitize=address
LIBFT 		= libft.a
LIBFTDIR	= libft

NAME = miniRT

all: $(NAME)

$(NAME): $(OBJ)
	@make bonus -C $(LIBFTDIR)
	@cp $(LIBFTDIR)/$(LIBFT) .
	$(CC) $(CPPFLAGS) $(OBJ) $(LIBFT) mlx/libmlx_Linux.a -lXext -lX11 -o $(NAME)

$(MLX):

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re