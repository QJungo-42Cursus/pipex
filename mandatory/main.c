/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:33:27 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/28 15:49:56 by qjungo           ###   ########.fr       */
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

void	post_execve(int saved_stdout, t_command cmd)
{
	if (execve(cmd.path, cmd.argv, cmd.envp) == -1)
	{
		dup2(saved_stdout, 1);
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(cmd.argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
		close(saved_stdout);
	}
}

int	piper(t_command cmd, int infile_fd, int outfile_fd, int pipers[2])
{
	int		pid;
	int		saved_stdout;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid != 0)
		return (pid);
	saved_stdout = dup(1);
	if (cmd.position == START && infile_fd != -1)
		dup2(infile_fd, STDIN_FILENO);
	if (cmd.position != END)
		dup2(pipers[1], STDOUT_FILENO);
	if (cmd.position != START)
		dup2(pipers[0], STDIN_FILENO);
	if (cmd.position == END)
		dup2(outfile_fd, STDOUT_FILENO);
	close(pipers[0]);
	close(pipers[1]);
	post_execve(saved_stdout, cmd);
	return (-1);
}

static void	wait_set(int infile_fd, int *return_val, int pid[2])
{
	int		status;

	if (infile_fd != -1)
	{
		waitpid(pid[0], &status, 0);
		if (WIFEXITED(status))
			*return_val = WEXITSTATUS(status);
	}
	waitpid(pid[1], &status, 0);
	if (WIFEXITED(status))
		*return_val = WEXITSTATUS(status);
}

void	pipex(t_command *cmds, int infile_fd, int outfile_fd, int *return_val)
{
	int		pipers[2];
	int		pid[2];

	if (pipe(pipers) == -1)
		full_free(&cmds, "Failed pipe opening", infile_fd, outfile_fd);
	if (infile_fd != -1)
	{
		pid[0] = piper(cmds[0], infile_fd, outfile_fd, pipers);
		if (pid[0] == -1)
			full_free(&cmds, "Fork failed", infile_fd, outfile_fd);
	}
	pid[1] = piper(cmds[1], infile_fd, outfile_fd, pipers);
	if (pid[1] == -1)
		full_free(&cmds, "Fork failed", infile_fd, outfile_fd);
	close(pipers[0]);
	close(pipers[1]);
	wait_set(infile_fd, return_val, pid);
}

int	main(int argc, char **argv, char **envp)
{
	t_command	*cmds;
	int			infile_fd;
	int			outfile_fd;
	int			return_val;

	argc--;
	argv++;
	if (argc < 4)
		terminate("Pas assez d'arguments\n\"infile\" \"cmd1\" \"cmd2\" \"outfile\"");
	infile_fd = open(argv[0], O_RDONLY);
	if (infile_fd == -1)
		perror("pipex: input");
	outfile_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (outfile_fd == -1)
		terminate("Probleme lors de l'ouverture du fichier de sortie");
	cmds = get_cmds(argc - 1, argv + 1, envp);
	return_val = 0;
	pipex(cmds, infile_fd, outfile_fd, &return_val);
	full_free(&cmds, NULL, outfile_fd, infile_fd);
	return (return_val);
}
