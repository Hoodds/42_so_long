NAME = so_long

SRCS = src/main.c src/map.c
OBJS = $(SRCS:.c=.o)

#INCLUDES = -Iinclude -Ilibft -IMLX42/include
LIBFT = libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibft -IMLX42/include

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) MLX42/build/libmlx42.a -lglfw -ldl -lm -lpthread

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all
