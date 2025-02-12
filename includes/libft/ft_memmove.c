/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 08:31:31 by omfelk            #+#    #+#             */
/*   Updated: 2023/10/11 15:17:31 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*the_dest;
	char	*the_src;
	size_t	i;

	the_dest = (char *)dest;
	the_src = (char *)src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	if (dest < src)
	{
		while (i < n)
		{
			the_dest[i] = the_src[i];
			i++;
		}
	}
	else
	{
		while (n-- > 0)
			the_dest[n] = the_src[n];
	}
	return (the_dest);
}
