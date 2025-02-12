/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 08:11:07 by omfelk            #+#    #+#             */
/*   Updated: 2024/04/01 15:51:47 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdups(const char *s)
{
	char	*new_text;
	size_t	i;

	i = ft_strlens(s) + 1;
	new_text = (char *) malloc((sizeof(char) * i));
	if (new_text == NULL)
		return (NULL);
	ft_strlcpy(new_text, s, i);
	return (new_text);
}

char	*ft_strldup(const char *s, size_t len_finish)
{
	char	*new_text;
	size_t	i;

	i = ft_strlens(s) + 1;
	i = i - len_finish;
	new_text = (char *) malloc((sizeof(char) * i));
	if (new_text == NULL)
		return (NULL);
	ft_strlcpy(new_text, s, i);
	return (new_text);
}
