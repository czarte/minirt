# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: voparkan <voparkan@student.42heilbronn.de>+#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 19:55:14 by voparkan          #+#    #+#              #
#    Updated: 2023/03/27 20:13:10 by voparkan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Folders and files

NAME		= libft.a
ODIR		= obj
BODIR		= bobj
SRCS		= ./ft_atoi.c ./ft_bzero.c ./ft_calloc.c ./ft_isalnum.c \
		./ft_isalpha.c ./ft_isascii.c ./ft_isdigit.c ./ft_isprint.c \
		./ft_itoa.c ./ft_memchr.c ./ft_memcmp.c ./ft_memcpy.c ./ft_memmove.c\
		./ft_memset.c ./ft_putchar_fd.c ./ft_putendl_fd.c ./ft_putnbr_fd.c \
		./ft_putstr_fd.c ./ft_split.c ./ft_strchr.c ./ft_strdup.c \
		./ft_striteri.c ./ft_strjoin.c ./ft_strlcat.c ./ft_strlcpy.c \
		./ft_strlen.c ./ft_strmapi.c ./ft_strncmp.c ./ft_strnstr.c \
		./ft_strrchr.c ./ft_strtrim.c ./ft_substr.c ./ft_tolower.c \
		./ft_toupper.c ./ft_atof.c

BSRCS		= ./ft_lstadd_back.c ./ft_lstadd_front.c ./ft_lstclear.c \
			./ft_lstdelone.c ./ft_lstiter.c ./ft_lstlast.c ./ft_lstmap.c \
			./ft_lstnew.c ./ft_lstsize.c

# Compiler setup

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

###############################
#    compiling procedures     #
###############################

OBJECTS		= $(SRCS:%.c=$(ODIR)/%.o)
BOBJECTS	= $(BSRCS:%.c=$(BODIR)/%.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo $(SRCS)
	@echo "Linking $@"
	@ar rc $(NAME) $(OBJECTS)
	@echo "Done!"

$(OBJECTS): $(ODIR)/%.o: ./%.c
	@mkdir -p $(@D)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BOBJECTS): $(BODIR)/%.o: ./%.c
	@mkdir -p $(BODIR)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJECTS) $(BOBJECTS)
	@echo $(BSRCS)
	@echo "Linking $@"
	@ar rc $(NAME) $(OBJECTS) $(BOBJECTS)
	@echo "Done!"

clean:
	@echo "deleting $(ODIR), $(BODIR) and all outputs." 
	@rm -Rf $(ODIR)
	@rm -Rf $(BODIR)
	@rm -Rf *.out
	@rm -Rf *.o
	@rm -Rf *.dSYM
#	@rm -Rf main*.c
	@echo "Done!"

fclean: clean
	@echo "deleting $(NAME)" 
	@rm -f $(NAME)
	@echo "Done!"
	
re:	fclean all

.PHONY: all clean fclean re
