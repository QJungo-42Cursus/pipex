#include "../libft/libft.h"

typedef struct s_word {
	int	pos;
	int	len;
}	t_word;

static void	*free_all(char ***res)
{
	int	i;

	i = 0;
	while ((*res)[i] != NULL)
	{
		free((*res)[i]);
		i++;
	}
	free(*res);
	return (NULL);
}

static void	to_next_quote(char const *s, t_word *words, int *i_char, int *i_word)
{
	char	sep;

	sep = s[*i_char];
	(*i_char)++; 

	words[*i_word].pos = *i_char;
	while (s[*i_char] != sep && s[*i_char] != '\0')
	{
		if (s[*i_char] == '\\')
			ft_memmove();
		ft_printf("%c ", s[*i_char]);
		(*i_char)++;
	}
	words[*i_word].len = *i_char - words[*i_word].pos;
	//ft_printf("%d newx start->%d len->%d\n\n", *i_char, words[*i_word].pos, words[*i_word].len);
	(*i_word)++;
	(*i_char)++;
}

static int	index_words(char const *s, t_word *words)
{
	int	i_char;
	int	i_word;

	i_char = 0;
	i_word = 0;
	while (s[i_char] != '\0')
	{
		//ft_printf("%d \n", i_char);
		if (s[i_char] == ' ')
			i_char++;
		else if (s[i_char] != ' ')
		{
			words[i_word].pos = i_char;
			while (s[i_char] != ' ' && s[i_char] != '\0')
				i_char++;
			words[i_word].len = i_char - words[i_word].pos;
			i_word++;
		}
		if (s[i_char] == 39 || s[i_char] == 34)
			to_next_quote(s, words, &i_char, &i_word);
	}
	return (i_word);
}

char	**get_argv(char const *argv)
{
	t_word	words[2048];
	int		n_word;
	int		i_word;
	char	**res;

	n_word = index_words(argv, words);
	res = malloc((n_word + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	i_word = 0;
	while (i_word < n_word)
	{
		res[i_word] = ft_substr(argv, words[i_word].pos, words[i_word].len);
		//ft_printf("%i - %s \n",i_word, res[i_word]);
		if (res[i_word] == NULL)
			return (free_all(&res));
		i_word++;
	}
	res[i_word] = NULL;
	return (res);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 10:59:40 by qjungo            #+#    #+#             */
/*   Updated: 2022/10/11 10:45:57 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*dest_ptr;
	char		*src_ptr;

	if (!dest && !src)
		return (dest);
	dest_ptr = (char *)dest;
	src_ptr = (char *)src;
	i = -1;
	if (dest > src)
		while (++i < n)
			dest_ptr[n - i - 1] = src_ptr[n - i - 1];
	else
		while (++i < n)
				dest_ptr[i] = src_ptr[i];
	return (dest);
}
