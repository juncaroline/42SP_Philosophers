# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/10 12:23:00 by cabo-ram          #+#    #+#              #
#    Updated: 2025/01/26 11:32:15 by cabo-ram         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
CC := gcc
CFLAGS := -g -Wall -Wextra -Werror -pthread
SRC:= init.c main.c utils.c
OBJS := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re