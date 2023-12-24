/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: selcyilm <selcyilm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/24 15:58:29 by selcyilm      #+#    #+#                 */
/*   Updated: 2023/12/24 19:00:41 by selcyilm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int		ft_strlen(char *str);
char	*get_next_line(int fd);
char	*ft_leftover(char *old);
char	*ft_get_line(char *str);
char	*ft_strjoin(char *s1, char *s2);
int		ft_is_newline(char	*str);
char	*ft_read_line(int fd, char *str);
char	*ft_strdup(char *str);

#endif