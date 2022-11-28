/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 07:19:44 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/28 12:58:38 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>			// exit()
#include <errno.h>			// errno
#include <stdio.h>			// perror()
#include "libft/libft.h"	// ft_putendl_fd()
#include "pipex.h"			// END

void	terminate(char *s)
{
	if (errno == 0)
	{
		ft_putendl_fd(s, 2);
		exit(1);
	}
	else
		perror(s);
	exit(1);
}
//exit(errno);

void	full_free(t_command **cmds, char *err_msg, int fd1, int fd2)
{
	int		i;

	close(fd1);
	close(fd2);
	i = 0;
	while ((*cmds)[i - 1].position != END)
	{
		if ((*cmds)[i].argv != NULL)
			split_free((*cmds)[i].argv);
		if ((*cmds)[i].path != NULL)
			free((*cmds)[i].path);
		i++;
	}
	free(*cmds);
	if (err_msg != NULL)
		terminate(err_msg);
}
