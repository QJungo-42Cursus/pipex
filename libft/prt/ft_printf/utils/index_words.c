/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:44:04 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/01 13:14:01 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_word.h"
#include "../../../libft.h"

static void	set_flag(
		t_word *words, int *i_word, int *i_char, const char *string)
{
	int	i_flag;

	(*i_char)++;
	words[*i_word].type = FLAG;
	i_flag = 0;
	if (string[(*i_char)] == '%')
	{
		words[*i_word].flag[0] = '%';
		words[*i_word].flag[1] = '\0';
		(*i_char)++;
		return ;
	}
	while (!is_in_charset(string[(*i_char)], "cspdiuxX"))
	{
		if (string[(*i_char)] == '%')
			return ;
		words[*i_word].flag[i_flag] = string[*i_char];
		i_flag++;
		(*i_char)++;
	}
	words[*i_word].flag[i_flag] = string[*i_char];
	words[*i_word].flag[i_flag + 1] = '\0';
	(*i_char)++;
}

static void	set_word(
		t_word *words, int *i_word, int *i_char, const char *string)
{
	words[*i_word].type = WORD;
	while (string[*i_char] != '%' && string[*i_char] != '\0')
		(*i_char)++;
	words[*i_word].len = (*i_char) - words[*i_word].start;
}

int	index_w(const char *string, t_word *words)
{
	int	i_char;
	int	i_word;

	i_char = 0;
	i_word = 0;
	while (string[i_char] != '\0')
	{
		words[i_word].start = i_char;
		if (string[i_char] == '%')
			set_flag(words, &i_word, &i_char, string);
		else
			set_word(words, &i_word, &i_char, string);
		i_word++;
	}
	return (i_word);
}
