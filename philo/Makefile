# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 15:40:14 by vviterbo          #+#    #+#              #
#    Updated: 2025/05/05 17:27:47 by vviterbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CFLAGS = -Wall -Wextra -Werror
CC = cc
INCLUDE = -I./include/

SRCS_UTILS_F = ft_calloc.c ft_isint.c ft_itoa.c ft_memcmp.c ft_strlen.c \
               ft_atoi.c ft_number_len.c ft_iswhitespace_eq.c ft_strchr.c \
               ft_prev_power.c ft_free_array.c

SRCS_MAIN_F = philo.c start_simu.c run_simu.c end_simu.c time_utils.c \
              mutex_utils.c state_utils.c

SRCS_UTILS = $(addprefix srcs/utils/, $(SRCS_UTILS_F))
SRCS_MAIN = $(addprefix srcs/, $(SRCS_MAIN_F))
SRCS = $(SRCS_MAIN) $(SRCS_UTILS)

OBJS = $(patsubst srcs/%.c,objs/%.o,$(SRCS_MAIN)) \
       $(patsubst srcs/utils/%.c,objs/utils/%.o,$(SRCS_UTILS))

OBJS_DIRS = $(sort $(dir $(OBJS)))

all: folders $(NAME)

clean:
	@rm -rf objs/

fclean: clean
	@rm -f $(NAME)

re: fclean all

folders:
	@mkdir -p $(OBJS_DIRS)

objs/%.o: srcs/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

objs/utils/%.o: srcs/utils/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(NAME) compiled successfully"

.PHONY: all clean fclean re folders