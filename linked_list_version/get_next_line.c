/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_next_line.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: selcyilm <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/19 13:03:03 by selcyilm       #+#    #+#                */
/*   Updated: 2024/10/19 13:03:05 by selcyilm       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include "get_next_line.h"

void	leftover(t_list **node)
{
	t_list	*last;
	t_list	*clean;
	int		i;
	int		j;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (free_all(node, NULL, NULL, false));
	clean = malloc(sizeof(t_list));
	if (clean == NULL)
		return (free_all(node, NULL, NULL, false), free(buf));
	last = find_last(*node);
	if (!last)
		return (free(buf), free(clean), free_all(node, NULL, NULL, false));
	i = 0;
	j = 0;
	while (last->str[i] != '\n' && last->str[i])
		i++;
	while (last->str[i] && last->str[++i])
		buf[j++] = last->str[i];
	buf[j] = '\0';
	clean->str = buf;
	clean->next = NULL;
	free_all(node, clean, buf, true);
}

char	*get_line_x(t_list *node)
{
	int		len;
	char	*str;

	if (!node)
		return (NULL);
	len = newline_len(node);
	str = malloc((len + 1));
	if (str == NULL)
		return (NULL);
	copy_str(node, str);
	return (str);
}

void	append_to_last(t_list **node, char *buf)
{
	t_list	*new;
	t_list	*last;

	last = find_last(*node);
	new = malloc(sizeof(t_list));
	if (new == NULL)
	{
		free_all(node, NULL, NULL, false);
		return (free(buf));
	}
	if (last == NULL)
		*node = new;
	else
		last->next = new;
	new->str = buf;
	new->next = NULL;
}

void	create_nodes(int fd, t_list **node)
{
	int		byte_read;
	char	*buf;

	buf = NULL;
	byte_read = 0;
	while (!check_all_list(*node))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return (free_all(node, NULL, NULL, false));
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read < 0)
			return (free(buf), free_all(node, NULL, NULL, false));
		if (byte_read == 0)
			return (free(buf));
		buf[byte_read] = '\0';
		append_to_last(node, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;

	line = NULL;
	if (fd < 0 || fd > 4096 || BUFFER_SIZE < 1)
		return (free_all(&list, NULL, NULL, false), NULL);
	create_nodes(fd, &list);
	if (list == NULL)
		return (NULL);
	line = get_line_x(list);
	if (line == NULL)
		return (free_all(&list, NULL, NULL, false), NULL);
	leftover(&list);
	return (line);
}
