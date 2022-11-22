#include <fcntl.h>			// open()   (+flags)

#include "../libft/libft.h"	// ft_strncmp(), TRUE, FALSE

#include "../pipex.h"		// t_command, t_position

#include <unistd.h>			// exit(), fork(), pipe(),
							// STDOUT_FILENO, STDIN_FILENO,
							// execve(), close(), dup2()

#include <stdio.h>			// perror()

#include <sys/wait.h>		// waitpid ?

int	piper(t_command cmd, int infile_fd, int outfile_fd, int pipers[2])
{
	int pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid != 0)		// Si c'est un pid, c'est juste l'info du pid de l'enfant a l'intention du parent
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
	if (execve(cmd.path, cmd.argv, cmd.envp) == -1)
	{
		perror("execve");
		//TODO test !!!
		exit(1);
	}
	return (-1);
}

void	pipex(t_command *cmds, int infile_fd, int outfile_fd /*, char **envp */)
{
	int		i;
	int		pipers[2]; // (read, write)

	(void)i;
	if (pipe(pipers) == -1)
		full_free(&cmds, "Un probleme a eu lieu lors de l'ouverture du pipe");
	i = 0;
	int pid1 = piper(cmds[0], infile_fd, outfile_fd, pipers);
	if (pid1 == -1)
		full_free(&cmds, "N'a pas fork... / Ne s'est pas execve");
	int pid2 = piper(cmds[1], infile_fd, outfile_fd, pipers);
	if (pid2 == -1)
		full_free(&cmds, "N'a pas fork... / Ne s'est pas execve");
	close(pipers[0]);
	close(pipers[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_command	*cmds;
	int			infile_fd;
	int			outfile_fd;

	/*
	int i = 0;
	while (argv[i] != NULL)
	{
		printf("%s \n", argv[i]);
		i++;

	}
	return 0;
	*/
	argc--;
	argv++;
	if (argc < 4)
		terminate("Pas assez d'arguments\n\"infile\" \"cmd1\" \"cmd2\" \"outfile\"");
	infile_fd = open(argv[0], O_RDONLY);
	if (infile_fd == -1)
		terminate("Probleme lors de l'ouverture du fichier d'entree");
	outfile_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (outfile_fd == -1)
		terminate("Probleme lors de l'ouverture du fichier de sortie");
	cmds = get_cmds(argc - 1, argv + 1, envp);
	pipex(cmds, infile_fd, outfile_fd);
	full_free(&cmds, NULL);
}
