/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 07:47:42 by omfelk            #+#    #+#             */
/*   Updated: 2023/12/30 14:29:54 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nb_word(char const *text, char caract_sep)
{
	size_t	i;
	size_t	sep;

	i = 0;
	sep = 0;
	while (text[i] != '\0')
	{
		if (text[i] != caract_sep)
		{
			sep++;
			while (text[i] != caract_sep && text[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (sep);
}

static char	*mal_cpy(char const *text_org, size_t *start_pos, char c)
{
	char	*text;
	size_t	i;
	size_t	j;

	j = 0;
	i = *start_pos;
	while (text_org[i] != '\0')
	{
		if (text_org[i] != c)
		{
			*start_pos = i;
			while (text_org[i] != '\0' && text_org[i++] != c)
			{
				j++;
			}
			text = malloc(sizeof(char) * (j + 1));
			if (text == NULL)
				return (NULL);
			ft_strlcpy(text, &text_org[*start_pos], j + 1);
			*start_pos = i;
			return (text);
		}
		i++;
	}
	return (NULL);
}

static void	ft_free(char **new_text, size_t nb_free)
{
	size_t	i;

	i = 0;
	while (i < nb_free)
	{
		free(new_text[i]);
		i++;
	}
	free(new_text);
}

char	**ft_split(char const *s, char c)
{
	char	**new_text;
	size_t	nb_alloc;
	size_t	i;
	size_t	pos;

	if (!s)
		return (NULL);
	nb_alloc = nb_word(s, c);
	new_text = ft_calloc(sizeof(char *), (nb_alloc + 1));
	if (new_text == NULL)
		return (NULL);
	new_text[nb_alloc] = NULL;
	i = 0;
	pos = 0;
	while (i < nb_alloc)
	{
		new_text[i] = mal_cpy(s, &pos, c);
		if (new_text[i] == NULL)
		{
			ft_free(new_text, i);
			return (NULL);
		}
		i++;
	}
	return (new_text);
}
