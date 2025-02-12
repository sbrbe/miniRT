/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 10:40:26 by sbarbe            #+#    #+#             */
/*   Updated: 2024/07/10 10:40:28 by sbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirts.h"

int	cy_pos_y(char *temp, t_data_rt *data_rt, int j)
{
	if (ft_len_atof(temp) <= 17 && check_0_9(temp, '.', 1) && temp[0] != '\0')
		data_rt->cylinder[j].pos.y = my_atof(temp);
	else
		return (free(temp),
			printf("Error : \033[31mtoo long "
				"or invalid for y in cy.%d\033[0m\n",
				j + 1));
	free(temp);
	return (0);
}

int	init_cy_suite(char *str, t_data_rt *data_rt, int j)
{
	int		i;
	char	*temp;

	temp = ft_calloc(sizeof(char), 20);
	ft_strlcpy(temp, str, ft_where(str, ',') + 2);
	if (ft_len_atof(temp) <= 17 && check_0_9(temp, '.', 1) && temp[0] != '\0')
		data_rt->cylinder[j].pos.x = my_atof(temp);
	else
		return (free(temp),
			printf("Error: \033[31mlong or invld x in cy.%d\033[0m\n", j + 1));
	i = ft_where(str, ',') + 2;
	free(temp);
	temp = ft_calloc(sizeof(char), 20);
	ft_strlcpy(temp, str + i, ft_where(str + i, ',') + 2);
	if (cy_pos_y(temp, data_rt, j))
		return (1);
	i += ft_where(str + i, ',') + 2;
	temp = ft_calloc(sizeof(char), 20);
	ft_strlcpy(temp, str + i, ft_len_atof(str + i) + 2);
	if (ft_len_atof(temp) <= 17 && check_0_9(temp, '.', 1) && temp[0] != '\0')
		data_rt->cylinder[j].pos.z = my_atof(temp);
	else
		return (free(temp),
			printf("Error : \033[31mlong or invld z in cy.%d\033[0m\n", j + 1));
	return (free(temp), 0);
}

int	init_cy_i_suite(char *str, t_data_rt *data_rt, int i)
{
	int	j;

	j = ft_len_atof(str);
	j += ft_len_waitspace(str + j);
	if (my_atof(str + j) >= 0.0 && ft_len_atof(str + j) <= 17
		&& check_0_9(str + j, '.', 1))
		data_rt->cylinder[i].diameter = my_atof(str + j);
	else
		return (printf("Error: \033[31mcylinder "
				"diameter\033[0m too long or '-' or invld in cy.%d\n", i + 1));
	j += ft_len_atof(str + j);
	j += ft_len_waitspace(str + j);
	if (my_atof(str + j) >= 0.0 && ft_len_atof(str + j) <= 17
		&& check_0_9(str + j, '.', 1))
		data_rt->cylinder[i].height = my_atof(str + j);
	else
		return (printf("Error: \033[31mcylinder "
				"height\033[0m too long or '-' or invld in cy.%d\n", i + 1));
	j += ft_len_atof(str + j);
	j += ft_len_waitspace(str + j);
	if (check_0_255_cy(str + j, data_rt, i))
		return (1);
	return (0);
}

int	init_cy_i(char *str, t_data_rt *data_rt, int i)
{
	int	j;

	j = ft_len_waitspace(str);
	if (count_word(str) > 5)
		return (printf("Error : too many arguments in line cy.%d\n", i + 1));
	else if (count_word(str) != 5)
		return (printf("Error : argument(s) missing in line cy.%d\n", i + 1));
	if (!check_0_9_point(str + j, ',', 2))
		return (printf("Error : \033[31mInvalid"
				" charcat for x,y,z in pl\n\033[0m"));
	if (init_cy_suite(str + j, data_rt, i))
		return (1);
	j += ft_len_atof(str + j);
	j += ft_len_waitspace(str + j);
	if (check_neg1_1_cy(str + j, data_rt, i))
		return (1);
	if (init_cy_i_suite(str + j, data_rt, i))
		return (1);
	return (0);
}

int	init_cy(char *str, t_data_rt *data_rt)
{
	int	i;

	i = 0;
	while (data_rt->cylinder[i].diameter)
		i++;
	if (init_cy_i(str, data_rt, i))
		return (1);
	return (0);
}
