/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:31:33 by omfelk            #+#    #+#             */
/*   Updated: 2024/07/04 18:29:05 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirts.h"

int	stop(t_data_rt *data_rt)
{
	free(data_rt->cylinder);
	free(data_rt->plane);
	free(data_rt->sphere);
	mlx_destroy_window(data_rt->data_window.mlx,
		data_rt->data_window.window);
	mlx_destroy_display(data_rt->data_window.mlx);
	free(data_rt->data_window.mlx);
	return (exit (1), 0);
}

void	my_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
