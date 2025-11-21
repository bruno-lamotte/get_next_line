#ifndef get_next_line_h
# define get_next_line_h
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

typedef struct s_list
{
	char			content[BUFFER_SIZE + 1];
	int				status;
	struct s_list	*next;
}					t_list;

typedef struct s_global
{
	t_list			*liste;
	int				fd_stack;
	struct s_global	*next;
}					t_global;

int					end_of_line(t_list *current_buffer);
void				*ft_lstclear_all(t_global *stack);
t_global			*ft_lstnew(int fd);
t_list				*ft_lstnewnode(int fd);
int					ft_lstsize(t_list *lst);

#endif