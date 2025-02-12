/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_range_vals2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <libelmim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:14:26 by libelmim          #+#    #+#             */
/*   Updated: 2025/01/30 18:27:45 by libelmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	sphere_check_save_all(t_sp *spheres, char **tab)
{
	int		i;
	int		spherenb;
	char	**sphere_tab;

	i = 0;
	spherenb = 0;
	while (tab[i])
	{
		if (tab[i][0] == 's' && tab[i][1] == 'p')
		{
			sphere_tab = ft_split(tab[i], ' ');
			if (is_vector(sphere_tab[1])
				&& is_in_range(sphere_tab[2], 0, DBL_MAX)
				&& is_vector_is_in_range(sphere_tab[3], 0, 255))
			{
				spheres[spherenb].coord = fill_vect(sphere_tab[1]);
				spheres[spherenb].diameter = ft_atof(sphere_tab[2]);
				spheres[spherenb].rgb_colors = fill_vect(sphere_tab[3]);
				spherenb++;
			}
			freesplits(sphere_tab);
		}
		i++;
	}
	return (spherenb);
}

int	plane_check_save_all(t_pl *planes, char **tab)
{
	int			i;
	int			planenb;
	char		**plane_tab;

	i = 0;
	planenb = 0;
	while (tab[i])
	{
		if (tab[i][0] == 'p' && tab[i][1] == 'l')
		{
			plane_tab = ft_split(tab[i], ' ');
			if (is_vector(plane_tab[1]) && is_in_range(plane_tab[2], -1.0, 1.0)
				&& is_vector_is_in_range(plane_tab[3], 0, 255))
			{
				planes[planenb].coord = fill_vect(plane_tab[1]);
				planes[planenb].norm_vect = fill_vect(plane_tab[2]);
				planes[planenb].rgb_colors = fill_vect(plane_tab[3]);
				planenb++;
			}
			freesplits(plane_tab);
		}
		i++;
	}
	return (planenb);
}

int	cyl_check_save_all(t_cy *cyls, char **tab)
{
	int			i;
	int			cylnb;
	char		**cyl_tab;

	i = 0;
	cylnb = 0;
	while (tab[i])
	{
		if (tab[i][0] == 'c' && tab[i][1] == 'y')
		{
			cyl_tab = ft_split(tab[i], ' ');
			if (is_vector(cyl_tab[1])
				&& is_vector_is_in_range(cyl_tab[2], -1, 1)
				&& is_in_range(cyl_tab[3], 0, DBL_MAX)
				&& is_in_range(cyl_tab[4], 0, DBL_MAX)
				&& is_vector_is_in_range(cyl_tab[5], 0, 255))
			{
				fill_cyls(cyl_tab, cylnb, cyls);
				cylnb++;
			}
			freesplits(cyl_tab);
		}
		i++;
	}
	return (cylnb);
}

int	obj_nb_check(t_scene_data *data, char **tab)
{
	t_sp	*spheres;
	t_pl	*planes;
	t_cy	*cylinders;

	spheres = NULL;
	planes = NULL;
	cylinders = NULL;
	spheres = ft_calloc(sizeof(t_sp), data->sp_nb);
	planes = ft_calloc(sizeof(t_pl), data->pl_nb);
	cylinders = ft_calloc(sizeof(t_cy), data->cy_nb);
	if (spheres)
		data->sp_nb = sphere_check_save_all(spheres, tab);
	if (planes)
		data->pl_nb = plane_check_save_all(planes, tab);
	if (cylinders)
		data->cy_nb = cyl_check_save_all(cylinders, tab);
	if (data->sp_nb + data->pl_nb + data->cy_nb < 1)
	{
		printf("Need at least one object!\n");
		return (free(spheres), free(planes), free(cylinders), 0);
	}
	obj_save_data(data, spheres, planes, cylinders);
	return (1);
}

void	obj_save_data(t_scene_data *data, t_sp *spheres,
			t_pl *planes, t_cy *cylinders)
{
	if (data->sp_nb)
		data->spheres = spheres;
	else
		free(spheres);
	if (data->pl_nb)
		data->planes = planes;
	else
		free(planes);
	if (data->cy_nb)
		data->cylinders = cylinders;
	else
		free(cylinders);
}
