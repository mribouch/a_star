# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/14 03:33:55 by marvin            #+#    #+#              #
#    Updated: 2020/01/20 15:46:49 by mribouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a_star

SRCS = main.c		\
		a_star.c	\
		parse.c		\
		list.c

FLAGS = -Wall -Wextra -Werror
OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) test.h
		gcc $(FLAGS) $(OBJS) $(LIBFT) -o a_star

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

clean:
		rm -rf $(OBJS)
		make clean -C libft/

fclean: clean
		rm -rf a_star libft/libft.a

re: fclean $(NAME)
