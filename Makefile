SRC 		= main.c src/window.c src/parser.c src/init.c src/ft_spacious.c src/exit.c
OBJ 		= $(SRC:.c=.o)
CC 			= gcc
RM 			= rm -f
CFLAGS 		= -Wall -Wextra -Werror -g3 -pedantic #-fsanitize=address
LIBFT 		= libft.a
LIBFTDIR	= libft

NAME = miniRT

all: $(NAME)

$(NAME): $(OBJ)
	@make bonus -C $(LIBFTDIR)
	@cp $(LIBFTDIR)/$(LIBFT) .
	$(CC) $(CFLAGS) $(OBJ) ./$(LIBFT) ./mlx/libmlx.a -lXext -lX11 -o $(NAME)

mac: $(OBJ)
	@make bonus -C $(LIBFTDIR)
	@cp $(LIBFTDIR)/$(LIBFT) .
	@ar rc $(LIBFT) $(OBJ)
	$(CC) -v $(CFLAGS) ./$(LIBFT) ./mlx/libmlx.a -Iinclude -lglfw -o $(NAME)

$(MLX):

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

remac: fclean mac

.PHONY: all clean fclean re