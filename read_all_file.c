#include <unistd.h>
#include <fcntl.h>
#include "libft/libft.h"

// TODO libft
static void	all_in_list(int fd, int *final_len, t_list **list)
{
	int		count;
	char	buf[BUFFER_SIZE + 1];

	*final_len = 0;
	while (1)
	{
		count = read(fd, buf, BUFFER_SIZE);
		buf[count] = '\0';
		(*final_len) += count;
		if (count != 0)
			ft_lstadd_back(list, ft_lstnew(ft_strdup(buf)));
		if (count == 0 || count < BUFFER_SIZE)
			break ;
	}
}

static char	*all_in_string(int final_len, t_list *list)
{
	char	*res;
	int		count;
	int		total;

	res = malloc(sizeof(char) * (final_len + 1));
	if (res == NULL)
	{
		// TODO
	}
	count = 0;
	total = 0;
	while (list != NULL)
	{
		count = ft_strlen((char *)list->content);
		ft_strlcpy(&res[total], (const char *)list->content, count + 1);
		total += count;
		list = list->next;
	}
	return (res);
}

char	*read_all_file(const char *path)
{
	int		final_len;
	int		fd;
	t_list	*list;
	char	*res;

	fd = open(path, O_RDONLY);
	// TODO perror
	if (fd == -1)
	{
		return (NULL);
	}
	list = NULL;
	all_in_list(fd, &final_len, &list);
	res = all_in_string(final_len, list);
	ft_lstclear(&list, free);
	return (res);
}
