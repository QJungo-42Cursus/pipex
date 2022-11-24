#include <fcntl.h>			// open()   (+flags)

#include "../libft/libft.h"	// ft_strncmp(), TRUE, FALSE

#include "../pipex.h"		// t_command, t_position

#include <unistd.h>			// exit(), fork(), pipe(),
							// STDOUT_FILENO, STDIN_FILENO,
							// execve(), close(), dup2()

#include <stdio.h>			// perror()

//#include <sys/wait.h>		// waitpid ?


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

int	piper(t_command cmd, int infile_fd, int outfile_fd, int pipers[2])
{
	int pid;

	pid = fork();
	if (pid == -1)
	{
		// TODO
	}
	if (pid != 0)
		return (pid);
	if (cmd.position == START)
		dup2(infile_fd, STDIN_FILENO);
	if (cmd.position != END)
		dup2(pipers[1], STDOUT_FILENO); // remplace le standard output par le fd to write
	if (cmd.position != START)
		dup2(pipers[0], STDIN_FILENO); // remplace le standard input, par ce qu'on veut lui faire lire
	if (cmd.position == END)
		dup2(outfile_fd, STDOUT_FILENO); // remplace le standard out, par le fichier out
	close(pipers[0]);
	close(pipers[1]);
	execve(cmd.path, cmd.argv, cmd.envp);

	// TODO exit exit error ?
	//exit(EXIT_SUCCESS);
	return (pid);
	// si pid == 0, ca sert a r de le retourner ??
}

void	pipex(t_command *cmds, int infile_fd, int outfile_fd /*, char **envp */)
{
	int		i;
	int		pipers[2]; // (read, write)

	if (pipe(pipers) == -1)
	{
		perror(": ");
		// free TODO
		exit (1);
	}
	i = 0;
	while (cmds[i - 1].position != END)
	{
		int pid1 = piper(cmds[i], infile_fd, outfile_fd, pipers);
		(void)pid1;
		i++;
	}
	close(pipers[0]);
	close(pipers[1]);
	//waitpid(pid1, NULL, 0);
	//waitpid(pid2, NULL, 0);
}


int	main(int argc, char **argv, char **envp)
{
	t_command	*cmds;
	int			infile_fd;
	int			outfile_fd;

	argc--;
	argv++;
	if (argc < 4)
		terminate("Pas assez d'arguments\n\"infile\" \"cmd1\" \"cmd2\" \"outfile\"");
	if (is_here_doc(argv[0]))
	{
		// TODO
		here_doc_mode(argc, argv, envp);
		return (0);
	}
	infile_fd = open(argv[0], O_RDONLY);
	if (infile_fd == -1)
		terminate("Probleme lors de l'ouverture du fichier d'entree");
	outfile_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (outfile_fd == -1)
		terminate("Probleme lors de l'ouverture du fichier de sortie");
	cmds = get_cmds(argc - 1, argv + 1, envp);
	pipex(cmds, infile_fd, outfile_fd);
	wait(0);
	// TODO free...
	return (0);
}
