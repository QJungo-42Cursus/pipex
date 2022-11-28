/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:36:04 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/28 13:01:07 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef enum e_position {
	START,
	MIDDLE,
	END,
}	t_position;

	///		Path to the file binary
	///		args to be passed (the first is the name)
	// autre ??
typedef struct s_command {
	char		*path;
	char		**argv;
	char		**envp;
	t_position	position;	
}	t_command;
//int			pid;

char		*read_all_file(const int fd);

//			/get
char		**get_env_path(char **envp);
char		*get_cmd_path(char *name, char **env_paths);
t_command	*get_cmds(int argc, char **argv, char **envp);
char		**get_argv(char const *argv);

//			utils.c
void		terminate(char *s);
void		full_free(t_command **cmds, char *err_msg, int fd1, int fd2);

#endif /* PIPEX_H */
