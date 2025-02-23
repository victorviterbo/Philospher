# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/22 20:24:47 by vviterbo          #+#    #+#              #
#    Updated: 2025/02/23 16:25:48 by vviterbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

HEADER = philosopher.h

CFLAGS = -Wall -Wextra -Werror

SRCS_UTILS_F =	ft_calloc.c ft_isint.c ft_itoa.c ft_memcmp.c ft_strlen.c \
				ft_atoi.c ft_number_len.c ft_iswhitespace_eq.c ft_strchr.c \
				ft_prev_power.c

SRCS_UTILS = $(addprefix ./srcs/utils/, $(SRCS_UTILS_F))

SRCS_MAIN_F =	philo.c

SRCS_MAIN = $(addprefix ./srcs/, $(SRCS_MAIN_F))

SRCS = $(SRCS_MAIN) $(SRCS_UTILS)

BIN = ./bin/

CC = cc

INCLUDE = -I./include/

all: folders $(NAME)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -f objs/*.o

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(BIN)$(NAME)

re: fclean all

folders :
	@mkdir -p objs/
	@mkdir -p bin/

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): folders $(SRCS)
	@$(CC) $(CFLAGS) $(SRCS) $(INCLUDE) -o $(BIN)$(NAME)
	@echo "philo compiled successfully"

.PHONY: all clean fclean re
