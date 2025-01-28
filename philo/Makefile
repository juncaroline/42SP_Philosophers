# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/10 12:23:00 by cabo-ram          #+#    #+#              #
#    Updated: 2025/01/27 16:22:04 by cabo-ram         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
CC := gcc
CFLAGS := -g -Wall -Wextra -Werror -pthread
SRC:= check.c init_end.c main.c routine.c threads.c utils.c
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