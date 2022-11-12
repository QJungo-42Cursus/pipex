#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_command {
	///		Path to the file binary
	char	*path;
	///		args to be passed (the first is the name)
	char	**argv;
	//char	**envp;
	// autre ??
	int		pid;
	int		parent_pid;
}	t_command;

char	*read_all_file(const char *path);

//		/get
char	**get_env_path(char **envp);
char	*get_cmd_path(char *name, char **env_paths);

#endif /* PIPEX_H */
