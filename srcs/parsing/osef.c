/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   osef.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 00:44:43 by libelmim          #+#    #+#             */
/*   Updated: 2025/02/05 15:07:11 by libelmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	obj_allcheck(t_scene_data *data, char *line)
{
	if (obj_check(line, 's', 'p'))
	{
		data->sp_nb++;
		return (mandatory_params_01(line, "sp"));
	}
	else if (obj_check(line, 'p', 'l'))
	{
		data->pl_nb++;
		return (mandatory_params_01(line, "pl"));
	}
	else if (obj_check(line, 'c', 'y'))
	{
		data->cy_nb++;
		return (mandatory_params_01(line, "cy"));
	}
	return (1);
}

t_elem	*elems(void)
{
	t_elem	*elements;

	elements = ft_calloc(sizeof(t_elem), 7);
	if (!elements)
		return (NULL);
	elements[0].name = "A";
	elements[0].count = 3;
	elements[1].name = "C";
	elements[1].count = 4;
	elements[2].name = "L";
	elements[2].count = 4;
	elements[3].name = "sp";
	elements[3].count = 4;
	elements[4].name = "pl";
	elements[4].count = 4;
	elements[5].name = "cy";
	elements[5].count = 6;
	elements[6].name = NULL;
	elements[6].count = 0;
	return (elements);
}

double	vect_length(t_vecto v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

void	fill_cyls(char **cyl_tab, int cylnb, t_cy *cyls)
{
	cyls[cylnb].coord = fill_vect(cyl_tab[1]);
	cyls[cylnb].norm_vect = fill_vect(cyl_tab[2]);
	cyls[cylnb].diameter = ft_atof(cyl_tab[3]);
	cyls[cylnb].height = ft_atof(cyl_tab[4]);
	cyls[cylnb].rgb_colors = fill_vect(cyl_tab[5]);
}
