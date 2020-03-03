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
		list.c		\
		child.c		\
		analyse.c	\
		node.c

FLAGS = -Wall -Wextra -Werror
OBJS = $(SRCS:.c=.o)

#LIBRARIES
#	libft
LIBFT_FOLDER=	./libft
LIBFT		=	$(LIBFT_FOLDER)/libft.a
INCLUDES	:=	$(INCLUDES) -I $(LIBFT_FOLDER)/includes
LDFLAGS		:=	$(LDFLAGS) -L $(LIBFT_FOLDER) -lft

# LIBFT = libft/libft.a

all:	$(LIBFT) $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	gcc $(FLAGS) -c $< -o $@ $(INCLUDES)

$(LIBFT):
	make -C libft

clean:
	rm -rf $(OBJS)
	make clean -C $(LIBFT_FOLDER)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_FOLDER)

re: fclean all
