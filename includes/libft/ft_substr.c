/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:36:46 by omfelk            #+#    #+#             */
/*   Updated: 2023/10/10 19:31:00 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_text;
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	j = 0;
	if (ft_strlens(s) <= (size_t)start)
		return ((char *)ft_strdups(""));
	size = ft_strlens(&s[start]);
	if (size < len)
		len = size;
	new_text = (char *)malloc(sizeof(char) * len + 1);
	if (new_text == NULL || !s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (i >= start && j < len)
			new_text[j++] = s[i];
		i++;
	}
	new_text[j] = '\0';
	return (new_text);
}
/*
int	main()
{
	printf("%s", ft_substr("le grand text", 3, 5));
	return (0);
}*/