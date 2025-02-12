/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realoc_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:06:00 by omfelk            #+#    #+#             */
/*   Updated: 2024/05/29 11:29:46 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realloc_tab(char **tab, size_t len, bool free_or_non)
{
	size_t	j;
	size_t	k;
	char	**tab_new;

	j = 0;
	while (tab[j])
		j++;
	tab_new = ft_calloc(sizeof(char *), (j + len));
	if (!tab_new)
		return (NULL);
	k = j;
	j = 0;
	while (tab[j] && j <= len + k)
	{
		tab_new[j] = ft_strdups(tab[j]);
		j++;
	}
	j = -1;
	if (free_or_non)
	{
		while (tab[++j])
			free(tab[j]);
		free(tab);
	}
	return (tab_new);
}
