/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 00:34:26 by libelmim          #+#    #+#             */
/*   Updated: 2025/02/05 15:07:11 by libelmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (str1[i] == str2[i] && n > 0)
	{
		n--;
		if (n == 0 || (!str1[i] || !str2[i]))
			break ;
		i++;
	}
	return (str1[i] - str2[i]);
}

char	*ft_strdup(char *s)
{
	int			i;
	char		*dest;

	i = 0;
	if (s == NULL)
		return (NULL);
	dest = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (dest == NULL)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

t_vecto	normalize_vector(t_vecto vector)
{
	double	length;

	length = sqrt((vector.x * vector.x) + (vector.y * vector.y)
			+ (vector.z * vector.z));
	if (!length)
		return ((t_vecto){0, 0, 0});
	vector.x = vector.x / length;
	vector.y = vector.y / length;
	vector.z = vector.z / length;
	return (vector);
}

void	freesplits(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
