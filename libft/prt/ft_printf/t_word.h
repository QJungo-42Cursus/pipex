/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_word.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:46:40 by qjungo            #+#    #+#             */
/*   Updated: 2022/10/19 08:46:42 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_WORD_H
# define T_WORD_H

typedef enum e_word_type {
	WORD,
	FLAG,
}	t_word_type;

typedef struct s_word {
	int			start;
	int			len;
	t_word_type	type;
	char		*string;
	char		flag[7];
}	t_word;

#endif /* T_WORD_H */
