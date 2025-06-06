SRC 		= main.c src/window.c src/parser.c src/init.c src/ft_spacious.c \
				src/exit.c src/scene.c src/object.c src/colors.c src/object_fill.c \
				src/helpers/o_bags.c src/helpers/print_objects.c src/vec/ray.c \
        		src/parser_utils.c src/validate_objects.c  src/validate_params.c \
				src/vec/t_vec_new.c src/vec/t_vec_ops.c src/vec/t_vec_products.c \
				src/shader.c src/vec/cy_utils.c src/process_objects.c \
				src/validate.c
OBJ 		= $(SRC:.c=.o)
CC 			= cc
RM 			= rm -f
CPPFLAGS 	= -Wall -Wextra -Werror -g3 #-fsanitize=address
LIBFT 		= libft.a
LIBFTDIR	= libft

NAME = miniRT

all: $(NAME)

$(NAME): $(OBJ)
	@make bonus -C $(LIBFTDIR)
	@cp $(LIBFTDIR)/$(LIBFT) .
	$(CC) $(CPPFLAGS) $(OBJ) $(LIBFT) mlx/libmlx.a -lXext -lX11 -o $(NAME) -lm

$(MLX):

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

noleak: CPPFLAGS = $(NO_SAN_FLAGS)
noleak: re

memleak: noleak
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./$(NAME) $(ARGS)

test: $(OBJ)
	@c++ ./tests/vec_tests_test.cpp -Iinclude -Igoogletest/googletest/include/ -std=c++14 -o vec_tests.o
	@c++ ./tests/main.cpp -Iinclude -Igoogletest/googletest/include/ -std=c++14
	@c++ ./main.o ./vec_tests.o $(NAMEA) $(TOBJS) -I./include ./googletest/build/lib/libgtest.a -o unit_test

.PHONY: all clean fclean re