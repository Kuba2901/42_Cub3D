NAME := CUB3D
CFLAGS := -Wextra -Wall -Werror -g
LIBLIBFT := ./lib/libft
HEADERS := -I ./includes/ -I $(LIBLIBFT) \
           -I ./includes/cube/mock/ \
           -I ./includes/cube/parse \
           -I ./includes/cube/utils/ \
           -I ./includes/cube/controls/ \
           -I ./includes/cube/entities/ \
           -I ./includes/cube/map/ \
           -I ./includes/cube/mlx_handler/ \
           -I ./includes/cube/runtime_handler/ \
           -I ./includes/cube/settings/ \
           -I ./includes/cube/dda/ \
           -I ./includes/cube/drawing/ \
           -I ./includes/cube/lifecycle/ \
           -I ./includes/cube/animations/ \
           -I ./includes/cube/audio/

# OS detection
UNAME_S := $(shell uname -s)

# Linux configuration
ifeq ($(UNAME_S),Linux)
    LIBMLX := ./lib/mlx_linux
    LIBMINIAUDIO := ./lib/miniaudio
    MINIAUDIO_LINKED_LIBRARIES := -lm -lpthread -ldl
    LIBS := $(LIBMLX)/libmlx.a -lXext -lX11 -lm $(LIBLIBFT)/libft.a $(MINIAUDIO_LINKED_LIBRARIES)
    HEADERS += -I $(LIBMLX) -I /usr/include/X11 -I $(LIBMINIAUDIO)
endif

# macOS configuration
ifeq ($(UNAME_S),Darwin)
    LIBMLX := ./lib/mlx_mac
    LIBMINIAUDIO := ./lib/miniaudio
    # Check for Apple Silicon
    UNAME_M := $(shell uname -m)
    ifeq ($(UNAME_M),arm64)
        # Apple Silicon
        GLFW_LIB = -L"/opt/homebrew/Cellar/glfw/3.4/lib/"
    else
        # Intel Mac
        GLFW_LIB = -L"/usr/local/Cellar/glfw/3.4/lib/"
    endif
    MINIAUDIO_LINKED_LIBRARIES := -framework AudioToolbox -framework CoreFoundation
    LIBS := $(LIBMLX)/libmlx.a -framework Cocoa -framework OpenGL -framework IOKit -ldl -lglfw -pthread -lm $(GLFW_LIB) $(LIBLIBFT)/libft.a $(MINIAUDIO_LINKED_LIBRARIES)
    HEADERS += -I $(LIBMLX) -I /usr/X11/include -I $(LIBMINIAUDIO)
    X11_FLAGS = -L/usr/X11/lib -lXext -lX11
endif

# Common source files (used by both mandatory and bonus)
SRC_COMMON := \
	./src/main.c \
	./src/utils/utils.c \
	./src/settings/textures.c \
	./src/settings/settings.c \
	./src/settings/map.c \
	./src/settings/args.c \
	./src/settings/animated_sprites.c \
	./src/runtime/runtime.c \
	./src/mlx/mlx_handler.c \
	./src/map/map_utils.c \
	./src/map/map.c \
	./src/lifecycle/lifecycle_animation.c \
	./src/lifecycle/lifecycle.c \
	./src/intro/intro.c \
	./src/input_handler/input_handler_mouse.c \
	./src/input_handler/input_handler.c \
	./src/input_handler/controls_rotation.c \
	./src/input_handler/controls_movement.c \
	./src/input_handler/controls_mouse.c \
	./src/input_handler/controls_input.c \
	./src/input_handler/controls.c \
	./src/entities/enemy/entity_enemy.c \
	./src/entities/entity/entity_entity.c \
	./src/entities/exit/entity_exit.c \
	./src/entities/player/entity_player.c \
	./src/entities/sprites/sprites_position.c \
	./src/entities/sprites/sprites_render.c \
	./src/entities/sprites/sprites_utils.c \
	./src/entities/sprites/sprites.c \
	./src/entities/entities_aux.c \
	./src/entities/entities.c \
	./src/drawing/render.c \
	./src/drawing/drawing_utils.c \
	./src/drawing/drawing_floor_ceiling.c \
	./src/drawing/drawing.c \
	./src/drawing/data_prep_and_calc.c \
	./src/drawing/credits/credits_utils.c \
	./src/drawing/credits/credits.c \
	./src/drawing/minimap/minimap_cells.c \
	./src/drawing/minimap/minimap_enemies.c \
	./src/drawing/minimap/minimap_player.c \
	./src/drawing/minimap/minimap_utils.c \
	./src/drawing/minimap/minimap.c \
	./src/dda/dda.c \
	./src/cube/cube.c \
	./src/audio/audio_utils.c \
	./src/audio/audio_integration.c \
	./src/audio/audio_init.c \
	./src/audio/audio_controls_aux.c \
	./src/audio/audio.c \
	./src/audio/audio_integration_aux.c \
	./src/audio/audio_init_aux.c \
	./src/audio/audio_impl.c \
	./src/audio/audio_controls.c \
	./src/animations/animations_animation_controller.c \
	./src/parse/parse_map_utils.c \
	./src/animations/animations.c

# Mandatory-specific source files
SRC_MANDATORY := \
	./src/parse/parse_texture_mandatory.c \
	./src/parse/parse_map_mandatory.c \
	./src/parse/parse_mandatory.c \
	./src/parse/init_mandatory.c \
	./src/parse/free_mandatory.c

# Bonus-specific source files
SRC_BONUS := \
	./src/parse/parse_texture_bonus.c \
	./src/parse/parse_map_bonus.c \
	./src/parse/parse_bonus.c \
	./src/parse/init_bonus.c 

# Object files for mandatory and bonus
OBJS_COMMON := $(SRC_COMMON:.c=.o)
OBJS_MANDATORY := $(SRC_MANDATORY:.c=.o)
OBJS_BONUS := $(SRC_BONUS:.c=.o)

# Default target
all: mandatory

# Mandatory target
.PHONY: mandatory
mandatory: CFLAGS += -D CUBE_MANDATORY=1
mandatory: $(OBJS_COMMON) $(OBJS_MANDATORY)
	@echo "Building mandatory version..."
	@make liblibft
	@make libmlx
	@echo "Linking $(NAME)..."
ifeq ($(UNAME_S),Darwin)
	@$(CC) $(CFLAGS) $(OBJS_COMMON) $(OBJS_MANDATORY) $(LIBS) $(HEADERS) $(X11_FLAGS) -o $(NAME)
else
	@$(CC) $(CFLAGS) $(OBJS_COMMON) $(OBJS_MANDATORY) $(LIBS) $(HEADERS) -o $(NAME)
endif
	@echo "$(NAME) (mandatory version) successfully built!"

# Bonus target
.PHONY: bonus
bonus: CFLAGS += -D CUBE_BONUS=1
bonus: fclean $(OBJS_COMMON) $(OBJS_BONUS)
	@echo "Building bonus version..."
	@make liblibft
	@make libmlx
	@echo "Linking $(NAME) (bonus)..."
ifeq ($(UNAME_S),Darwin)
	@$(CC) $(CFLAGS) $(OBJS_COMMON) $(OBJS_BONUS) $(LIBS) $(HEADERS) $(X11_FLAGS) -o $(NAME)
else
	@$(CC) $(CFLAGS) $(OBJS_COMMON) $(OBJS_BONUS) $(LIBS) $(HEADERS) -o $(NAME)
endif
	@echo "$(NAME) (bonus version) successfully built!"

# Library targets
liblibft:
	@cd $(LIBLIBFT) && make

libmlx:
	@cd $(LIBMLX) && make

# Rule for compiling .c files
%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

# Clean targets
clean:
	@echo "Cleaning object files..."
	@rm -rf $(shell find ./src/ -name "*.o")
	@cd $(LIBLIBFT) && make clean
	@cd $(LIBMLX) && ./configure clean

fclean: clean
	@echo "Cleaning executable..."
	@rm -rf $(NAME)
	@rm -f $(LIBLIBFT)/libft.a
	@rm -f $(LIBMLX)/libmlx.a

configure:
	@echo "Installing MLX..."
	@if [ ! -d "./lib/mlx_linux" ]; then \
		echo "Cloning MLX repository..."; \
		git clone https://github.com/42Paris/minilibx-linux ./lib/mlx_linux; \
	else \
		echo "MLX repository already exists. Skipping clone."; \
	fi
	@if [ ! -d "./lib/mlx_mac" ]; then \
		echo "Copying MLX to macOS directory..."; \
		cp -r ./lib/mlx_linux ./lib/mlx_mac; \
	else \
		echo "MLX macOS directory already exists. Skipping copy."; \
	fi
	@echo "Installing Miniaudio..."
	@if [ ! -d "./lib/miniaudio" ]; then \
		echo "Cloning Miniaudio repository..."; \
		git clone git@github.com:mackron/miniaudio.git ./lib/miniaudio; \
	else \
		echo "Miniaudio repository already exists. Skipping clone."; \
	fi
	@echo "Configuring MLX..."
	@cd $(LIBMLX) && ./configure

re: fclean all

.PHONY: all clean fclean re libmlx liblibft