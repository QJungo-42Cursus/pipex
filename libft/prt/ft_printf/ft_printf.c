/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:26:53 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/01 13:12:03 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "t_word.h"
#include "../../libft.h"
#include "conversions/conversions.h"
#include "writer/writer.h"
#include "utils/utils.h"

int	ft_printf(const char *string, ...)
{
	va_list	args;
	t_word	words[2048];
	int		word_count;
	int		n_char;

	if (string == NULL)
		return (-1);
	word_count = index_w(string, words);
	if (word_count == 0)
		return (0);
	va_start(args, string);
	n_char = writer(word_count, words, args, string);
	va_end(args);
	return (n_char);
}
