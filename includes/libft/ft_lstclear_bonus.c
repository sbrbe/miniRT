/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 08:35:07 by omfelk            #+#    #+#             */
/*   Updated: 2023/10/18 08:48:45 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*lst_temp;

	if (!del || !lst || !*lst)
		return ;
	while (lst && *lst)
	{
		lst_temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = lst_temp;
	}
}
