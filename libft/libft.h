/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 21:22:48 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/02 15:47:29 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "math/ft_math.h"
# include "char/char.h"
# include "prt/prt.h"
# include "lst/lst.h"
# include "nb/nb.h"
# include "mem/mem.h"
# include "str/str.h"
# include "mlx/ft_mlx.h"

# ifndef INT_MIN
#  define INT_MIN -2147483648
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif

typedef enum e_bool {
	FALSE,
	TRUE,
	SUCCESS = 0,
	ERROR = 1,
}	t_bool;

char	*get_next_line(int fd);

#endif

// void	color(int color, int font);
/* enum e_color {
	BLUE,
	RED,
	YELLOW,
	PURPLE,
	GREEN,
	CYAN,
	WHITE,
	RESET,
	BOLD,
	STD,
};

void	ft_color(int color, int font)
{
	if (color == RESET)
		printf("\033[0m");
	if (color == RED)
		printf("\033[0;31m");
	if (color == GREEN)
		printf("\033[0;32m");
	if (color == YELLOW)
		printf("\033[0;33m");
	if (color == BLUE)
		printf("\033[0;34m");
	if (color == PURPLE)
		printf("\033[0;35m");
	if (color == CYAN)
		printf("\033[0;36m");
	if (color == WHITE)
		printf("\033[0;37m");
	if (font == BOLD)
		printf("\033[1m");
}
*/
