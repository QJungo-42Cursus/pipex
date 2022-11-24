#include "../libft/libft.h"
#include <unistd.h>

char	*get_cmd_path(char *name, char **env_paths)
{
	int		i;
	char	*tmp_full_path;

	// TODO gerer un path complet
	if (ft_strncmp(name, "./", 2) == 0) // TODO vu que c'est un script je lui donne pas l'env
		return (ft_strdup(name));

	i = 0;
	while (env_paths[i] != 0)
	{
		tmp_full_path = ft_sprintf("%s/%s", env_paths[i], name);
		if (access(tmp_full_path, F_OK) == 0)
			return (tmp_full_path);
		free(tmp_full_path);
		i++;
	}
	if (access(name, F_OK) == 0)
		return (ft_strdup(name));
	return (NULL);
}
