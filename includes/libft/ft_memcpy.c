/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:15:50 by omfelk            #+#    #+#             */
/*   Updated: 2023/10/07 11:23:46 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*la_dest;
	const unsigned char	*la_src;
	size_t				i;

	la_dest = dest;
	la_src = src;
	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		la_dest[i] = la_src[i];
		i++;
	}
	return ((void *)dest);
}
