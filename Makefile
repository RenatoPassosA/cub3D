# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: renato <renato@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 17:02:19 by rpassos-          #+#    #+#              #
#    Updated: 2025/08/08 17:09:51 by renato           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CCFLAGS = -Wall -Wextra -Werror -g -ggdb -Imlx
SRC = ./src/main.o ./src/parser/map_utils.o ./src/parser/split_content.o ./src/parser/map_data.o ./src/parser/get_map_matrix.o ./src/parser/utils.o ./src/parser/map_val_validate_map_size.o ./src/parser/validate_map.o ./src/parser/map_val_flood_fill.o ./src/parser/map_val_outside_flood_fill.o ./src/parser/map_val_check_isolated_spaces.o ./src/parser/map_val_validate_textures.o ./src/parser/map_val_validate_player.o ./src/parser/map_val_validate_map_position.o ./src/parser/map_val_validate_edges.o ./src/parser/map_val_validate_colors.o ./src/parser/map_val_check_valid_lines.o ./src/parser/map_val_check_valid_map_elements.o ./src/parser/map_val_check_missing_identifier.o ./src/parser/map_val_check_map.o ./src/parser/map_val_check_double_identifier.o ./src/graphics/graphics_render_wall.o ./src/graphics/graphics_player_info.o ./src/graphics/graphics_mlx.o ./utils/ft_atoi.o ./utils/ft_memcpy.o ./utils/ft_memset.o ./utils/ft_split.o ./utils/ft_strcmp.o ./utils/ft_strdup.o ./utils/ft_strjoin.o ./utils/ft_strlen.o ./utils/ft_strnstr.o ./utils/get_next_line.o ./utils/ft_isdigit.o ./utils/ft_calloc.o ./utils/ft_substr.o ./utils/ft_strchr.o ./utils/ft_memmove.o ./utils/ft_memcmp.o ./utils/ft_strstr.o ./utils/ft_strncmp.o
SRCS = ./src/main.c ./src/parser/map_utils.c ./src/parser/split_content.c ./src/parser/map_data.c ./src/parser/get_map_matrix.c ./src/parser/utils.c ./src/parser/map_val_validate_map_size.c ./src/parser/validate_map.c ./src/parser/map_val_flood_fill.c ./src/parser/map_val_outside_flood_fill.c ./src/parser/map_val_check_isolated_spaces.c ./src/parser/map_val_validate_textures.c ./src/parser/map_val_validate_player.c ./src/parser/map_val_validate_map_position.c ./src/parser/map_val_validate_edges.c ./src/parser/map_val_validate_colors.c ./src/parser/map_val_check_valid_lines.c ./src/parser/map_val_check_valid_map_elements.c ./src/parser/map_val_check_missing_identifier.c ./src/parser/map_val_check_map.c ./src/parser/map_val_check_double_identifier.c ./src/graphics/graphics_render_wall.c ./src/graphics/graphics_player_info.c ./src/graphics/graphics_mlx.c ./utils/ft_atoi.c ./utils/ft_memcpy.c ./utils/ft_memset.c ./utils/ft_split.c ./utils/ft_strcmp.c ./utils/ft_strdup.c ./utils/ft_strjoin.c ./utils/ft_strlen.c ./utils/ft_strnstr.c ./utils/get_next_line.c ./utils/ft_isdigit.c ./utils/ft_calloc.c ./utils/ft_substr.c ./utils/ft_strchr.c ./utils/ft_memmove.c ./utils/ft_memcmp.c ./utils/ft_strstr.c ./utils/ft_strncmp.c
TEST = ./src/parser/map_utils.c ./src/parser/split_content.c ./src/parser/map_data.c ./src/parser/get_map_matrix.c ./src/parser/utils.c ./src/parser/map_val_validate_map_size.c ./src/parser/validate_map.c ./src/parser/map_val_flood_fill.c ./src/parser/map_val_outside_flood_fill.c ./src/parser/map_val_check_isolated_spaces.c ./src/parser/map_val_validate_textures.c ./src/parser/map_val_validate_player.c ./src/parser/map_val_validate_map_position.c ./src/parser/map_val_validate_edges.c ./src/parser/map_val_validate_colors.c ./src/parser/map_val_check_valid_lines.c ./src/parser/map_val_check_valid_map_elements.c ./src/parser/map_val_check_missing_identifier.c ./src/parser/map_val_check_map.c ./src/parser/map_val_check_double_identifier.c ./utils/ft_atoi.c ./utils/ft_memcpy.c ./utils/ft_memset.c ./utils/ft_split.c ./utils/ft_strcmp.c ./utils/ft_strdup.c ./utils/ft_strjoin.c ./utils/ft_strlen.c ./utils/ft_strnstr.c ./utils/get_next_line.c ./utils/ft_isdigit.c ./utils/ft_calloc.c ./utils/ft_substr.c ./utils/ft_strchr.c ./utils/ft_memmove.c ./utils/ft_memcmp.c ./utils/ft_strstr.c ./utils/ft_strncmp.c
MLX = mlx/libmlx.a -L/usr/lib -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CCFLAGS) -o $(NAME) $(SRC) $(MLX) -g

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
	$(CC) $(CCFLAGS) $(SRCS) $(MLX) -g -o cub3d

sanitizer:
	$(CC) $(CCFLAGS) $(SRCS) $(MLX) -g -o cub3d -g -fsanitize=address -fno-omit-frame-pointer

test:
	$(CC) $(CCFLAGS) $(TEST) tests/*.c -o test_map -lcriterion -I./src -I./utils
	./test_map

.PHONY: all bonus clean fclean