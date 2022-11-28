/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:51:34 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/28 11:52:18 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# include "../libft/libft.h"
# define TOKENIZER_H
# define SEP_NB 4

typedef enum e_sep
{
	QUOTE,
	DQUOTE,
	SEP_ERROR,
	NONE
}	t_sep;

typedef void	(*t_get_token)(char *str, int *index, int *start, int *end);

void		get_token_dquote(char *str, int *index, int *start, int *end);
void		get_token_quote(char *str, int *index, int *start, int *end);
void		get_token_normal(char *str, int *index, int *start, int *end);

t_get_token	*list_func(void);
t_sep		get_sep(char sep);
t_list		*tokenizer(char *str);

//	debug helpers
void		log_tokens(t_list *tokens);
void		log_sep(t_sep sep);

#endif /* TOKENIZER_H */
