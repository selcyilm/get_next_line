/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/24 15:58:05 by selcyilm      #+#    #+#                 */
/*   Updated: 2023/12/24 19:31:55 by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *str)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	p = malloc(sizeof(char) * (i + 2));
	if (!p)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\n' && str[i])
		p[j++] = str[i++];
	if (str[i] == '\n')
		p[j++] = '\n';
	p[j] = 0;
	return (p);
}

char	*ft_leftover(char *old)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	j = 0;
	if (!old)
		return (NULL);
	while (old[i] != '\n' && old[i])
		i++;
	if (!old[i] || old[i + 1] == 0)
		return (free(old), NULL);
	p = malloc(sizeof(char) * (ft_strlen(old) - i + 1));
	if (!p)
		return (free(old), NULL);
	i++;
	while (old[i])
		p[j++] = old[i++];
	p[j] = 0;
	free(old);
	return (p);
}

char	*ft_read_line(int fd, char *str)
{
	int		byte_read;
	char	*buf;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	byte_read = 1;
	while (!ft_is_newline(str) && byte_read > 0)
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read < 0)
			return (free(buf), NULL);
		buf[byte_read] = '\0';
		str = ft_strjoin(str, buf);
	}
	free(buf);
	if (str && str[0] == 0)
		return (free(str), NULL);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		str = NULL;
		return (0);
	}
	str = ft_read_line(fd, str);
	if (!str)
		return (NULL);
	if (str[0] == 0)
		return (free(str), NULL);
	line = ft_get_line(str);
	str = ft_leftover(str);
	return (line);
}

/*int	main()
{
	int fd;
	char	*str;
	int	i;

	i = 1;
	fd = open("text.txt", O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		printf("Line %d: |%s|\n", i, str);
		i++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	system("leaks a.out");
}*/