# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarot <abarot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/20 17:58:02 by abarot            #+#    #+#              #
#    Updated: 2021/05/06 18:44:05 by abarot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_three

SRCS	=	main.c \
			init.c \
			utils.c \
			time.c \
			routine.c 

OBJS	=	$(SRCS:.c=.o)

CC		=	clang

CFLAGS	+=	-Wall -Wextra -Werror -g

all		:	
			make $(NAME)

$(NAME) :	$(OBJS)
			clang $(CFLAGS) -lpthread $(OBJS) -o $@ -I.

clean	:	
			rm -f $(OBJS)

fclean	:	clean
			rm -f $(NAME)

re		:	fclean 
			make all