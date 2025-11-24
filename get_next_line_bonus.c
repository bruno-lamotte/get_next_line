/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 07:25:48 by blamotte          #+#    #+#             */
/*   Updated: 2025/11/24 00:54:06 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	put_in_stack(int fd, t_list *actual_buffer, int isfirst)
{
	t_list	*new_node;

	if (!actual_buffer)
		return (0);
	if (!actual_buffer->status)
		return (1);
	if (isfirst && end_of_line(actual_buffer))
		return (1);
	new_node = ft_lstnewnode(fd);
	if (!new_node)
		return (0);
	actual_buffer->next = new_node;
	if (end_of_line(new_node))
		return (1);
	return (put_in_stack(fd, new_node, 0));
}

int	put_in_out(t_global *actual_stack, char **out)
{
	int		i;
	int		j;
	t_list	*tmp;

	tmp = actual_stack->liste;
	*out = malloc(ft_lstsize(tmp) + 1);
	if (!*out)
		return (0);
	j = 0;
	while (tmp)
	{
		i = 0;
		while (tmp->content[i])
		{
			(*out)[j++] = tmp->content[i];
			if (tmp->content[i++] == '\n')
				break ;
		}
		if (tmp->content[i] == '\n')
			break ;
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
	stack->liste = NULL;
}

char	*get_next_line(int fd)
{
	static t_global	*stack;
	t_global		*current;
	char			*out;

	current = stack;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	while (current && fd != current->fd_stack)
		current = current->next;
	if (!current)
	{
		current = ft_lstnew(fd);
		if (!current)
			return (NULL);
		current->liste = ft_lstnewnode(fd);
		if (!current->liste || !current->liste->status)
			return (ft_clear(stack), free(current->liste), free(current), NULL);
		current->next = stack;
		stack = current;
	}
	if (!put_in_stack(fd, current->liste, 1) || !put_in_out(current, &out))
		return (ft_clear(stack), stack = NULL, NULL);
	if (!out || !out[0])
		return (free(out), NULL);
	clean_stack(current);
	return (out);
}
/*
int	main(int ac, char *av[])
{
	int	fd = open(av[1], O_RDONLY);
	char *line;

	(void) ac;
	line = get_next_line(fd);
	while (line) {
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}
*/