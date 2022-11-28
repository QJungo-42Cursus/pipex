#include "../libft/libft.h"
#include <stdio.h>
#include "tokenizer.h"

void	log_tokens(t_list *tokens)
{
	//printf("log_tokens called for a list with %d el\n", ft_lstsize(tokens));
	while (tokens)
	{
		printf("|%s| ", (char *)tokens->content);
		fflush ( stdout );
		tokens = tokens->next;
	}
}

void	log_sep(t_sep sep)
{
	if (sep == QUOTE)
		printf("QUOTE");
	else if (sep == DQUOTE)
		printf("DQUOTE");
	else if (sep == NONE)
		printf("NONE");
	else if (sep == SEP_ERROR)
		printf("ERROR");
	else
		printf("UNKNOWN???");
	printf(" (%d)\n", sep);
	fflush ( stdout );
}
