#include "get_next_line.h"


int	put_in_stack(int fd, t_list *actual_buffer)
{
	t_list	*new_node;
	t_list	*last_node;
	int		eol_status;

	if (!actual_buffer)
		return (0);
	if (!actual_buffer->status)
		return (1);
	new_node = ft_lstnewnode(fd);
	if (!new_node)
		return (0);
	last_node = actual_buffer;
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = new_node;
	eol_status = end_of_line(new_node);
	if (eol_status)
		return (put_in_stack(fd, new_node));
	return (1);
}

int	put_in_out(t_global *actual_stack, char **out)
{
	int		i;
	int		j;
	t_list	*tmp;

	tmp = actual_stack->liste;
	*out = malloc(ft_lstsize(actual_stack->liste) * BUFFER_SIZE + 1);
	if (!*out)
		return (0);
	j = 0;
	while (tmp)
	{
		i = 0;
		while (tmp->content[i])
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
	static t_global *stack;
	t_global *current;
	char *out;

	current = stack;
	if (fd < 0 || fd >= 1024|| BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	while (current && fd != current->fd_stack)
		current = current->next;
	if (!current)
	{
		current = ft_lstnew(fd);
		if (!current)
			return (NULL);
		current->liste = ft_lstnewnode(fd);
		current->next = stack;
		stack = current;
	}
	if (!put_in_stack(fd, current->liste) || !put_in_out(current, &out))
		return (ft_lstclear_all(stack));
	clean_stack(stack);
	return (out);
}
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		printf("%s\n\n\n", line);
		free(line);
	}
	return (0);
}