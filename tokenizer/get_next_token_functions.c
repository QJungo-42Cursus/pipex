#include "tokenizer.h"
#include "../libft/libft.h"
#include <stdio.h>

/// Return the separator type of the first char of the string
/// For the bash interpreter
t_sep	get_sep(char sep)
{
	if (sep == '"')
		return (DQUOTE);
	if (sep == '\'')
		return (QUOTE);
	if (ft_isprint(sep))
		return (NONE);
	return (SEP_ERROR);
}

t_get_token	*list_func()
{
	t_get_token	*list;

	list = (t_get_token *)malloc(sizeof(t_get_token) * SEP_NB);
	if (list == NULL)
		return (NULL);
	list[DQUOTE] = get_token_dquote;
	list[QUOTE] = get_token_quote;
	list[NONE] = get_token_normal;
	return (list);
}
