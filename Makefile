# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: renato <renato@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 17:02:19 by rpassos-          #+#    #+#              #
#    Updated: 2025/09/09 14:53:59 by renato           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
NAME_BONUS = cub3d_bonus
CC = cc
CCFLAGS = -Wall -Wextra -Werror -g -ggdb -Imlx
SRC = ./src/main.o ./src/game/game.o ./src/game/inputs.o ./src/game/inputs_utils.o ./src/parser/map_utils.o ./src/parser/split_content.o ./src/parser/handle_error.o ./src/parser/map_data.o ./src/parser/get_map_matrix.o ./src/parser/get_map_matrix_utils.o ./src/utils.o ./src/utils2.o ./src/parser/map_val_validate_map_size.o ./src/parser/validate_map.o ./src/parser/map_val_flood_fill.o ./src/parser/map_val_outside_flood_fill.o ./src/parser/map_val_check_isolated_spaces.o ./src/parser/map_val_validate_textures.o ./src/parser/map_val_validate_player.o ./src/parser/map_val_validate_map_position.o ./src/parser/map_val_validate_edges.o ./src/parser/map_val_validate_colors.o ./src/parser/map_val_check_valid_lines.o ./src/parser/map_val_check_valid_map_elements.o ./src/parser/map_val_check_missing_identifier.o ./src/parser/map_val_check_map.o ./src/parser/map_val_check_double_identifier.o ./src/graphics/graphics_render.o ./src/graphics/graphics_render2.o ./src/graphics/graphics_player_info.o ./src/graphics/graphics_mlx.o ./src/graphics/graphics_utils.o ./utils/ft_atoi.o ./utils/ft_memcpy.o ./utils/ft_memset.o ./utils/ft_split.o ./utils/ft_strcmp.o ./utils/ft_strdup.o ./utils/ft_strjoin.o ./utils/ft_strlen.o ./utils/ft_strnstr.o ./utils/get_next_line.o ./utils/ft_isdigit.o ./utils/ft_calloc.o ./utils/ft_substr.o ./utils/ft_strchr.o ./utils/ft_memmove.o ./utils/ft_memcmp.o ./utils/ft_strstr.o ./utils/ft_strncmp.o
SRCS = ./src/main.c ./src/game/game.c ./src/game/inputs.c ./src/game/inputs_utils.c ./src/parser/map_utils.c ./src/parser/split_content.c ./src/parser/handle_error.c ./src/parser/map_data.c ./src/parser/get_map_matrix.c ./src/parser/get_map_matrix_utils.c ./src/utils.c ./src/utils2.c ./src/parser/map_val_validate_map_size.c ./src/parser/validate_map.c ./src/parser/map_val_flood_fill.c ./src/parser/map_val_outside_flood_fill.c ./src/parser/map_val_check_isolated_spaces.c ./src/parser/map_val_validate_textures.c ./src/parser/map_val_validate_player.c ./src/parser/map_val_validate_map_position.c ./src/parser/map_val_validate_edges.c ./src/parser/map_val_validate_colors.c ./src/parser/map_val_check_valid_lines.c ./src/parser/map_val_check_valid_map_elements.c ./src/parser/map_val_check_missing_identifier.c ./src/parser/map_val_check_map.c ./src/parser/map_val_check_double_identifier.c ./src/graphics/graphics_render.c ./src/graphics/graphics_render2.c ./src/graphics/graphics_player_info.c ./src/graphics/graphics_mlx.c ./src/graphics/graphics_utils.c ./utils/ft_atoi.c ./utils/ft_memcpy.c ./utils/ft_memset.c ./utils/ft_split.c ./utils/ft_strcmp.c ./utils/ft_strdup.c ./utils/ft_strjoin.c ./utils/ft_strlen.c ./utils/ft_strnstr.c ./utils/get_next_line.c ./utils/ft_isdigit.c ./utils/ft_calloc.c ./utils/ft_substr.c ./utils/ft_strchr.c ./utils/ft_memmove.c ./utils/ft_memcmp.c ./utils/ft_strstr.c ./utils/ft_strncmp.c
BONUS = ./src_bonus/main.o ./src_bonus/game/game.o ./src_bonus/game/inputs.o ./src_bonus/game/inputs_utils.o ./src_bonus/game/mouse_movement.o ./src_bonus/game/doors_input.o ./src_bonus/parser/map_utils.o ./src_bonus/parser/split_content.o ./src_bonus/parser/handle_error.o ./src_bonus/parser/map_data.o ./src_bonus/parser/get_map_matrix.o ./src_bonus/parser/get_map_matrix_utils.o ./src_bonus/utils.o ./src_bonus/utils2.o ./src_bonus/parser/map_val_validate_map_size.o ./src_bonus/parser/validate_map.o ./src_bonus/parser/map_val_flood_fill.o ./src_bonus/parser/map_val_outside_flood_fill.o ./src_bonus/parser/map_val_check_isolated_spaces.o ./src_bonus/parser/map_val_validate_textures.o ./src_bonus/parser/map_val_validate_player.o ./src_bonus/parser/map_val_validate_map_position.o ./src_bonus/parser/map_val_validate_edges.o ./src_bonus/parser/map_val_validate_colors.o ./src_bonus/parser/map_val_check_valid_lines.o ./src_bonus/parser/map_val_check_valid_map_elements.o ./src_bonus/parser/map_val_check_missing_identifier.o ./src_bonus/parser/map_val_check_map.o ./src_bonus/parser/map_val_check_double_identifier.o ./src_bonus/graphics/graphics_render.o ./src_bonus/graphics/graphics_render2.o ./src_bonus/graphics/graphics_render_sprites.o ./src_bonus/graphics/graphics_monster.o ./src_bonus/graphics/graphics_decorative_sprites.o ./src_bonus/graphics/graphics_doors.o ./src_bonus/graphics/graphics_render_floor.o ./src_bonus/graphics/graphics_player_info.o ./src_bonus/graphics/graphics_mlx.o ./src_bonus/graphics/graphics_utils.o ./src_bonus/graphics/graphics_minimap.o ./utils/ft_atoi.o ./utils/ft_memcpy.o ./utils/ft_memset.o ./utils/ft_split.o ./utils/ft_strcmp.o ./utils/ft_strdup.o ./utils/ft_strjoin.o ./utils/ft_strlen.o ./utils/ft_strnstr.o ./utils/get_next_line.o ./utils/ft_isdigit.o ./utils/ft_calloc.o ./utils/ft_substr.o ./utils/ft_strchr.o ./utils/ft_memmove.o ./utils/ft_memcmp.o ./utils/ft_strstr.o ./utils/ft_strncmp.o
SRC_BONUS = ./src_bonus/main.c ./src_bonus/game/game.c ./src_bonus/game/inputs.c ./src_bonus/game/inputs_utils.c ./src_bonus/game/mouse_movement.c ./src_bonus/game/doors_input.c ./src_bonus/parser/map_utils.c ./src_bonus/parser/split_content.c ./src_bonus/parser/handle_error.c ./src_bonus/parser/map_data.c ./src_bonus/parser/get_map_matrix.c ./src_bonus/parser/get_map_matrix_utils.c ./src_bonus/utils.c ./src_bonus/utils2.c ./src_bonus/parser/map_val_validate_map_size.c ./src_bonus/parser/validate_map.c ./src_bonus/parser/map_val_flood_fill.c ./src_bonus/parser/map_val_outside_flood_fill.c ./src_bonus/parser/map_val_check_isolated_spaces.c ./src_bonus/parser/map_val_validate_textures.c ./src_bonus/parser/map_val_validate_player.c ./src_bonus/parser/map_val_validate_map_position.c ./src_bonus/parser/map_val_validate_edges.c ./src_bonus/parser/map_val_validate_colors.c ./src_bonus/parser/map_val_check_valid_lines.c ./src_bonus/parser/map_val_check_valid_map_elements.c ./src_bonus/parser/map_val_check_missing_identifier.c ./src_bonus/parser/map_val_check_map.c ./src_bonus/parser/map_val_check_double_identifier.c ./src_bonus/graphics/graphics_render.c ./src_bonus/graphics/graphics_render2.c ./src_bonus/graphics/graphics_render_sprites.c ./src_bonus/graphics/graphics_monster.c ./src_bonus/graphics/graphics_decorative_sprites.c ./src_bonus/graphics/graphics_doors.c ./src_bonus/graphics/graphics_render_floor.c ./src_bonus/graphics/graphics_player_info.c ./src_bonus/graphics/graphics_mlx.c ./src_bonus/graphics/graphics_utils.c ./src_bonus/graphics/graphics_minimap.c ./utils/ft_atoi.c ./utils/ft_memcpy.c ./utils/ft_memset.c ./utils/ft_split.c ./utils/ft_strcmp.c ./utils/ft_strdup.c ./utils/ft_strjoin.c ./utils/ft_strlen.c ./utils/ft_strnstr.c ./utils/get_next_line.c ./utils/ft_isdigit.c ./utils/ft_calloc.c ./utils/ft_substr.c ./utils/ft_strchr.c ./utils/ft_memmove.c ./utils/ft_memcmp.c ./utils/ft_strstr.c ./utils/ft_strncmp.c
TEST = ./src/parser/map_utils.c ./src/parser/split_content.c ./src/parser/handle_error.c ./src/parser/map_data.c ./src/parser/get_map_matrix.c ./src/parser/get_map_matrix_utils.c ./src/utils.c ./src/utils2.c ./src/parser/map_val_validate_map_size.c ./src/parser/validate_map.c ./src/parser/map_val_flood_fill.c ./src/parser/map_val_outside_flood_fill.c ./src/parser/map_val_check_isolated_spaces.c ./src/parser/map_val_validate_textures.c ./src/parser/map_val_validate_player.c ./src/parser/map_val_validate_map_position.c ./src/parser/map_val_validate_edges.c ./src/parser/map_val_validate_colors.c ./src/parser/map_val_check_valid_lines.c ./src/parser/map_val_check_valid_map_elements.c ./src/parser/map_val_check_missing_identifier.c ./src/parser/map_val_check_map.c ./src/parser/map_val_check_double_identifier.c ./utils/ft_atoi.c ./utils/ft_memcpy.c ./utils/ft_memset.c ./utils/ft_split.c ./utils/ft_strcmp.c ./utils/ft_strdup.c ./utils/ft_strjoin.c ./utils/ft_strlen.c ./utils/ft_strnstr.c ./utils/get_next_line.c ./utils/ft_isdigit.c ./utils/ft_calloc.c ./utils/ft_substr.c ./utils/ft_strchr.c ./utils/ft_memmove.c ./utils/ft_memcmp.c ./utils/ft_strstr.c ./utils/ft_strncmp.c
MLX = mlx/libmlx.a -L/usr/lib -lXext -lX11 -lm
OBJS_BONUS := $(SRC_BONUS:%.c=%.o)

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CCFLAGS) -o $(NAME) $(SRC) $(MLX) -g

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CCFLAGS) $(OBJS_BONUS) $(MLX) -o $(NAME_BONUS)

.o:.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	@clear
	rm -f $(SRC) $(BONUS) 

fclean: clean
	@clear
	rm -f $(NAME) $(NAME_BONUS)

re: clean all

run: re
	./$(NAME) $(NUMBERS)

compile:
	$(CC) $(CCFLAGS) $(SRCS) $(MLX) -g -o cub3d

compilebonus:
	$(CC) $(CCFLAGS) $(SRC_BONUS) $(MLX) -g -o cub3d_bonus

sanitizer:
	$(CC) $(CCFLAGS) $(SRCS) $(MLX) -g -o cub3d -g -fsanitize=address -fno-omit-frame-pointer

sanitizerbonus:
	$(CC) $(CCFLAGS) $(SRC_BONUS) $(MLX) -g -o cub3d_bonus -g -fsanitize=address -fno-omit-frame-pointer

test:
	@clear
	$(CC) $(CCFLAGS) $(TEST) tests/*.c -o test_map -lcriterion -I./src -I./utils
	./test_map

.PHONY: all bonus clean fclean