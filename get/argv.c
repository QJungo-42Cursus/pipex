/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:49:06 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/28 11:49:07 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../tokenizer/tokenizer.h"

static void	*free_all(char ***res, t_list **tokens)
{
	int	i;

	i = 0;
	while ((*res)[i] != NULL)
	{
		free((*res)[i]);
		i++;
	}
	free(*res);
	ft_lstclear(tokens, free);
	return (NULL);
}

static char	**transfert(t_list *tokens)
{
	int		i_word;
	t_list	*token_ptr;
	char	**res;

	i_word = 0;
	token_ptr = tokens;
	res = malloc((ft_lstsize(tokens) + 1) * sizeof(char *));
	if (res == NULL)
	{
		ft_lstclear(&tokens, free);
		return (NULL);
	}
	while (token_ptr != NULL)
	{
		res[i_word] = ft_strdup((char *)token_ptr->content);
		if (res[i_word] == NULL)
			return (free_all(&res, &tokens));
		token_ptr = token_ptr->next;
		i_word++;
	}
	res[i_word] = NULL;
	return (res);
}

// Le but de cette fonction est de separer en split les arguments 
// qui sont en un string
// ca tokenize !
char	**get_argv(char const *argv)
{
	char	**res;
	t_list	*tokens;

	tokens = tokenizer((char *)argv);
	if (tokens == NULL)
		return (NULL);
	res = transfert(tokens);
	ft_lstclear(&tokens, free);
	return (res);
}
