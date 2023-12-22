NAME = pipex

OBJS = pipex.o pipex_utilitis.o

SRCS = pipex.c pipex_utilitis.c

CFLAGS = -Wall -Wextra -Werror

CC = gcc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
