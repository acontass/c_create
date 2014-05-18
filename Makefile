#*******************************************************************************#
#                                                                               #
#                                                          :::      ::::::::    #
#    Makefile                                            :+:      :+:    :+:    #
#                                                      +:+ +:+         +:+      #
#    by: acontass <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                  +#+#+#+#+#+   +#+            #
#    Created: 2014/03/30 08:35:11 by acontass           #+#    #+#              #
#    Updated: 2014/05/04 10:27:45 by acontass          ###   ########.fr        #
#                                                                               #
#*******************************************************************************#
NAME		=	c_create

SRCS		=	c_create.c

OBJ			=	$(SRCS:.c=.o)

CFLAGS		+=	-W -Wall -Wextra -Werror

CC			=	gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re