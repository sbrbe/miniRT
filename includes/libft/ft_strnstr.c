/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:36:35 by omfelk            #+#    #+#             */
/*   Updated: 2023/10/11 12:06:19 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		if (little[j] == big[i] && little[j] != '\0')
			j++;
		else if (j != 0 && little[j] != big[i])
		{
			i = i - j;
			j = 0;
		}
		if (little[j] == '\0')
		{
			i = i - j + 1;
			return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
