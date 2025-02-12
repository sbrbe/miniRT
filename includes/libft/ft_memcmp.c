/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:48:27 by omfelk            #+#    #+#             */
/*   Updated: 2023/10/06 10:14:01 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*text1;
	unsigned char	*text2;
	size_t			i;

	text1 = (unsigned char *)s1;
	text2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (text1[i] != text2[i])
			return (text1[i] - text2[i]);
		else
			i++;
	}
	return (0);
}
