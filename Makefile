CC          =   gcc
CFLAGS      =   -Wall -Wextra -Werror -Wno-unused-result -O3 -I$(INCLUDE_DIR)
SRC_DIR     =   srcs
INCLUDE_DIR =   includes
LIBFT_PATH	=	./includes/libft/
MLX_FILE	=	libmlx.a
LIBFT_FILE	=	libft.a
LIBFT_LIB	=	$(LIBFT_PATH)$(LIBFT_FILE)
LIBFT_EX	=	$(LIBFT_LIB) $(CFLAGS)
MLX_DIR     =   minilibx-linux
NAME        =   miniRT
MLX_LIB     =   $(MLX_DIR)/libmlx_Linux.a
SRCS        =   $(wildcard $(SRC_DIR)/utils/*.c)     \
                $(wildcard $(SRC_DIR)/parsing/*.c)    \
                $(wildcard $(SRC_DIR)/main/*.c)       \
                $(wildcard ./GNL/*.c)                 \
                $(wildcard $(SRC_DIR)/*.c)

OBJS        =   $(SRCS:.c=.o)

define FONT_3D
    echo "\033[1;34m" && \
    figlet -f slant "$(1)" && \
    echo "\033[0m"
endef

all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)

%.o: %.c
	@echo "\033[34mCompilation de $<\033[0m"
	@$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@ > /dev/null

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "\033[34mCompilation de $<\033[0m"
	@$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@ > /dev/null

$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT_LIB)
	@echo "\033[34m╔════════════════════════════════════════╗\033[0m"
	@echo "\033[34m║      Compilation de miniRT...          ║\033[0m"
	@echo "\033[34m╚════════════════════════════════════════╝\033[0m"
	@$(CC) $(OBJS) $(MLX_LIB) -L/usr/lib -I$(MLX_DIR) -lXext -lX11 -lm $(LIBFT_LIB) -o $(NAME) > /dev/null
	@echo "\033[1;33mminiRT\033[0m\033[32m compilé avec succès\033[0m"

$(MLX_LIB):
	@echo "\033[35m┌────────────────────────────────────────┐\033[0m"
	@echo "\033[35m│     Compilation de la MiniLibX...      │\033[0m"
	@echo "\033[35m└────────────────────────────────────────┘\033[0m"
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1
	@ar rcs $@ $^ 2> /dev/null
	@echo "\033[32mMiniLibX compilée avec succès\033[0m"

$(LIBFT_LIB):
	@echo "\033[35m┌────────────────────────────────────────┐\033[0m"
	@echo "\033[35m│     Compilation de la Libft...         │\033[0m"
	@echo "\033[35m└────────────────────────────────────────┘\033[0m"
	@$(MAKE) -C $(LIBFT_PATH) > /dev/null 2>&1
	@echo "\033[32mLibft compilée avec succès\033[0m"

clean:
	@echo "\033[33mNettoyage des fichiers objets...\033[0m"
	@rm -f $(OBJS) > /dev/null
	@echo "\033[32mNettoyage terminé\033[0m"

fclean: clean
	@rm -f $(NAME) > /dev/null
	@$(MAKE) -C $(MLX_DIR) clean > /dev/null
	@echo "\033[32mSuppression complète effectuée\033[0m"

re: fclean all

.PHONY: all clean fclean re
