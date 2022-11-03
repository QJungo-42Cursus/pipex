/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:41:36 by qjungo            #+#    #+#             */
/*   Updated: 2022/10/19 15:04:05 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRITER_H
# define WRITER_H

int	writer(const int word_count,
		const t_word *words,
		va_list args,
		const char *string);

#endif /* WRITER_H */
