/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:06:38 by omfelk            #+#    #+#             */
/*   Updated: 2024/01/28 12:21:48 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *pointer, size_t memorySize)
{
	void	*new_ptr;

	new_ptr = ft_calloc(sizeof(pointer), memorySize + 1);
	if (!new_ptr)
		return (NULL);
	ft_strlcpy(new_ptr, pointer, (memorySize + ft_strlens(pointer)));
	free(pointer);
	return (new_ptr);
}
