/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:37:26 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/24 16:18:59 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_strncmp_ign_del(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while ((s1[j] || s2[i]) && i < n)
	{
		while (s1[j] == 127)
		{
			j++;
			k++;
		}
		if (s1[j] != s2[i])
			return ((unsigned char)s1[j] - (unsigned char)s2[i]);
		i++;
		j++;
	}
	if (k % 2 != 0)
		return (-1);
	return (0);
}
