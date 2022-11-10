NAME =     		pipex
CC =			gcc
CFLAGS =		-Wall -Wextra -Werror
LIBFT =			-L./libft -lft
RM =			rm -f
SRCS = 			main.c \
				read_all_file.c
OBJS =			$(SRCS:.c=.o)

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

all: $(NAME)


clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

t: all
	./pipex /bin/ls -l -a

db:
	@make -C libft
	@$(CC) $(CFLAGS) $(SRCS) -g $(LIBFT) -o $(NAME)
	lldb ./pipex ls -l -a

.PHONY: all clean fclean re test
