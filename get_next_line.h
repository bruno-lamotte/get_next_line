#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef FD_MAX
#  define FD_MAX 10
# endif

typedef struct s_global
{
	char			content[BUFFER_SIZE];
	ssize_t			siz;
	struct s_global	*next;
}					t_global;

char				*get_next_line(int fd);
void				ft_clear(t_global **stash);
int					is_eol(t_global *list);
int					line_size(t_global *lst);

#endif
