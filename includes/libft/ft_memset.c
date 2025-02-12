/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 07:46:39 by omfelk            #+#    #+#             */
/*   Updated: 2023/10/06 08:15:06 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*caract;
	size_t			i;

	caract = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		caract[i] = c;
		i++;
	}
	s = caract;
	return (s);
}
