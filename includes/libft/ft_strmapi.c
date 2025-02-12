/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 10:54:36 by omfelk            #+#    #+#             */
/*   Updated: 2023/10/14 11:14:53 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_text;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
		i++;
	new_text = malloc(sizeof(char) * (i + 1));
	if (new_text == NULL)
		return (NULL);
	new_text[i] = '\0';
	i = 0;
	while (s[i] != '\0')
	{
		new_text[i] = s[i];
		i++;
	}
	while (new_text[j] != '\0')
	{
		new_text[j] = (*f)(j, new_text[j]);
		j++;
	}
	return (new_text);
}
