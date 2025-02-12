/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 08:50:01 by omfelk            #+#    #+#             */
/*   Updated: 2023/10/06 11:24:12 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*text;
	unsigned char		caract;
	size_t				i;

	text = (const unsigned char *)s;
	caract = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (text[i] == caract)
			return ((void *)s + i);
		else
			i++;
	}
	return (NULL);
}
