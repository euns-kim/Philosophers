# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 19:53:57 by eunskim           #+#    #+#              #
#    Updated: 2023/05/12 16:53:29 by eunskim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#//= Colors =//#
BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

#//= Mandatory part =//#
NAME 			:= philo
CFLAGS 			:= -Wextra -Wall -Werror 
# -fsanitize=thread -g
# -fsanitize=address -g3

INC_DIR			:= inc
HEADERS			:= -I $(INC_DIR)

SRC_DIR			:= src
SRCS			:= $(addprefix $(SRC_DIR)/, \
				philo.c \
				parse.c \
				routine.c \
				act.c \
				solo.c \
				reaper.c \
				time.c \
				display.c \
				utils.c \
				free.c)
OBJS			:= $(SRCS:.c=.o)

#//= Make Rules =//#
all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(HEADERS) $(OBJS) -o $(NAME) && \
	echo "$(MAGENTA)$(BOLD)>> Mandatory part - Philosophers $(RESET)" && \
	echo "$(GREEN)$(BOLD)Compilation successful!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ 

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
