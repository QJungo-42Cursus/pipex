/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 08:57:15 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/10 15:13:48 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft/libft.h"

int	main(int argc, char **argv)
{
	if (argc < 3)
	{
		ft_printf("pas assez d'args\n");
		return (0);
	}
	char	*envp[] = {NULL};
	int		res = execve(argv[1], &argv[2], envp);
	ft_printf("yooo (res de %d)\n", res);
	(void)res;

}
