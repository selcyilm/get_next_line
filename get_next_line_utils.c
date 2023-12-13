/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 11:58:03 by selcyilm      #+#    #+#                 */
/*   Updated: 2023/12/13 12:29:25 by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*gnl_calloc(size_t count, size_t size)
{
	char	*p;
	size_t	i;

	p = malloc(count * size);
	if (!p)
		return (NULL);
	if (size != 0 || count != 0)
	{
		i = 0;
		while (i < (size * count))
			((char *)p)[i++] = 0;
	}
	return ((void *)p);
}

char	*gnl_strdup(const char *str)
{
	char	*p;
	size_t	i;

	i = gnl_strlen(str);
	p = malloc((i + 1) * sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	while (str[i])
	{
		p[i] = str[i];
		i++;
	}
	p[i] = 0;
	return (p);
}

size_t	gnl_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = gnl_strlen(src);
	if (size == 0)
		return (len);
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (len);
}

void	gnl_fill_string(char *buf, char *str, int i, int len)
{
	while (buf[i] && buf[i] != '\n')
	{
		str[i + len] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
	{
		str[len + i] = '\n';
		str[len + i + 1] = '\0';
	}
	else
		str[len + i] = '\0';
}
