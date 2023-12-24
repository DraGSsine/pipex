NAME = pipex

OBJS = pipex.o pipex_utilities.o ft_split.o

CFLAGS = -Wall -Wextra -Werror

CC = gcc -g

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.c pipex.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
