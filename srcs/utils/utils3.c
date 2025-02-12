/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libelmim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:34:09 by libelmim          #+#    #+#             */
/*   Updated: 2025/02/05 15:07:11 by libelmim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static const char	*handle_sign(const char *str, int *sign)
{
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	return (str);
}

static double	parse_integer_part(const char **str)
{
	double	result;

	result = 0.0;
	while (ft_isdigit(**str))
	{
		result = result * 10 + (**str - '0');
		(*str)++;
	}
	return (result);
}

static double	parse_decimal_part(const char **str)
{
	double	result;
	double	decimal_place;

	result = 0.0;
	decimal_place = 0.1;
	while (ft_isdigit(**str))
	{
		result += (**str - '0') * decimal_place;
		decimal_place *= 0.1;
		(*str)++;
	}
	return (result);
}

double	ft_atof(const char *str)
{
	double	result;
	int		sign;
	int		has_decimal;

	result = 0.0;
	sign = 1;
	has_decimal = 0;
	while (ft_isspace(*str))
		str++;
	str = handle_sign(str, &sign);
	result = parse_integer_part(&str);
	if (*str == '.')
	{
		has_decimal = 1;
		str++;
	}
	if (has_decimal)
		result += parse_decimal_part(&str);
	return (result * sign);
}

void	init_inter(t_inter *inter)
{
	inter->hit = false;
	inter->dist = DBL_MAX;
	inter->color = (t_vecto){0, 0, 0};
}
