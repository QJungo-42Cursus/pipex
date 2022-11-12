#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "libft/libft.h"
#include "pipex.h"

///		< in_file cmd1 | cmd2 > out_file
///		1. check if the file exists
///		2. read all the file -> save it in memory
///		3. execve... -> 
///					Ouvrir 1 fork par cmd et piper entre eux

///		Bon a savoir : execve, dans le 2eme argument, les flags, 
///			il ne prend pas le 1er en compte !!
///			-> (c'est une convention de le nommer comme le fichier qu'on execute,
///				selon man 2 execve)
///			!!! ca agit differement si c'est un script, on doit indiquer avec
///				quel programme l'interpreter

///		exec v -> v pour vector (la facon dont on passe les arguments)
///		exec e -> e pour env (pour dire qu'on peut passe des variables d'env
///
///		Le PID (process ID) reste le meme lors d'un appel de execve

t_bool	is_here_doc(char *first_arg)
{
	if (ft_strncmp(first_arg, "here_doc", 8) == 0)
		return (TRUE);
	return (FALSE);
}

void	here_doc_mode(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	// TODO
}

int	main(int argc, char **argv, char **envp)
{
	char		*infile;
	char		*outfile;
	t_command	*cmds;

	argc--;
	argv++;
	if (argc < 4)
	{
		ft_printf("Pas assez d'arguments\n\"infile\" \"cmd1\" \"cmd2\" \"outfile\"");
		return (0);
	}
	if (is_here_doc(argv[0]))
	{
		// TODO
		here_doc_mode(argc, argv, envp);
		return (0); // Inutile ??
	}
	infile = read_all_file(argv[0]);
	if (infile == NULL)
	{
		// TODO
		perror("");
		return (1);
	}
	outfile = read_all_file(argv[argc - 1]); 
	if (outfile == NULL)
	{
		// TODO
		perror("");
		return (1);
	}
	cmds = malloc(sizeof(t_command) * (argc - 2));
	int		i;
	i = 0;
	argv++;
	argc--;

	char **env_paths = get_env_path(envp);
	while (i < argc - 1)
	{
		cmds[i].argv = ft_split(argv[i], ' ');
		cmds[i].path = get_cmd_path(cmds[i].argv[0], env_paths);
		i++;
	}
	int pid = fork();
	int *val = malloc(sizeof(int));
	*val = 0;
	if (pid == 0)
	{
		// TODO
		// child
		// execve(cmds[0].path, cmds[0].argv, envp);
		*val = 2;
		printf("child val : %i\n", *val);
	}
	else
	{
		// TODO
		// parent
		// wait(NULL);
		//*val = 0;
		waitpid(pid, NULL, 0);
		printf("parent val %i\n", *val);
	}
	printf("fini");
	//perror("Voila ");
	return (0);

}
