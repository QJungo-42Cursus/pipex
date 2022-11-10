NAME =     		pipex
CC =			gcc
CFLAGS =		-Wall -Wextra -Werror
RM =			rm -f
SRCS = 			main.c
OBJS =			$(SRCS:.c=.o)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

test: all
	./pipex -l -a

.PHONY: all clean fclean re test
