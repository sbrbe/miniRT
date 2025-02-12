/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:15:47 by libelmim          #+#    #+#             */
/*   Updated: 2025/02/05 15:07:11 by libelmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static char	*ft_splat(const char *s, int start, int end)
{
	int			i;
	char		*str;

	i = 0;
	str = malloc(sizeof(char) * (end - start) + 1);
	if (str == NULL)
		return (NULL);
	while (start + i < end)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_count_words(char const *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[0] != c && str[0] != '\0')
	{
		j++;
		i++;
	}
	while (str[i])
	{
		if ((str[i] == c) && (str[i + 1] != c) && (str[i + 1] != '\0'))
			j++;
		i++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	int			i;
	int			j;
	int			start;
	char		**tab;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		if (i != start)
		{
			tab[j] = ft_splat(s, start, i);
			j++;
		}
	}
	tab[j] = NULL;
	return (tab);
}

t_vecto	add_color(t_vecto a, t_vecto b)
{
	t_vecto	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	if (res.x > 255)
		res.x = 255;
	if (res.y > 255)
		res.y = 255;
	if (res.z > 255)
		res.z = 255;
	return (res);
}

int	obj_check(char *str, char first, char sec)
{
	return (str[0] == first && str[1] == sec);
}
