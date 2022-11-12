NAME =     		pipex
CC =			gcc
CFLAGS =		-Wall -Wextra -Werror
LIBFT =			-L./libft -lft
RM =			rm -f
SRCS = 			main.c \
				get/env_path.c \
				get/cmd_path.c \
				read_all_file.c

OBJS =			$(SRCS:.c=.o)

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

all: $(NAME)


clean:
	@make clean -C libft
	@$(RM) $(OBJS)

fclean: clean
	@make fclean -C libft
	@$(RM) $(NAME)

re: fclean all

t: all
	./pipex "./infile" "ls -l -a" "wc -l" "./outfile"

db:
	@make -C libft
	@$(CC) $(CFLAGS) $(SRCS) -g $(LIBFT) -o $(NAME)
	lldb ./pipex ls -l -a

.PHONY: all clean fclean re test
