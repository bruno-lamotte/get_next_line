/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 07:26:11 by blamotte          #+#    #+#             */
/*   Updated: 2025/11/24 00:54:40 by blamotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*ft_lstnewnode(int fd)
{
	t_list	*new_content;
	int		nb_bytes;

	new_content = malloc(sizeof(t_list));
	if (!new_content)
		return (NULL);
	new_content->status = 1;
	nb_bytes = read(fd, new_content->content, BUFFER_SIZE);
	if (nb_bytes < 0)
		return (free(new_content), NULL);
	if (nb_bytes == 0)
		new_content->status = 0;
	new_content->content[nb_bytes] = '\0';
	new_content->next = NULL;
	return (new_content);
}

t_global	*ft_lstnew(int fd)
{
	t_global	*new_liste;

	new_liste = malloc(sizeof(t_global));
	if (!new_liste)
		return (NULL);
	new_liste->fd_stack = fd;
	new_liste->next = NULL;
	new_liste->liste = NULL;
	return (new_liste);
}

int	end_of_line(t_list *current_buffer)
{
	int	i;

	if (!current_buffer || !current_buffer->status)
		return (1);
	i = 0;
	while (current_buffer->content[i])
	{
		if (current_buffer->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	*ft_clear(t_global *stack)
{
	t_global	*tmp_global;
	t_list		*tmp_liste;
	t_list		*next_liste;

	while (stack)
	{
		tmp_global = stack->next;
		tmp_liste = stack->liste;
		while (tmp_liste)
		{
			next_liste = tmp_liste->next;
			free(tmp_liste);
			tmp_liste = next_liste;
		}
		free(stack);
		stack = tmp_global;
	}
	return (NULL);
}

int ft_lstsize(t_list *lst)
{
    int total = 0;
    int i;

    while (lst)
    {
        i = 0;
        while (lst->content[i])
        {
            total++;
            if (lst->content[i++] == '\n')
                return total;
        }
        lst = lst->next;
    }
    return total;
}

