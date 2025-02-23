# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/22 20:24:47 by vviterbo          #+#    #+#              #
#    Updated: 2025/02/23 10:41:49 by vviterbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

HEADER = philosopher.h

CFLAGS = -Wall -Wextra -Werror

SRCS = 

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
	@$(CC) $(CFLAGS) $(SRCS) ./srcs/philo.c $(INCLUDE) -o $(BIN)$(NAME)
	@echo "philo compiled successfully"

.PHONY: all clean fclean re
