/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_next_line_utils.c                               :+:    :+:           */
/*                                                      +:+                   */
/*   By: selcyilm <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/19 13:03:12 by selcyilm       #+#    #+#                */
/*   Updated: 2024/10/19 13:03:13 by selcyilm       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

bool	check_all_list(t_list *node)
{
	t_list	*tmp;
	int		i;

	tmp = node;
	if (node == NULL)
		return (false);
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->str[i] != '\0')
		{
			if (tmp->str[i] == '\n')
				return (true);
			i++;
		}
		tmp = tmp->next;
	}
	return (false);
}

void	free_all(t_list **node, t_list *clean, char *buf, bool flag)
{
	t_list	*tmp;

	while (*node != NULL)
	{
		tmp = (*node)->next;
		if ((*node)->str != NULL)
			free((*node)->str);
		free(*node);
		*node = tmp;
	}
	*node = NULL;
	if (flag)
	{
		if (clean && clean->str && clean->str[0])
			*node = clean;
		else
		{
			free(buf);
			free(clean);
		}
	}
}

int	newline_len(t_list *node)
{
	int		i;
	int		len;
	t_list	*tmp;

	len = 0;
	tmp = node;
	while (tmp != NULL)
	{
		if (tmp->str == NULL)
			return (len);
		i = 0;
		while (tmp->str[i] != '\0')
		{
			len++;
			if (tmp->str[i++] == '\n')
				return (len);
		}
		tmp = tmp->next;
	}
	return (len);
}

t_list	*find_last(t_list *node)
{
	if (node == NULL)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	return (node);
}

void	copy_str(t_list *node, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (node)
	{
		j = 0;
		while (node->str[j])
		{
			if (node->str[j] == '\n')
			{
				str[i++] = '\n';
				str[i] = '\0';
				return ;
			}
			str[i++] = node->str[j++];
		}
		node = node->next;
	}
	str[i] = '\0';
}
