NAME = pipex

OBJS = pipex.o utilities.o ft_split.o
OBJS_BONUS = utilities.o pipex_bonus.o pipex_bonus_utilities.o ft_split.o read_line.o read_line_utilities.o

CFLAGS = -Wall -Wextra -Werror
CC = cc

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
