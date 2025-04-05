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

test: $(OBJ)
	@c++ ./tests/vec_tests_test.cpp -Iinclude -Igoogletest/googletest/include/ -std=c++14 -o vec_tests.o
	@c++ ./tests/main.cpp -Iinclude -Igoogletest/googletest/include/ -std=c++14
	@c++ ./main.o ./vec_tests.o $(NAMEA) $(TOBJS) -I./include ./googletest/build/lib/libgtest.a -o unit_test

.PHONY: all clean fclean re