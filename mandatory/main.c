/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:33:27 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/28 13:02:53 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>			// open()   (+flags)
#include "../libft/libft.h"	// ft_strncmp(), TRUE, FALSE
#include "../pipex.h"		// t_command, t_position
#include <unistd.h>			// exit(), fork(), pipe(),
							// STDOUT_FILENO, STDIN_FILENO,
							// execve(), close(), dup2()
#include <stdio.h>			// perror()
#include <sys/wait.h>		// waitpid ?
#include <errno.h>			// errno

int	piper(t_command cmd, int infile_fd, int outfile_fd, int pipers[2])
{
	int		pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid != 0)
		return (pid);
	if (cmd.position == START && infile_fd != -1)
		dup2(infile_fd, STDIN_FILENO);
	if (cmd.position == START && infile_fd == -1)
		dup2(pipers[1], STDIN_FILENO);
	if (cmd.position != END)
		dup2(pipers[1], STDOUT_FILENO);
	if (cmd.position != START)
		dup2(pipers[0], STDIN_FILENO);
	if (cmd.position == END)
		dup2(outfile_fd, STDOUT_FILENO);
	close(pipers[0]);
	close(pipers[1]);
	if (execve(cmd.path, cmd.argv, cmd.envp) == -1)
		terminate("execve oups: ");
	return (-1);
}

void	pipex(t_command *cmds, int infile_fd, int outfile_fd)
{
	int		pipers[2];
	int		pid1;
	int		pid2;

	if (pipe(pipers) == -1)
		full_free(&cmds, "Un probleme a eu lieu lors de l'ouverture du pipe",
			infile_fd, outfile_fd);
	pid1 = piper(cmds[0], infile_fd, outfile_fd, pipers);
	if (pid1 == -1)
		full_free(&cmds, "N'a pas fork... / Ne s'est pas execve",
			infile_fd, outfile_fd);
	pid2 = piper(cmds[1], infile_fd, outfile_fd, pipers);
	if (pid2 == -1)
		full_free(&cmds, "N'a pas fork... / Ne s'est pas execve",
			infile_fd, outfile_fd);
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

	argc--;
	argv++;
	if (argc < 4)
		terminate("Pas assez d'arguments\n\"infile\" \"cmd1\" \"cmd2\" \"outfile\"");
	infile_fd = open(argv[0], O_RDONLY);
	if (infile_fd == -1)
		perror("Fichier d'entree: ");
	outfile_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (outfile_fd == -1)
		terminate("Probleme lors de l'ouverture du fichier de sortie");
	cmds = get_cmds(argc - 1, argv + 1, envp);
	pipex(cmds, infile_fd, outfile_fd);
	full_free(&cmds, NULL, outfile_fd, infile_fd);
}
