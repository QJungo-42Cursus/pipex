/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 08:57:15 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/03 09:45:27 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <unistd.h>

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char *ars[] = {NULL, "salut", NULL};
	char *envp[] = {NULL};
	int		res = execve("./a.sh", ars, envp);
	printf("yooo (res de %d)\n", res);
	(void)res;

}
