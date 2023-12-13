/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 12:02:01 by selcyilm      #+#    #+#                 */
/*   Updated: 2023/12/13 12:02:53 by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>

char	*get_next_line(int fd);
size_t	gnl_strlen(const char *str);
void	*gnl_calloc(size_t count, size_t size);
char	*gnl_strdup(const char *str);
size_t	gnl_strlcpy(char *dest, const char *src, size_t size);
void	gnl_fill_string(char *buf, char *str, int i, int len);
char	*gnl_buf_to_line(char *line, char *buf);
bool	gnl_buffer_update(char *buf);
char	*gnl_create_line(char *line, int read_ret, char *buf, int fd);

#endif