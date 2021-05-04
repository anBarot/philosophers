# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarot <abarot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/20 17:58:02 by abarot            #+#    #+#              #
#    Updated: 2021/05/04 12:00:40 by abarot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_one

SRCS	=	main.c \
			init.c \
			utils.c \
			time.c \
			routine.c 

OBJS	=	$(SRCS:.c=.o)

CC		=	clang

CFLAGS	+=	-g -Wall -Wextra -Werror 

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