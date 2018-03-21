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

NAME	=	libftprintf.a
SRC_DIR	=	./src/
OBJ_DIR	=	./obj/
INC_DIR	=	./include/
SRC		= 	check_the_buf.c \
			check_the_flags.c \
			check_the_width.c \
			ft_abs.c \
			ft_atoi.c \
			ft_bzero.c \
			ft_itoa_base.c \
			ft_litoa_base.c \
			ft_memalloc.c \
			ft_memcpy.c \
			ft_printf.c \
			ft_strdel.c \
			ft_strdup.c \
			ft_strlen.c \
			ft_uixtoa_base.c \
			ft_ulxtoa_base.c \
			functs1.c \
			functs2.c \
			functs3.c \
			functs4.c \
			functs5.c \
			functs6.c \
			functs7.c \
			look_for_specificators.c \
			prefunct1.c \
			prefunct2.c \
			prefunct3.c \
			additional.c
OBJ		=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $@ $^
	@ranlib $@
	@echo "\033[4;32mlibftprintf.a is ready\033[0m"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@gcc -Wall -Wextra -Werror -o $@ -c $<

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[3;33mObjects have been deleted\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[3;31mlibftprintf.a has been deleted\033[0m"

re: fclean all

.PHONY: all clean fclean re
