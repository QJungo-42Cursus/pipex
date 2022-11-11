#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "pipex.h"

typedef struct s_command {
	char	**argv;
	char	**envp;

	// autre ??
	int		pid;
	int		parent_pid;
}	t_command;

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


int	main(int argc, char **argv, char **envp)
{
	char		*infile;
	char		*outfile;
	t_bool		here_doc;
	t_command	*cmds;

	int j = 0;
	while (envp[j])
	{
		if (!ft_strncmp(envp[j], "PATH", 4))
			ft_printf("%d - %s\n", j, envp[j]);
		// TODO get tout les paths
		// et test avec la fonction "access F_OK" si le file existe en essayand tout les paths..


		j++;
	}
	argc--;
	argv++;
	if (argc < 4)
	{
		ft_printf("Pas assez d'arguments\n\"infile\" \"cmd1\" \"cmd2\" \"outfile\"");
		return (0);
	}
	// TODO
	// if argv[0] == here_doc -> bonus
	// here_doc_mode(int argc, char **argv);
	(void)here_doc;
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
	while (i < argc - 2)
	{
		cmds[i].argv = ft_split(argv[i], ' ');
		//ft_printf("%s\n", argv[i]);
		i++;
	}
	

	execve(argv[0], argv, NULL);

	perror("Voila ");
	return (0);

}
