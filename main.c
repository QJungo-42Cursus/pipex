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


int	main(int argc, char **argv)
{
	char	*infile;

	infile = read_all_file("infile");
	if (infile == NULL)
	{
		// TODO
		return (1);
	}
	//ft_printf("file :\n%s", infile);
	argc--;
	argv++;

	//char	*envp[] = {"TEST=\"test\"", "PATH=/bin:/home/qjungo/.cargo/bin:/home/qjungo/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/bin:/usr/bin/site_perl:/usr/bin/vendor_perl:/usr/bin/core_perl", NULL};
	execve(argv[0], argv, NULL);

	perror("Voila ");
	return (0);

	(void)argv;
	if (argc < 4)
	{
		ft_printf("Pas assez d'arguments\n\"infile\" \"cmd1\" \"cmd2\" \"outfile\"");
		return (0);
	}
}
