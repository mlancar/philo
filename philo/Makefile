# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malancar <malancar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/11 17:31:42 by malancar          #+#    #+#              #
#    Updated: 2023/09/13 16:47:34 by malancar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= cc

CFLAGS	= -Wextra -Werror -Wall -g

NAME	= philo

HEADER = philo.h

SRC		= check.c			\
		  philo.c			\
		  utils.c			\
		  utils_2.c			\
		  routine.c			\
		  init.c			\
		  dishes.c			\
		  time.c			\
		  lonely_philo.c	\
		  main.c		

OBJ =	$(SRC:.c=.o)
DEPS = $(SRC:.c=.d)

RM	= rm -f

all:	 $(NAME)

$(NAME):	$(OBJ) $(HEADER)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o:	%.c
	$(CC) $(CFLAGS) -MMD -c  $< -o $@

clean:
	$(RM) $(OBJ) $(DEPS)

fclean: clean
	$(RM) $(NAME) $(DEPS)

re:	fclean all

-include : $(DEPS)

.PHONY: all clean fclean re