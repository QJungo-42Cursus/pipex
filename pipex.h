#ifndef PIPEX_H
# define PIPEX_H

typedef enum e_position {
	START,
	MIDDLE,
	END,
}	t_position;

typedef struct s_command {
	///		Path to the file binary
	char		*path;
	///		args to be passed (the first is the name)
	char		**argv;
	char		**envp;
	// autre ??
	int			pid;
	t_position	position;	
	t_bool		is_script;

}	t_command;

char	*read_all_file(const int fd);

//			/get
char		**get_env_path(char **envp);
char		*get_cmd_path(char *name, char **env_paths);
t_command	*get_cmds(int argc, char **argv, char **envp);
char		**get_argv(char const *argv);

//			utils.c
void		terminate(char *s);
void		full_free(t_command **cmds, char *err_msg);

#endif /* PIPEX_H */
