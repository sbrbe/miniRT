/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 16:23:32 by libelmim          #+#    #+#             */
/*   Updated: 2025-01-30 16:23:32 by libelmim         ###   ########marvin@4  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

char	*ft_get_line(char *stash);
char	*get_next_line(int fd);
size_t	ft_strlen(char *s);
char	*ft_get_file(int fd, char *stock);
char	*ft_clear_buffer(char *stock);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strchr(char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s);
char	*ft_join(char *stock, char *buffer);

#endif
