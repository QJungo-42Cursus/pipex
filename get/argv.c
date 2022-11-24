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

//34 -> "
//39 -> '
static int	is_quote(char c)
{
	return (c == 34 || c == 39);
}

static void escape(char const *s, t_word *words, int *i_char, int *i_word)
{
	(void)words;
	(void)i_word;
	// Set celui d'apres directement... 
	char	*dest = (char *)&(s[*i_char]);
	char	*src = (char *)&(s[(*i_char) + 1]);
	int		len = ft_strlen(dest);

	// TODO il faudrait gerer chaque escape sequence pour inserer ce qu'il faut ????
	if (is_quote(s[(*i_char) + 1]) || is_in_charset(s[(*i_char) + 1]," "))
		ft_strlcpy(dest, src, len);
}

//92 -> backslash
static void	to_next_quote(
		char const *s, t_word *words, int *i_char, int *i_word)
{
	char	sep;
	t_bool	is_single_quote;
	ft_printf("to_next_quote pas in\n");

	sep = s[*i_char];
	is_single_quote = sep == 39;
	//(*i_char)++;
	words[*i_word].pos = *i_char;
	while (s[*i_char] != sep && s[*i_char] != '\0')
	{
		// Si c'est un back slash
		//if (s[*i_char] == 92 && is_quote(s[(*i_char) + 1]))
		//if (!is_single_quote && s[*i_char] == 92 && (is_quote(s[(*i_char) + 1]) || is_in_charset(s[(*i_char) + 1]," ")	 )   )
		if (!is_single_quote && s[*i_char] == 92)
			escape(s, words, i_char, i_word);

		(*i_char)++;
	}
	words[*i_word].len = *i_char - words[*i_word].pos;
	(*i_word)++;
	(*i_char)++;
}

static void	to_next_quote_in(
		char const *s, t_word *words, int *i_char, int *i_word)
{
	char	sep;
	t_bool	is_single_quote;
	ft_printf("in. debut : %d, %s\n", *i_char, &(s[*i_char]));

	// commence par tout decaler puisqu'on ne veut plus du quote
	char	*dest = (char *)&(s[*i_char]);
	char	*src = (char *)&(s[(*i_char) + 1]);
	int		len = ft_strlen(dest);

	sep = s[*i_char];
	ft_strlcpy(dest, src, len);
	is_single_quote = sep == 39;
	//(*i_char)++;
	//words[*i_word].pos = *i_char;
	while (s[*i_char] != sep && s[*i_char] != '\0')
	{
		// TODO ca marche ??
		//if (!is_single_quote && s[*i_char] == 92)
		//	escape(s, words, i_char, i_word);
		(*i_char)++;
	}
	//words[*i_word].len = *i_char - words[*i_word].pos;
	words[*i_word].len--; // Comme ca il ne prend pas le dernier quote
	words[*i_word].len--; // Comme ca il ne prend pas le dernier quote
	//(*i_word)++;
	(*i_char)++;
	ft_printf("stop here : %i %c\n", *i_char, s[*i_char]);
}

// 39 et 34 sont les valeurs ASCII de ' et "
static int	index_words(char const *s, t_word *words)
{
	int		i_char;
	int		i_word;
	t_bool	in_word; (void)in_word;

	int		i_nside;

	i_char = 0;
	i_word = 0;

	while(s[i_char])
	{
		ft_printf("%i %c\n", i_char, s[i_char]);
		i_char++;
	}
	i_char = 0;

	while (s[i_char] != '\0')
	{
		if (s[i_char] == ' ')
		{
			//in_word = FALSE;
			i_char++;
		}
		if (s[i_char] != ' ')
		{
			i_nside = 0;
			//in_word = TRUE;
			words[i_word].pos = i_char;
			words[i_word].len = 0;
			while (s[i_char] != ' ' && s[i_char] != '\0')
			{
				if (is_quote(s[i_char]) && i_nside == 0)
					to_next_quote(s, words, &i_char, &i_word);
				else if (is_quote(s[i_char]) && i_nside != 0)
					to_next_quote_in(s, words, &i_char, &i_word);
				i_char++;
				i_nside++;
			}
			words[i_word].len += i_char - words[i_word].pos;
			i_word++;
		}
		if (is_quote(s[i_char]))
			to_next_quote(s, words, &i_char, &i_word);
	}
	return (i_word);
}

// Le but de cette fonction est de separer en split les arguments 
// qui sont en un string
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
		ft_printf("%d| (%s)\n", i_word, res[i_word]); //
		if (res[i_word] == NULL)
			return (free_all(&res));
		i_word++;
	}
	res[i_word] = NULL;
	return (res);
}
