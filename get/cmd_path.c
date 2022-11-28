/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:49:42 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/28 11:49:43 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <unistd.h>

char	*get_cmd_path(char *name, char **env_paths)
{
	int		i;
	char	*tmp_full_path;

	i = 0;
	if (env_paths != NULL)
	{
		while (env_paths[i] != 0)
		{
			tmp_full_path = ft_sprintf("%s/%s", env_paths[i], name);
			if (access(tmp_full_path, F_OK) == 0)
				return (tmp_full_path);
			free(tmp_full_path);
			i++;
		}
	}
	if (access(name, F_OK) == 0 && ft_strchr(name, '/'))
		return (ft_strdup(name));
	return (NULL);
}
