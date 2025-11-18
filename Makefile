NAME := CUB3D
CC := cc
CFLAGS := -Wextra -Wall -Werror -g -MMD -MP
LIBLIBFT := ./lib/libft

# Headers
HEADERS := -I ./includes/ -I $(LIBLIBFT) \
           -I ./includes/cube/mock/ -I ./includes/cube/parse \
           -I ./includes/cube/utils/ -I ./includes/cube/controls/ \
           -I ./includes/cube/entities/ -I ./includes/cube/map/ \
           -I ./includes/cube/mlx_handler/ -I ./includes/cube/runtime_handler/ \
           -I ./includes/cube/settings/ -I ./includes/cube/dda/ \
           -I ./includes/cube/drawing/ -I ./includes/cube/lifecycle/ \
           -I ./includes/cube/animations/ -I ./includes/cube/audio/

# OS-specific settings
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LIBMLX := ./lib/mlx_linux
    LIBS := $(LIBMLX)/libmlx.a $(LIBLIBFT)/libft.a -lXext -lX11 -lm -lpthread -ldl
    HEADERS += -I $(LIBMLX) -I /usr/include/X11 -I ./lib/miniaudio
else ifeq ($(UNAME_S),Darwin)
    LIBMLX := ./lib/mlx_mac
    UNAME_M := $(shell uname -m)
    GLFW_PATH := $(if $(filter arm64,$(UNAME_M)),/opt/homebrew,/usr/local)/Cellar/glfw/3.4/lib/
    LIBS := $(LIBMLX)/libmlx.a $(LIBLIBFT)/libft.a -framework Cocoa -framework OpenGL \
            -framework IOKit -framework AudioToolbox -framework CoreFoundation \
            -L$(GLFW_PATH) -lglfw -L/usr/X11/lib -lXext -lX11 -ldl -lm -pthread
    HEADERS += -I $(LIBMLX) -I /usr/X11/include -I ./lib/miniaudio
endif

# Source files
SRC_COMMON := src/main.c src/utils/utils.c src/settings/textures.c \
              src/settings/settings.c src/settings/map.c src/settings/args.c \
              src/settings/animated_sprites.c src/settings/map_utils.c \
			  src/settings/textures_free.c src/runtime/runtime.c \
			  src/settings/textures_utils.c \
              src/mlx/mlx_handler.c src/map/map_utils.c src/map/map.c \
              src/lifecycle/lifecycle_animation.c src/lifecycle/lifecycle.c \
              src/intro/intro.c src/input_handler/input_handler_mouse.c \
              src/input_handler/input_handler.c src/input_handler/controls_rotation.c \
              src/input_handler/controls_movement.c src/input_handler/controls_mouse.c \
              src/input_handler/controls_input.c src/input_handler/controls.c \
              src/entities/enemy/entity_enemy.c src/entities/entity/entity_entity.c \
              src/entities/exit/entity_exit.c src/entities/player/entity_player.c \
              src/entities/sprites/sprites_position.c src/entities/sprites/sprites_render.c \
              src/entities/sprites/sprites_utils.c src/entities/sprites/sprites.c \
              src/entities/entities_aux.c src/entities/entities.c src/drawing/render.c \
              src/drawing/drawing_utils.c src/drawing/drawing_floor_ceiling.c \
              src/drawing/drawing.c src/drawing/data_prep_and_calc.c \
              src/drawing/credits/credits_utils.c src/drawing/credits/credits.c \
              src/drawing/minimap/minimap_cells.c src/drawing/minimap/minimap_enemies.c \
              src/drawing/minimap/minimap_player.c src/drawing/minimap/minimap_utils.c \
              src/drawing/minimap/minimap.c src/dda/dda.c src/cube/cube.c \
              src/audio/audio_utils.c src/audio/audio_integration.c \
              src/audio/audio_init.c src/audio/audio_controls_aux.c src/audio/audio.c \
              src/audio/audio_integration_aux.c src/audio/audio_init_aux.c \
              src/audio/audio_impl.c src/audio/audio_controls.c \
              src/animations/animations_animation_controller.c \
              src/parse/parse_map_utils.c src/parse/check_map_utils.c \
              src/parse/realloc_map_utils.c src/animations/animations.c \
              src/parse/parse_utils.c

SRC_MANDATORY := src/parse/parse_texture_mandatory.c src/parse/parse_map_mandatory.c \
                 src/parse/parse_mandatory.c src/parse/init_mandatory.c \
                 src/parse/free_mandatory.c

SRC_BONUS := src/parse/parse_texture_bonus.c src/parse/parse_map_bonus.c \
             src/parse/parse_bonus.c src/parse/init_bonus.c

# Object and dependency directories
OBJS_DIR_MANDATORY := obj/mandatory
OBJS_DIR_BONUS := obj/bonus

# Object and dependency files
OBJS_COMMON_MANDATORY := $(addprefix $(OBJS_DIR_MANDATORY)/, $(SRC_COMMON:.c=.o))
OBJS_MANDATORY_MANDATORY := $(addprefix $(OBJS_DIR_MANDATORY)/, $(SRC_MANDATORY:.c=.o))
OBJS_COMMON_BONUS := $(addprefix $(OBJS_DIR_BONUS)/, $(SRC_COMMON:.c=.o))
OBJS_BONUS_BONUS := $(addprefix $(OBJS_DIR_BONUS)/, $(SRC_BONUS:.c=.o))

DEPS_MANDATORY := $(OBJS_COMMON_MANDATORY:.o=.d) $(OBJS_MANDATORY_MANDATORY:.o=.d)
DEPS_BONUS := $(OBJS_COMMON_BONUS:.o=.d) $(OBJS_BONUS_BONUS:.o=.d)

# Include dependency files
-include $(DEPS_MANDATORY)
-include $(DEPS_BONUS)

# Default target
all: $(NAME)

# Mandatory version
$(NAME): $(OBJS_COMMON_MANDATORY) $(OBJS_MANDATORY_MANDATORY) | libraries
	@$(CC) $(CFLAGS) -D CUBE_MANDATORY=1 $^ $(LIBS) -o $@
	@echo "✅ $(NAME) built successfully!"

# Bonus version
bonus: $(OBJS_COMMON_BONUS) $(OBJS_BONUS_BONUS) | libraries
	@$(CC) $(CFLAGS) -D CUBE_BONUS=1 $^ $(LIBS) -o $(NAME)
	@echo "✅ $(NAME) (bonus) built successfully!"

# Libraries
libraries: $(LIBLIBFT)/libft.a $(LIBMLX)/libmlx.a

$(LIBLIBFT)/libft.a:
	@cd $(LIBLIBFT) && make

$(LIBMLX)/libmlx.a: | configure
	@cd $(LIBMLX) && make

# Compilation rules
$(OBJS_DIR_MANDATORY)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -D CUBE_MANDATORY=1 -c $< -o $@ $(HEADERS)
	@printf "Compiling (mandatory): $(notdir $<)\n"

$(OBJS_DIR_BONUS)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -D CUBE_BONUS=1 -c $< -o $@ $(HEADERS)
	@printf "Compiling (bonus): $(notdir $<)\n"

# Setup dependencies
configure:
	@[ -d "./lib/mlx_linux" ] || git clone https://github.com/42Paris/minilibx-linux ./lib/mlx_linux
	@[ -d "./lib/mlx_mac" ] || cp -r ./lib/mlx_linux ./lib/mlx_mac
	@[ -d "./lib/miniaudio" ] || git clone https://github.com/mackron/miniaudio.git ./lib/miniaudio
	@cd $(LIBMLX) && ./configure

# Debug builds
debug: CFLAGS += -fsanitize=address -fsanitize=undefined
debug: $(NAME)

valgrind: CFLAGS += -DDEBUG
valgrind: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

# Clean targets
clean:
	@rm -rf $(OBJS_DIR_MANDATORY) $(OBJS_DIR_BONUS)
	@cd $(LIBLIBFT) && make clean 2>/dev/null || true
	@cd $(LIBMLX) && make clean 2>/dev/null || true

fclean: clean
	@rm -f $(NAME)
	@cd $(LIBLIBFT) && make fclean 2>/dev/null || true

re: fclean all

.PHONY: all bonus libraries configure debug valgrind clean fclean re