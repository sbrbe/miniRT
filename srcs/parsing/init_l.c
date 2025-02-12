/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_l.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 08:34:37 by sbarbe            #+#    #+#             */
/*   Updated: 2024/07/10 06:26:36 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirts.h"

int	l_pos_y(char *temp, t_data_rt *data_rt)
{
	if (ft_len_atof(temp) <= 17 && check_0_9(temp, '.', 1) && temp[0] != '\0')
		data_rt->light.pos.pos.y = my_atof(temp);
	else
		return (free(temp),
			printf("Error : \033[31mtoo long or invalid for y in L\033[0m\n"));
	free(temp);
	data_rt->light.pos.radius = 5;
	return (0);
}

int	init_lsuite(char *str, t_data_rt *data_rt)
{
	int		i;
	char	*temp;

	temp = ft_calloc(sizeof(char), 20);
	ft_strlcpy(temp, str, ft_where(str, ',') + 2);
	if (ft_len_atof(temp) <= 17 && check_0_9(temp, '.', 1) && temp[0] != '\0')
		data_rt->light.pos.pos.x = my_atof(temp);
	else
		return (free(temp),
			printf("Error : \033[31mtoo long or invalid for x in L\033[0m\n"));
	i = ft_where(str, ',') + 2;
	free(temp);
	temp = ft_calloc(sizeof(char), 20);
	ft_strlcpy(temp, str + i, ft_where(str + i, ',') + 2);
	if (l_pos_y(temp, data_rt))
		return (1);
	i += ft_where(str + i, ',') + 2;
	temp = ft_calloc(sizeof(char), 20);
	ft_strlcpy(temp, str + i, ft_len_atof(str + i) + 2);
	if (ft_len_atof(temp) <= 17 && check_0_9(temp, '.', 1) && temp[0] != '\0')
		data_rt->light.pos.pos.z = my_atof(temp);
	else
		return (free(temp),
			printf("Error : \033[31mtoo long or invalid for z in L\033[0m\n"));
	return (free(temp), 0);
}

int	check_0_255_l(char *str, t_data_rt *data_rt)
{
	int		i;
	int		j;
	char	**av;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == ',')
			j++;
		if ((str[i] == ',' && str[i + 1] == ',') || j > 2)
			return (1);
		if (!check_0_9((str + i), ',', 2))
			return (printf("Error: \033[31mR,G,B\033[0m in L\n"));
	}
	av = ft_split(str, ',');
	i = -1;
	while (av[++i])
		if (ft_atoi(av[i]) > 255 || ft_atoi(av[i]) < 0 || (!av[i + 1] && i < 2))
			return (my_free_tab(av),
				printf("Error : \033[31mR,G,B colors\033[0m [0-255] in L\n"));
	data_rt->light.pos.color.red = ft_atoi(av[0]);
	data_rt->light.pos.color.green = ft_atoi(av[1]);
	data_rt->light.pos.color.blue = ft_atoi(av[2]);
	return (my_free_tab(av), 0);
}

int	init_l(char *str, t_data_rt *data_rt)
{
	int	i;

	i = ft_len_waitspace(str);
	if (count_word(str) > 3)
		return (printf("Error : too many arguments in line L\n"));
	else if (count_word(str) != 3)
		return (printf("Error : argumetn(s) missing in line L\n"));
	if (!check_0_9_point(str + i, ',', 2))
		return (printf("Error : \033[31mInvalid for x,y,z in L\n\033[0m"));
	if (init_lsuite(str + i, data_rt))
		return (1);
	i += ft_len_atof(str + i);
	i += ft_len_waitspace(str + i);
	if (my_atof(str + i) >= 0.0 && my_atof(str + i) <= 1.0
		&& ft_len_atof(str + i) <= 17 && check_0_9(str + i, '.', 1))
		data_rt->light.light = my_atof(str + i);
	else
		return (printf("Error : \033[31mlight\033[0m [0.0,1.0] in L\n"));
	i += ft_len_atof(str + i);
	i += ft_len_waitspace(str + i);
	if (check_0_255_l(str + i, data_rt))
		return (1);
	data_rt->sphere[data_rt->nb_sphere] = data_rt->light.pos;
	data_rt->sphere[data_rt->nb_sphere].radius = 1;
	return (0);
}
