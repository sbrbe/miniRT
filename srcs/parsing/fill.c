/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:10:40 by libelmim          #+#    #+#             */
/*   Updated: 2025/02/05 15:12:29 by libelmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vecto	fill_vect(char *vect)
{
	t_vecto	vector;
	char	**vect_tab;

	vect_tab = ft_split(vect, ',');
	vector.x = ft_atof(vect_tab[0]);
	vector.y = ft_atof(vect_tab[1]);
	vector.z = ft_atof(vect_tab[2]);
	freesplits(vect_tab);
	return (vector);
}

void	init_struct(t_data *rt)
{
	t_scene_data	*data;

	data = ft_calloc(sizeof(t_scene_data), 1);
	if (!data)
	{
		free(rt);
		exit_err(-1);
	}
	data->light_nb = 0;
	data->sp_nb = 0;
	data->pl_nb = 0;
	data->cy_nb = 0;
	data->lights = NULL;
	data->planes = NULL;
	data->cylinders = NULL;
	rt->data = data;
	rt->iter = -1;
}

char	*scene_get_loop(int fd)
{
	char	*line;
	char	*all_lines;

	line = get_next_line(fd);
	all_lines = ft_strdup(line);
	free(line);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		all_lines = ft_join(all_lines, line);
		free(line);
	}
	return (all_lines);
}

int	scene_name_check(char *ext, char *scene)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (scene[i] && scene[i] != '.')
		i++;
	if (scene[i] == '.')
	{
		while (ext[j] && scene[i] == ext[j])
		{
			i++;
			j++;
		}
		if (scene[i] || ext[j])
			return (0);
		else
			return (1);
	}
	return (0);
}
