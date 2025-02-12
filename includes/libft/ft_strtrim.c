/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:10:31 by omfelk            #+#    #+#             */
/*   Updated: 2023/10/18 17:48:22 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	chr_set_deb(char const *text, char const *set, size_t size_set)
{
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	while (j <= size_set && text[i] != '\0')
	{
		if (text[i] == set[j])
		{
			j = 0;
			i++;
		}
		else
			j++;
	}
	return (i);
}

static size_t	chr_set_fin(char const *text, char const *set, size_t size_set)
{
	size_t			i;
	size_t			j;

	i = ft_strlens(text) - 1;
	j = 0;
	while (j <= size_set && i > 0)
	{
		if (text[i] == set[j])
		{
			j = 0;
			i--;
		}
		else
			j++;
	}
	return (ft_strlens(text) - 1 - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_text;
	size_t	size_s1;
	size_t	size_set;
	size_t	nb_multiple;
	size_t	start;

	size_s1 = ft_strlens(s1);
	size_set = ft_strlens(set);
	nb_multiple = chr_set_deb(s1, set, size_set);
	start = nb_multiple;
	nb_multiple = nb_multiple + chr_set_fin(&s1[nb_multiple], set, size_set);
	new_text = ft_substr(s1, start, (size_s1 - nb_multiple));
	if (new_text == NULL)
		return (NULL);
	return (new_text);
}
/*
int	main(void)
{
	printf("%s", ft_strtrim("xxxz  test with x and z and x .  zx  xx z", "z x"));
	return (0);
}*/
