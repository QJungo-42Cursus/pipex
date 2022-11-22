NAME =     		pipex
CC =			gcc
CFLAGS =		-Wall -Wextra -Werror
LIBFT =			-L./libft -lft
RM =			rm -f

# shared
S_SRCS =		utils.c \
				read_all_file.c \
				get/env_path.c \
				get/cmd_path.c \
				get/argv.c \
				get/commands.c

M_SRC =			main.c
M_SRCS =		$(addprefix mandatory/, $(M_SRC))

S_OBJS =		$(S_SRCS:.c=.o)
M_OBJS =		$(M_SRCS:.c=.o)
#B_OBJS =		$(SRCS:.c=.o)

libft:
	@make -C ../libft
	mkdir -p libft
	cp ../libft/libft.a libft
	cp ../libft/libft.h libft
	find ../libft -name '*.h' | cpio -pdm 'libft/'

$(NAME): $(M_OBJS) $(S_OBJS)
	make libft
	#@make -C libft
	@$(CC) $(CFLAGS) $(S_OBJS) $(M_OBJS) $(LIBFT) -o $(NAME)

#bonus: $(B_OBJS) $(S_OBJS)
#	@make -C libft
#	@$(CC) $(CFLAGS) $(B_OBJS) $(S_OBJS) $(LIBFT) -o $(NAME)

all: $(NAME)

clean:
	#@make clean -C libft
	@$(RM) -r libft
	@$(RM) $(S_OBJS) $(M_OBJS)

fclean: clean
	#@make fclean -C libft
	@$(RM) $(NAME)

re: fclean
	make libft
	make all

t: all
	$(RM) outfile
	./pipex "infile" "cat" "wc -l" "outfile"

hard: all
	$(RM) outfile
	./pipex "infile" "cat -e" "grep \\\\" "outfile"

tb: all
	$(RM) outfile boutfile
	./pipex "infile" "wc -l" "cat" "cat" "cat" "cat" "cat" "cat" "boutfile"
#./pipex "infile" "cat" "cat" "cat" "boutfile"
#./pipex "infile" "cat" "grep i" "cat" "wc" "cat" "outfile"

db:
	@make -C libft
	@$(CC) $(CFLAGS) $(SRCS) -g $(LIBFT) -o $(NAME)
	lldb ./pipex ls -l -a

.PHONY: all clean fclean re test libft
