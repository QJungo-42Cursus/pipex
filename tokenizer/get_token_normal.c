/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_normal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:24:19 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/28 12:26:20 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "tokenizer.h"
#include "stdio.h"

void	if_sep(char *str, int *index, int *end)
{
	t_sep	sep;
	int		f_start;

	sep = get_sep(str[*index]);
	ft_strlcpy(str + *index, str + *index + 1, ft_strlen(str + *index));
	if (sep == DQUOTE)
		get_token_dquote(str, index, &f_start, end);
	else if (sep == QUOTE)
		get_token_quote(str, index, &f_start, end);
}

void	get_token_normal(char *str, int *index, int *start, int *end)
{
	(*start) = *index;
	while (str[*index] != '\0' && !ft_isspace(str[*index]))
	{
		if (str[*index] == '\\')
			ft_strlcpy(str + *index, str + *index + 1, ft_strlen(str + *index));
		if (str[*index] == '"' || str[*index] == '\'')
			return (if_sep(str, index, end));
		if (is_in_charset(str[*index], "<>|"))
		{
			(*end) = (*index);
			return ;
		}
		(*index)++;
	}
	(*end) = (*index);
}
