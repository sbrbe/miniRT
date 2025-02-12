/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:50:48 by sbarbe            #+#    #+#             */
/*   Updated: 2025/01/30 18:42:59 by libelmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirts.h"

char	*ft_sep(char *line)
{
	int		i;
	char	*str;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	str = (char *)ft_calloc(sizeof(char), (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		str[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		str[i] = line[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin_calloc(char *temp, char *line)
{
	int		i;
	int		j;
	char	*str;

	if (!temp)
	{
		temp = (char *)ft_calloc(1, sizeof(char));
		temp[0] = '\0';
	}
	if (!temp || !line)
		return (NULL);
	str = ft_calloc(sizeof(char), ((ft_strlens(temp) + ft_strlens(line)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (temp)
		while (temp[++i] != '\0')
			str[i] = temp[i];
	while (line[j] != '\0')
		str[i++] = line[j++];
	str[ft_strlens(temp) + ft_strlens(line)] = '\0';
	free(temp);
	return (str);
}

char	*reste(char *temp)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (!temp[i])
	{
		free(temp);
		return (NULL);
	}
	str = ft_calloc(sizeof(char), (ft_strlens(temp) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (temp[i])
		str[j++] = temp[i++];
	free(temp);
	str[j] = '\0';
	return (str);
}

char	*ajouteca(int fd, char *temp)
{
	char	*line;
	int		rd;

	line = ft_calloc(sizeof(char), 4 + 1);
	if (!line)
		return (NULL);
	rd = 1;
	while (!ft_strchrs(line, '\n') && rd != 0)
	{
		rd = read(fd, line, 4);
		if (rd == -1)
		{
			free(line);
			return (NULL);
		}
		if (rd == 0)
			break ;
		line[rd] = '\0';
		temp = ft_strjoin_calloc(temp, line);
	}
	free(line);
	return (temp);
}

char	*get_next_lines(int fd)
{
	char		*theline;
	static char	*temp;

	if (fd < 0 || 4 <= 0)
		return (NULL);
	temp = ajouteca(fd, temp);
	if (!temp)
		return (NULL);
	theline = ft_sep(temp);
	temp = reste(temp);
	return (theline);
}
