# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malancar <malancar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/11 17:31:42 by malancar          #+#    #+#              #
#    Updated: 2023/09/11 17:40:15 by malancar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= cc

CFLAGS	= -Wextra -Werror -Wall

NAME	= philo

HEADER = philo.h

SRC		= check.c		\
		  philo.c		\
		  philo_utils.c	\
		  routine.c		\
		  init.c		\
		  finishing.c	\
		  to_be_name.c

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