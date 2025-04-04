NAME = Cub3D

LIBFTDIR = Libft
LIBFT = $(LIBFTDIR)/libft.a

MLXDIR = mlx
MLX = $(MLXDIR)/libmlx.a

SRC = src/main.c \
	src/init.c \
	src/read_map.c \
	GNL/get_next_line.c \
	GNL/get_next_line_utils.c \

OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I$(MLXDIR)
LDFLAGS = -L$(LIBFTDIR) -lft -L$(MLXDIR) -lmlx -lXext -lX11

all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(MLX):
	$(MAKE) -C $(MLXDIR)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(MLXDIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
	rm -f $(MLX)
	rm -rf $(MLXDIR)/OBJ/

re: fclean all

.PHONY: all clean fclean re