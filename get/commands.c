#include "../libft/libft.h"
#include "../pipex.h"

/*
 * libft ??
static void	add_end(char **list, char *string)
{
	int	word_c;

	word_c = 0;
	while (list[word_c] != NULL)
		word_c++;
	list[word_c] = string;
	list[word_c + 1] = NULL;
}
*/

void	pre_free(t_command **cmds, char *msg)
{
	int		i;

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
	terminate(msg);
}

static void	all_cmds(t_command **cmds, char ***env_paths, char **envp, int argc)
{
	*cmds = malloc(sizeof(t_command) * (argc - 1));
	if (*cmds == NULL)
		terminate("Probleme lors d'allocation de memoires pour les commandes");
	*env_paths = get_env_path(envp);
	if (*env_paths == NULL)
	{
		free(*cmds);
		terminate("Probleme lors de la recuperation du PATH");
	}
}

t_command	*get_cmds(int argc, char **argv, char **envp)
{
	t_command	*cmds;
	char		**env_paths;
	int			i;

	all_cmds(&cmds, &env_paths, envp, argc);
	i = 0;
	while (i < argc - 1)
	{
		cmds[i].position = END;
		if (i == 1)
			cmds[i - 1].position = START;
		if (i > 1)
			cmds[i - 1].position = MIDDLE;
		cmds[i].path = NULL;
		cmds[i].argv = NULL;
		cmds[i].argv = get_argv(argv[i]);
		if (cmds[i].argv == NULL)
			pre_free(&cmds, "argv pas trouve...");
		/*
		if (cmds[i].argv[1] != NULL && ft_strchr(cmds[i].argv[1], '/'))
		{
			cmds[i].path = get_cmd_path(cmds[i].argv[1], env_paths);
			ft_printf("nn: %s\n", cmds[i].argv[1]);
		}
		else
		{
		*/
			cmds[i].path = get_cmd_path(cmds[i].argv[0], env_paths);
			ft_printf("nn: %s\n", cmds[i].argv[0]);
		//}

		cmds[i].is_script = FALSE;
		cmds[i].envp = envp;

		/*
		//if (cmds[i].path != NULL && ft_strncmp(cmds[i].path, "./", 2) == 0)		// TODO vu que c'est un script je lui donne pas l'env
		if (cmds[i].path != NULL && ft_strchr(cmds[i].path, '/'))
		{
			cmds[i].is_script = TRUE;
			cmds[i].envp = NULL;
		}
		*/
		i++;
	}
	return (cmds);
}
// TODO le program est sence continuer quand meme... -> check si le path 
// est null
//if (cmds[i].path == NULL)
//	pre_free(&cmds);
