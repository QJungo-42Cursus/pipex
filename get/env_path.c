#include "../libft/libft.h"

///		Return a list of the env paths
char	**get_env_path(char **envp)
{
	int		i;
	char	*path;
	char	**res;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(envp[i] + 5);
			res = ft_split(path, ':');
			free(path);
			return (res);
		}
		i++;
	}
	return (NULL);
}
// TODO free le res plus tard !!
