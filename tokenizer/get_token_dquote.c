/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_dquote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:26:43 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/28 12:28:38 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"

static int	check(char *str, int *index, int *start, int *end)
{
	if (str[*index + 1] == '\0')
	{
		*start = -1;
		*end = -1;
		return (1);
	}
	(*index)++;
	if (str[*index] == '"')
	{
		*end = -1;
		*start = -1;
		(*index)++;
		return (1);
	}
	return (0);
}

void	get_token_dquote(char *str, int *index, int *start, int *end)
{
	if (check(str, index, start, end))
		return ;
	(*start) = *index;
	while (str[*index] != '"')
	{
		if (str[*index] == '\\')
			ft_strlcpy(str + *index, str + *index + 1, ft_strlen(str + *index));
		if (str[*index] == '\0')
			break ;
		(*index)++;
	}
	if (!ft_isspace(str[*index]) && str[*index] != '\0')
		ft_strlcpy(str + *index, str + *index + 1, ft_strlen(str + *index));
	while (!ft_isspace(str[*index]) && str[*index] != '\0')
		(*index)++;
	(*end) = (*index);
}
