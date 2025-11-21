#include "get_next_line.h"

int	put_in_stack(int fd, t_list *actual_buffer, int isfirst)
{
	t_list	*new_node;

	if (!actual_buffer)
		return (0);
	if (!actual_buffer->status)
		return (1);
	if (isfirst && !end_of_line(actual_buffer))
		return (1);
	new_node = ft_lstnewnode(fd);
	if (!new_node)
		return (0);
	actual_buffer->next = new_node;
	if (end_of_line(new_node))
		return (put_in_stack(fd, new_node, 0));
	return (1);
}

int	put_in_out(t_global *actual_stack, char **out)
{
	int		i;
	int		j;
	t_list	*tmp;

	tmp = actual_stack->liste;
	*out = malloc(ft_lstsize(tmp) * BUFFER_SIZE + 1);
	if (!*out)
		return (0);
	j = 0;
	while (tmp)
	{
		i = 0;
		while (tmp->content[i] && tmp->content[i - 1] != '\n')
		{
			(*out)[j] = tmp->content[i];
			i++;
			j++;
		}
		tmp = tmp->next;
	}
	(*out)[j] = '\0';
	return (1);
}

void	clean_stack(t_global *stack)
{
	t_list	*tmp;
	int		i;
	int		j;

	tmp = stack->liste;
	while (tmp)
	{
		i = 0;
		while (tmp->content[i] && tmp->content[i] != '\n')
			i++;
		if (tmp->content[i] == '\n')
		{
			i++;
			j = 0;
			while (tmp->content[i])
				tmp->content[j++] = tmp->content[i++];
			tmp->content[j] = '\0';
			return ;
		}
		stack->liste = tmp->next;
		free(tmp);
		tmp = stack->liste;
	}
}

char	*get_next_line(int fd)
{
	static t_global	*stack;
	t_global		*current;
	char			*out;

	current = stack;
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	while (current && fd != current->fd_stack)
		current = current->next;
	if (!current)
	{
		current = ft_lstnew(fd);
		if (!current)
			return (NULL);
		current->liste = ft_lstnewnode(fd);
		if (!current->liste)
			return (NULL);
		current->next = stack;
		stack = current;
	}
	if (!put_in_stack(fd, current->liste, 1) || !put_in_out(current, &out))
		return (ft_lstclear_all(stack));
	clean_stack(current);
	return (out);
}
int	main(void)
{
	int fd1;
	//int	fd2;
	char *line;
	int i;

	fd1 = open("test.txt", O_RDONLY);
	//fd2 = open("test1.txt", O_RDONLY);
	//fd = 0;
	i = 50;
	while (i--)
	{
	//	if (i % 3 == 0)
			line = get_next_line(fd1);
	//	else
	//		line = get_next_line(fd2);
		if (line == NULL)
			break ;
		printf("%s", line);
		free(line);
	}
	return (0);
}