NAME =     		pipex
CC =			gcc
CFLAGS =		-Wall -Wextra -Werror
LIBFT =			-L./libft -lft
RM =			rm -f

# shared
S_SRCS =		utils.c \
				get/env_path.c \
				get/cmd_path.c \
				get/argv.c \
				get/commands.c \
				tokenizer/tokenizer.c \
				tokenizer/get_next_token_functions.c \
				tokenizer/get_token_normal.c \
				tokenizer/get_token_quote.c \
				tokenizer/get_token_dquote.c \
				tokenizer/debug_helpers.c

M_SRC =			main.c
M_SRCS =		$(addprefix mandatory/, $(M_SRC))

S_OBJS =		$(S_SRCS:.c=.o)
M_OBJS =		$(M_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(M_OBJS) $(S_OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(S_OBJS) $(M_OBJS) $(LIBFT) -o $(NAME)

u_libft:
	rm -rf libft
	cp -r ../libft .
	rm -rf libft/.git

clean:
	@make clean -C libft
	@$(RM) $(S_OBJS) $(M_OBJS)

fclean: clean
	@make fclean -C libft
	@$(RM) $(NAME)

re: fclean all

t: all
	$(RM) outfile
	./pipex "infile" "cat" "wc -l" "outfile"

SAN =	-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all \
		-fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow \
		-fno-sanitize=null -fno-sanitize=alignment

san:
	@make -C libft
	@$(CC) $(CFLAGS) $(M_SRCS) $(S_SRCS) $(SAN) -g $(LIBFT) -o $(NAME)
	./pipex "infile" "cat" "wc -l" "outfile"

.PHONY: all clean fclean re
