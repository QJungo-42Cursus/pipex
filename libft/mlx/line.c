/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:27:36 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/02 10:13:42 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

t_line	new_line(t_vec2 a, t_vec2 b, int color, int thickness)
{
	t_line	line;

	line.a = a;
	line.b = b;
	line.color = color;
	line.thickness = thickness;
	return (line);
}
