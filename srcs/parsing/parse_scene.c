/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <libelmim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:19:42 by libelmim          #+#    #+#             */
/*   Updated: 2025/01/30 18:32:52 by libelmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	init_parse_scene(t_data *rt, char **argv)
{
	char	*all_lines;
	char	**tab;

	all_lines = NULL;
	if (!scene_name_check(".rt", argv[1]))
		return (0);
	rt->fd = open(argv[1], O_RDONLY);
	if (rt->fd == -1)
		exit_err(1);
	all_lines = scene_get_loop(rt->fd);
	tab = ft_split(all_lines, '\n');
	free(all_lines);
	init_struct(rt);
	if (!parse_scene(rt, tab))
	{
		free(rt->data);
		free(rt);
		freesplits(tab);
		exit_err(0);
	}
	freesplits(tab);
	return (1);
}

int	parse_scene(t_data *rt, char **tab)
{
	if (!mandatory_components(rt->data, tab))
	{
		printf("Error: (mandatory components)\n");
		return (0);
	}
	if (!in_range_values(rt->data, tab))
	{
		printf("Error: (range values)\n");
		return (0);
	}
	return (1);
}

int	in_range_values(t_scene_data *data, char **tab)
{
	t_amb	amb;
	t_cam	cam;
	t_light	*lights;

	lights = ft_calloc(sizeof(t_light), data->light_nb);
	if (amb_in_range_values(&amb, tab) && cam_in_range_values(&cam, tab)
		&& light_check_save_all(lights, tab) && obj_nb_check(data, tab))
	{
		data->amb = amb;
		data->cam = cam;
		data->lights = lights;
		return (1);
	}
	free(lights);
	return (0);
}

int	mandatory_params_01(char *line, char *elem)
{
	int		i;
	t_elem	*elements;

	i = 0;
	elements = elems();
	while (elements[i].name)
	{
		if (!ft_strncmp(elem, elements[i].name, -1))
		{
			if (ft_count_words(line, ' ') == elements[i].count
				&& parsedumbshit(line, elem))
			{
				free(elements);
				return (1);
			}
			if (!(ft_count_words(line, ' ') == elements[i].count))
				printf("Wrong number of parameters for %s\n", elem);
			break ;
		}
		i++;
	}
	free(elements);
	return (0);
}

int	mandatory_components(t_scene_data *data, char **tab)
{
	int	i;
	int	cam;
	int	obj;
	int	amb;

	i = 0;
	cam = 0;
	amb = 0;
	while (tab[i])
	{
		if (tab[i][0] == 'A' && mandatory_params_01(tab[i], "A"))
			amb++;
		if (tab[i][0] == 'C' && mandatory_params_01(tab[i], "C"))
			cam++;
		if (tab[i][0] == 'L' && mandatory_params_01(tab[i], "L"))
			data->light_nb++;
		if (!obj_allcheck(data, tab[i]))
			return (multiple_single_msg(cam, amb));
		i++;
	}
	obj = data->cy_nb + data->pl_nb + data->sp_nb;
	if ((cam == 1) && data->light_nb && obj && (amb == 1))
		return (1);
	multiple_single_msg(cam, amb);
	return (0);
}
