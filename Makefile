# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: renato <renato@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 17:02:19 by rpassos-          #+#    #+#              #
#    Updated: 2025/07/30 12:09:43 by renato           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CCFLAGS = -Wall -Wextra -Werror -g -ggdb
SRC = main.o map_utils.o map_data.o get_map_matrix.o utils.o validate_map.o map_val_flood_fill.o map_val_outside_flood_fill.o map_val_check_isolated_spaces.o map_val_validate_textures.o map_val_validate_player.o map_val_validate_map_position.o map_val_validate_edges.o map_val_validate_colors.o map_val_check_valid_lines.o map_val_check_valid_map_elements.o map_val_check_missing_identifier.o map_val_check_map.o map_val_check_double_identifier.o ./utils/ft_atoi.o ./utils/ft_memcpy.o ./utils/ft_memset.o ./utils/ft_split.o ./utils/ft_strcmp.o ./utils/ft_strdup.o ./utils/ft_strjoin.o ./utils/ft_strlen.o ./utils/ft_strnstr.o ./utils/get_next_line.o ./utils/ft_isdigit.o ./utils/ft_calloc.o ./utils/ft_substr.o ./utils/ft_strchr.o ./utils/ft_memmove.o ./utils/ft_memcmp.o ./utils/ft_strstr.o ./utils/ft_strncmp.o
SRCS = main.c map_utils.c map_data.c get_map_matrix.c utils.c validate_map.c map_val_flood_fill.c map_val_outside_flood_fill.c map_val_check_isolated_spaces.c map_val_validate_textures.c map_val_validate_player.c map_val_validate_map_position.c map_val_validate_edges.c map_val_validate_colors.c map_val_check_valid_lines.c map_val_check_valid_map_elements.c map_val_check_missing_identifier.c map_val_check_map.c map_val_check_double_identifier.c ./utils/ft_atoi.c ./utils/ft_memcpy.c ./utils/ft_memset.c ./utils/ft_split.c ./utils/ft_strcmp.c ./utils/ft_strdup.c ./utils/ft_strjoin.c ./utils/ft_strlen.c ./utils/ft_strnstr.c ./utils/get_next_line.c ./utils/ft_isdigit.c ./utils/ft_calloc.c ./utils/ft_substr.c ./utils/ft_strchr.c ./utils/ft_memmove.c ./utils/ft_memcmp.c ./utils/ft_strstr.c ./utils/ft_strncmp.c
TEST = main.o map_utils.o map_data.o get_map_matrix.o utils.o validate_map.o map_val_flood_fill.o map_val_outside_flood_fill.o map_val_check_isolated_spaces.o map_val_validate_textures.o map_val_validate_player.o map_val_validate_map_position.o map_val_validate_edges.o map_val_validate_colors.o map_val_check_valid_lines.o map_val_check_valid_map_elements.o map_val_check_missing_identifier.o map_val_check_map.o map_val_check_double_identifier.o ./utils/ft_atoi.o ./utils/ft_memcpy.o ./utils/ft_memset.o ./utils/ft_split.o ./utils/ft_strcmp.o ./utils/ft_strdup.o ./utils/ft_strjoin.o ./utils/ft_strlen.o ./utils/ft_strnstr.o ./utils/get_next_line.o ./utils/ft_isdigit.o ./utils/ft_calloc.o ./utils/ft_substr.o ./utils/ft_strchr.o ./utils/ft_memmove.o ./utils/ft_memcmp.o ./utils/ft_strstr.o ./utils/ft_strncmp.o
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
	$(CC) $(CCFLAGS) $(SRCS) -g -o cub3d -g

sanitizer:
	$(CC) $(CCFLAGS) $(SRCS) -g -o cub3d -g -fsanitize=address -fno-omit-frame-pointer

test:
	gcc $(TEST) tests/*.c -o test_map -lcriterion
	./test_map

.PHONY: all bonus clean fclean