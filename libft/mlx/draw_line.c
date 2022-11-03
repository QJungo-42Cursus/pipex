/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:35:13 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/02 10:24:58 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "ft_mlx.h"
#include "../libft.h"

static int	check_max(float x, float y, t_img_data img)
{
	if (x < 0 || y < 0)
		return (1);
	if (x >= img.x_size || y >= img.y_size)
		return (1);
	return (0);
}

static void	first_calculs(t_line *line, t_vec2 *pixel, t_droite *droite)
{
	pixel->x = line->a.x;
	pixel->y = line->a.y;
	droite->m = slope(line->a, line->b);
	droite->b = ordonnate_to_origin(pixel->x, pixel->y, droite->m);
	droite->move_factor = 0.001f;
	if (line->a.x > line->b.x)
		droite->move_factor = -0.001f;
}

static void	loop(t_vec2 pixel, t_line line, t_droite droite, t_img_data *img)
{
	t_vec2	last_pixel;

	last_pixel = new_vec2(-1, -1);
	while (!assert_rounded_vec2(pixel, line.b))
	{
		pixel.y = pixel.x * droite.m + droite.b;
		pixel.x = pixel.x + droite.move_factor;
		if (check_max(pixel.x, pixel.y, *img))
			break ;
		if (last_pixel.x == pixel.x && last_pixel.y == pixel.y)
			continue ;
		last_pixel.x = pixel.x;
		last_pixel.y = pixel.y;
		pixel_to_image(img, pixel, line.color);
	}
}

static void	inf_loop(t_vec2 pixel, t_line line, t_img_data *img)
{
	while (1)
	{
		pixel.y++;
		if (round(pixel.x) != round(line.b.x))
			break ;
		if (check_max(pixel.x, pixel.y, *img))
			break ;
		pixel_to_image(img, pixel, line.color);
	}
	return ;
}

void	draw_line(t_img_data *img, t_line line)
{
	t_droite	droite;
	t_vec2		pixel;

	first_calculs(&line, &pixel, &droite);
	if (isinf(droite.m))
		inf_loop(pixel, line, img);
	else
		loop(pixel, line, droite, img);
}
