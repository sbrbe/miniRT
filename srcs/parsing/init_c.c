/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:22:18 by sbarbe            #+#    #+#             */
/*   Updated: 2024/07/04 14:22:20 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirts.h"

int	c_pos_y(char *temp, t_data_rt *data_rt)
{
	if (ft_len_atof(temp) <= 17 && check_0_9(temp, '.', 1) && temp[0] != '\0')
		data_rt->camera.pos.y = my_atof(temp);
	else
		return (free(temp),
			printf("Error : \033[31mtoo long or invalid for y in C\033[0m\n"));
	data_rt->camera.up_y.x = 0;
	data_rt->camera.up_y.y = 1;
	data_rt->camera.up_y.z = 0;
	free(temp);
	return (0);
}

int	init_csuite(char *str, t_data_rt *data_rt)
{
	int		i;
	char	*temp;

	temp = ft_calloc(sizeof(char), 20);
	ft_strlcpy(temp, str, ft_where(str, ',') + 2);
	if (ft_len_atof(temp) <= 17 && check_0_9(temp, '.', 1) && temp[0] != '\0')
		data_rt->camera.pos.x = my_atof(temp);
	else
		return (free(temp),
			printf("Error : \033[31mtoo long or invalid for x in C\033[0m\n"));
	i = ft_where(str, ',') + 2;
	free(temp);
	temp = ft_calloc(sizeof(char), 20);
	ft_strlcpy(temp, str + i, ft_where(str + i, ',') + 2);
	if (c_pos_y(temp, data_rt))
		return (1);
	i += ft_where(str + i, ',') + 2;
	temp = ft_calloc(sizeof(char), 20);
	ft_strlcpy(temp, str + i, ft_len_atof(str + i) + 2);
	if (ft_len_atof(temp) <= 17 && check_0_9(temp, '.', 1) && temp[0] != '\0')
		data_rt->camera.pos.z = my_atof(temp);
	else
		return (free(temp),
			printf("Error : \033[31mtoo long or invalid for z in C\033[0m\n"));
	return (free(temp), 0);
}

int	init_c(char *str, t_data_rt *data_rt)
{
	int	i;

	i = ft_len_waitspace(str);
	if (count_word(str) > 3)
		return (printf("Error : too many arguments in line C\n"));
	if (count_word(str) != 3)
		return (printf("Error : argument(s) missing in line C\n"));
	if (!check_0_9_point(str + i, ',', 2))
		return (printf("Error : \033[31mInvalid charcat"
				" for x,y,z in C\n\033[0m"));
	if (init_csuite(str + i, data_rt))
		return (1);
	i += ft_len_atof(str + i);
	i += ft_len_waitspace(str + i);
	if (check_neg1_1(str + i, data_rt))
		return (1);
	i += ft_len_atof(str + i);
	i += ft_len_waitspace(str + i);
	if (!check_0_9(str + i, '\0', 0) || (ft_atoi(str + i) < 0
			|| ft_atoi(str + i) > 180) || ft_len_atof(str + i) > 4)
		return (printf("Error : \033[31m FOV in range [0,180] in C\n\033[0m"));
	data_rt->camera.fov = ft_atoi(str + i);
	return (0);
}

size_t	ft_where(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		i++;
	}
	i--;
	return (i);
}

int	check_0_9_point(char *str, char c, int j)
{
	int	i;
	int	a;

	i = -1;
	a = 0;
	while (str[++i] && (str[i] < 7 || str[i] > 32))
	{
		if (str[i] == c)
		{
			if (str[i] == c)
				a++;
			if (a == j + 1 || (str[i] == c && str[i + 1] == c)
				|| ((str[i] == c && (str[i + 1] < '0'
							&& str[i + 1] != '-' && str[i + 1] != '+'))
					|| (str[i] == c && str[i + 1] > '9'
						&& str[i + 1] != '-' && str[i + 1] != '+')))
				return (0);
		}
	}
	if (a != j)
		return (0);
	return (1);
}
