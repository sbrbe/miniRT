/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:33:01 by omfelk            #+#    #+#             */
/*   Updated: 2023/10/16 09:51:16 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	size_dst;
	size_t	size_src;
	size_t	i;
	size_t	j;

	size_dst = ft_strlens(dst);
	size_src = ft_strlens(src);
	i = size_dst;
	j = 0;
	if (size == 0 || size <= size_dst)
		return (size_src + size);
	while (src[j] != '\0' && j + 1 <= (size - size_dst - 1))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (size_dst + size_src);
}
