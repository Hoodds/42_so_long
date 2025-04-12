NAME = so_long

SRCS = src/main.c src/map.c
OBJS = $(SRCS:.c=.o)

INCLUDES = -Iinclude -Ilibft
LIBFT = libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)
	
re: fclean all
