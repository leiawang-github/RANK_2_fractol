NAME = fractol

SRC = julia.c mandelbrot.c main.c color_options.c event_handle.c parse_args.c utilities.c
OBJS	= $(SRC:.c=.o)

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

RM = rm -f

UNAME = $(shell uname -s)

MLX_FLAGS = -Lminilibx -lmlx -framework OpenGL -framework AppKit
CFLAGS += -I./minilibx
MLX_DIR = minilibx
all: $(NAME)

mlx:
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): mlx $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	@if [ -f $(MLX_DIR)/Makefile ]; then \
		$(MAKE) -C $(MLX_DIR) clean; \
	fi
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re mlx
