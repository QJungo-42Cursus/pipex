#include "../libft/libft.h"
#include "../pipex.h"

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
	/*
	if (*env_paths == NULL)
	{
		free(*cmds);
		terminate("Probleme lors de la recuperation du PATH");
	}
	*/
}

#include <stdio.h>
void	log_cmd(t_command *cmds, int cmd_l)
{
	int	c = 0;
	while (c < cmd_l)
	{
		printf("\n");
		if (cmds[c].position == START)
			printf("POSITION: START \n");
		else if (cmds[c].position == MIDDLE)
			printf("POSITION: MIDDLE \n");
		else if (cmds[c].position == END)
			printf("POSITION: END\n");
		else
			printf("POSITION: ????\n");
		//printf("IS_SCRIPT: %d \n", cmds[c].is_script);
		printf("PATH: %s \n", cmds[c].path);
		printf("ARGV: \n");
		int i = 0;
		while (cmds[c].argv[i] != NULL)
		{
			printf("\t%d) |%s| \n", i, cmds[c].argv[i]);
			i++;
		}
		printf("\n");
		c++;
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
		cmds[i].path = get_cmd_path(cmds[i].argv[0], env_paths);
		cmds[i].is_script = FALSE;
		cmds[i].envp = envp;
		i++;
	}
	//log_cmd(cmds, argc - 1); // TODO
	return (cmds);
}
