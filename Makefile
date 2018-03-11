# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnaumenk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/01 17:10:27 by rnaumenk          #+#    #+#              #
#    Updated: 2018/03/01 17:10:28 by rnaumenk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIB = libft/*.o
CS = 	./check_the_buf.c \
		./check_the_flags.c \
		./ft_litoa_base.c \
		./ft_printf.c \
		./ft_ulxtoa_base.c \
		./functs_for_flags.c \
		./ft_uixtoa_base.c \
		./look_for_specificators.c
OBJ = $(CS:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	@ar rc $@ ./*.o ./libft/*.o
	@echo "\033[32mlibftprintf.a is ready\033[0m"

$(LIB):
	@cd libft && make && rm -f libft.a

%.o: %.c
	@gcc -Wall -Wextra -Werror -c $<

clean:
	@rm -f $(OBJ)
	@echo "\033[36mObjects and libft.a have been deleted\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[31mlibftprintf.a has been deleted\033[0m"

re: fclean all

.PHONY: all clean fclean re
