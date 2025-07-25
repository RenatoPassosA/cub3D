# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 17:02:19 by rpassos-          #+#    #+#              #
#    Updated: 2025/07/24 16:21:37 by rpassos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CCFLAGS = -Wall -Wextra -Werror -g -ggdb
SRC = main.o validate_map.o map_utils.o map_functions.o parser.o utils.o ./utils/ft_atoi.o ./utils/ft_memcpy.o ./utils/ft_memset.o ./utils/ft_split.o ./utils/ft_strcmp.o ./utils/ft_strdup.o ./utils/ft_strjoin.o ./utils/ft_strlen.o ./utils/ft_strnstr.o ./utils/get_next_line.o ./utils/ft_isdigit.o ./utils/ft_calloc.o ./utils/ft_substr.o ./utils/ft_strchr.o ./utils/ft_memmove.o ./utils/ft_memcmp.o ./utils/ft_strstr.o ./utils/ft_strncmp.o
SRCS = main.c validate_map.c map_utils.c map_functions.c parser.c utils.c ./utils/ft_atoi.c ./utils/ft_memcpy.c ./utils/ft_memset.c ./utils/ft_split.c ./utils/ft_strcmp.c ./utils/ft_strdup.c ./utils/ft_strjoin.c ./utils/ft_strlen.c ./utils/ft_strnstr.c ./utils/get_next_line.c ./utils/ft_isdigit.c ./utils/ft_calloc.c ./utils/ft_substr.c ./utils/ft_strchr.c ./utils/ft_memmove.c ./utils/ft_memcmp.c ./utils/ft_strstr.c ./utils/ft_strncmp.c
TEST = validate_map.o map_utils.o map_functions.o parser.o utils.o ./utils/ft_atoi.o ./utils/ft_memcpy.o ./utils/ft_memset.o ./utils/ft_split.o ./utils/ft_strcmp.o ./utils/ft_strdup.o ./utils/ft_strjoin.o ./utils/ft_strlen.o ./utils/ft_strnstr.o ./utils/get_next_line.o ./utils/ft_isdigit.o ./utils/ft_calloc.o ./utils/ft_substr.o ./utils/ft_strchr.o ./utils/ft_memmove.o ./utils/ft_memcmp.o ./utils/ft_strstr.o ./utils/ft_strncmp.o
all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CCFLAGS) -o $(NAME) $(SRC) -g

.o:.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -f $(SRC)

fclean: clean
	rm -f $(NAME)

re: clean all

run: re
	./$(NAME) $(NUMBERS)

compile:
	$(CC) $(CCFLAGS) $(SRCS) -g -o cub3d

test:
	gcc $(TEST) tests/*.c -o test_map -lcriterion
	./test_map

.PHONY: all bonus clean fclean