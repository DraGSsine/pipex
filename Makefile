NAME = pipex

OBJS = pipex.o pipex_utilities.o ft_split.o
OBJS_BONUS = pipex_bonus.o pipex_bonus_utilities.o ft_split.o get_next_line.o get_next_line_utilities.o

CFLAGS = -Wall -Wextra -Werror

CC = gcc -g

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)
bonus:$(OBJS_BONUS)
	$(CC) $(OBJS_BONUS) -o $(NAME)
%.o: %.c pipex.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
