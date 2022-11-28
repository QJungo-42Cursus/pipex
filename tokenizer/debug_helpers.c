/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:51:07 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/28 12:22:58 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "tokenizer.h"

//printf("log_tokens called for a list with %d el\n", ft_lstsize(tokens));
void	log_tokens(t_list *tokens)
{
	while (tokens)
	{
		ft_printf("|%s| ", (char *)tokens->content);
		tokens = tokens->next;
	}
}

void	log_sep(t_sep sep)
{
	if (sep == QUOTE)
		ft_printf("QUOTE");
	else if (sep == DQUOTE)
		ft_printf("DQUOTE");
	else if (sep == NONE)
		ft_printf("NONE");
	else if (sep == SEP_ERROR)
		ft_printf("ERROR");
	else
		ft_printf("UNKNOWN???");
	ft_printf(" (%d)\n", sep);
}
