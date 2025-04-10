NAME = Cub3D

LIBFTDIR = Libft
LIBFT = $(LIBFTDIR)/libft.a

MLXDIR = mlx
MLX = $(MLXDIR)/libmlx.a

OBJDIR = obj

SRC = src/main.c \
	src/init.c \
	src/read_map.c \
	src/check_arg.c \
	src/free_exit.c \
	src/check_map_texture.c \
	src/check_map_color_and_xpm.c \
	src/extract_map_texture_and_color.c \
	src/extract_map.c \
	src/parsing_map.c \
	GNL/get_next_line.c \
	GNL/get_next_line_utils.c \

OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I$(MLXDIR)
LDFLAGS = -L$(LIBFTDIR) -lft -L$(MLXDIR) -lmlx -lXext -lX11

all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(LDFLAGS) -o $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(MLX):
	$(MAKE) -C $(MLXDIR)

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(MLXDIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
	rm -f $(MLX)
	rm -rf $(MLXDIR)/OBJ/

re: fclean all

.PHONY: all clean fclean re