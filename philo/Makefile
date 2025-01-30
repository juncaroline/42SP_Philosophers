# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/10 12:23:00 by cabo-ram          #+#    #+#              #
#    Updated: 2025/01/30 14:49:27 by cabo-ram         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
CC := gcc
CFLAGS := -g -Wall -Wextra -Werror -pthread
OBJS_FOLDER = ./obj/
SRC:= check.c init_end.c main.c monitor.c routine.c threads.c utils.c
OBJS := $(addprefix $(OBJS_FOLDER), $(SRC:.c=.o))

all: $(OBJS_FOLDER) $(NAME)

$(OBJS_FOLDER):
	mkdir -p $(OBJS_FOLDER)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_FOLDER)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS_FOLDER)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re