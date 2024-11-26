/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_next_line.h                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: selcyilm <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/19 13:03:21 by selcyilm       #+#    #+#                */
/*   Updated: 2024/10/19 13:03:22 by selcyilm       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
void	create_nodes(int fd, t_list **node);
void	append_to_last(t_list **node, char *buf);
t_list	*find_last(t_list *node);
int		newline_len(t_list *node);
char	*get_line_x(t_list *node);
void	free_all(t_list **node, t_list *clean, char *buf, bool flag);
void	leftover(t_list **node);
bool	check_all_list(t_list *node);
void	copy_str(t_list *node, char *str);

#endif
