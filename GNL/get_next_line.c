/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:40:06 by libelmim          #+#    #+#             */
/*   Updated: 2025/01/30 18:42:08 by libelmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_clear_buffer(char *stock)
{
	size_t				i;
	size_t				j;
	char				*new_stock;

	i = 0;
	j = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	if (stock[i] == '\n')
		i++;
	new_stock = ft_calloc(ft_strlen(stock) - i + 1, sizeof(char));
	while (stock[i])
	{
		new_stock[j] = stock[i];
		i++;
		j++;
	}
	free(stock);
	return (new_stock);
}

char	*ft_get_line(char *stock)
{
	int			i;
	char		*line;

	i = 0;
	if (stock == NULL)
		return (NULL);
	while (stock[i] && stock[i] != '\n')
		i++;
	line = ft_calloc(sizeof(char), (i + 2));
	i = 0;
	while (stock[i] && stock[i] != '\n')
	{
		line[i] = stock[i];
		i++;
	}
	if (stock[i])
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_join(char *stock, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(stock, buffer);
	free(stock);
	return (temp);
}

char	*ft_get_file(int fd, char *stock)
{
	int				bytesread;
	char			*buffer;

	bytesread = 1;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(buffer));
	if (!stock)
		stock = ft_calloc(sizeof(char), 1);
	if (!stock)
		return (NULL);
	while (bytesread > 0 && !(ft_strchr(stock, '\n')))
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if ((bytesread == 0 && ft_strlen(stock) < 1) || bytesread == -1)
		{
			free(buffer);
			free(stock);
			return (NULL);
		}
		buffer[bytesread] = '\0';
		stock = ft_join(stock, buffer);
	}
	free(buffer);
	return (stock);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*stock;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	stock = ft_get_file(fd, stock);
	if (!stock)
		return (NULL);
	line = ft_get_line(stock);
	stock = ft_clear_buffer(stock);
	if (stock == NULL)
	{
		free(stock);
		return (line);
	}
	return (line);
}
