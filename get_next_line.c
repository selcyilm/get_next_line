/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 11:57:55 by selcyilm      #+#    #+#                 */
/*   Updated: 2023/12/13 12:54:23 by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_check_newline(char *buf, char c)
{
	int	i;

	i = 0;
	if (!buf)
		return (0);
	if (c == '\n')
	{
		while (buf[i])
		{
			if (buf[i] == '\n')
				return (i + 1);
			i++;
		}
		return (0);
	}
	return (gnl_strlen(buf));
}

char	*gnl_buf_to_line(char *line, char *buf)
{
	char	*p;
	int		line_len;
	int		buf_len;

	buf_len = gnl_check_newline(buf, '\n');
	if (buf_len == 0)
		buf_len = gnl_check_newline(buf, 0);
	line_len = gnl_check_newline(line, 0);
	p = malloc(sizeof(char) * (buf_len + line_len + 1));
	if (!p)
		return (free(buf), free(line), NULL);
	gnl_strlcpy(p, line, line_len + 1);
	gnl_fill_string(buf, p, 0, line_len);
	free(line);
	line = gnl_strdup(p);
	free(p);
	return (line);
}

bool	gnl_buffer_update(char *buf)
{
	int		i;
	int		j;
	char	*new_buf;

	j = 0;
	i = gnl_check_newline(buf, '\n') - 1;
	new_buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!new_buf)
		return (false);
	if (buf[i])
	{
		i++;
		while (buf[i])
		{
			new_buf[j] = buf[i];
			i++;
			j++;
		}
		new_buf[j] = 0;
		gnl_strlcpy(buf, new_buf, gnl_strlen(new_buf) + 1);
	}
	else
		buf[0] = 0;
	return (free(new_buf), true);
}

char	*gnl_create_line(char *line, int read_ret, char *buf, int fd)
{
	while (!gnl_check_newline(line, '\n') && read_ret == BUFFER_SIZE)
	{
		read_ret = read(fd, buf, BUFFER_SIZE);
		if (read_ret == 0 && buf[0] == 0)
			return (free(line), NULL);
		if (read_ret == -1)
		{
			buf[0] = 0;
			return (free(line), NULL);
		}
		buf[read_ret] = 0;
		line = gnl_buf_to_line(line, buf);
		if (!line)
			return (NULL);
	}
	if (!gnl_buffer_update(buf))
		return (free(line), NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			read_ret;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	read_ret = BUFFER_SIZE;
	line = gnl_calloc(sizeof(char), 1);
	if (!line)
		return (NULL);
	if (buf[0] != 0)
	{
		line = gnl_buf_to_line(line, buf);
		if (!line)
			return (NULL);
	}
	line = gnl_create_line(line, read_ret, buf, fd);
	return (line);
}

/*
#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd = open("test.txt", O_RDONLY);
	int i = 1;
	char *s = get_next_line(fd);
	while(s)
	{
		printf("Line %d: %s$", i, s);
		i++;
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
	system("leaks a.out");
}*/