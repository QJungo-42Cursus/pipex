/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:53:02 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/28 11:53:24 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/// Renvoie un substr du prochain token qu'il se charge de trouver 
/// + avance le curseur (l'index)
/// En cas d'erreur, renvoie NULL ET set errno
/// Il peut arriver qu'il renvoie NULL sans erreur (ex: ' echo salut ""')
///    -> Dans ce cas, il faut juste passer au token suivant
char	*get_next_token(char *str, int *index)
{
	int			start;
	int			end;
	t_sep		sep;
	t_get_token	*get_token;

	if (str[*index] == '\0' || str == NULL || index == NULL)
		return (NULL);
	while (ft_isspace(str[*index]) && str[*index] != '\0')
		(*index)++;
	start = *index;
	sep = get_sep(str[*index]);
	if (sep == SEP_ERROR)
		return (NULL);
	else
	{
		get_token = list_func();
		if (get_token == NULL)
			return (NULL);
		get_token[sep](str, index, &start, &end);
		free(get_token);
	}
	if (start == -1 || end == start)
		return (NULL);
	else
		return (ft_substr(str, start, end - start));
}

void	tokenize(char *line, int *index, t_list **tokens)
{
	char	*token;

	token = get_next_token(line, index);
	if (token != NULL)
		ft_lstadd_back(tokens, ft_lstnew(token));
	if (*index == ft_strlen(line))
		return ;
	tokenize(line, index, tokens);
}

t_list	*tokenizer(char *str)
{
	t_list	*tokens;
	int		index;

	index = 0;
	tokens = NULL;
	tokenize(str, &index, &tokens);
	return (tokens);
}
