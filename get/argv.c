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

static void	to_next_quote(
		char const *s, t_word *words, int *i_char, int *i_word)
{
	char	sep;

	sep = s[*i_char];
	(*i_char)++;
	words[*i_word].pos = *i_char;
	while (s[*i_char] != sep && s[*i_char] != '\0')
	{
		(*i_char)++;
	}
	words[*i_word].len = *i_char - words[*i_word].pos;
	(*i_word)++;
	(*i_char)++;
}
/*
// Si c'est un back slash .. (inutile ??)
if (s[*i_char] == 92)
{
	// Set celui d'apres directement... 
	//ft_memmove(&(s[*i_char]), &(s[(*i_char) + 1]), ft_strlen(&(s[*i_char])));
	//ft_printf("\\\\", s[*i_char]);
}
*/

static int	index_words(char const *s, t_word *words)
{
	int	i_char;
	int	i_word;

	i_char = 0;
	i_word = 0;
	while (s[i_char] != '\0')
	{
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
		if (res[i_word] == NULL)
			return (free_all(&res));
		i_word++;
	}
	res[i_word] = NULL;
	return (res);
}
