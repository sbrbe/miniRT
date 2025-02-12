/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omfelk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:35:54 by omfelk            #+#    #+#             */
/*   Updated: 2023/10/18 17:57:01 by omfelk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	decomp(int n)
{
	int	i;

	i = 0;
	if (n < 0 || n == 0)
	{
		i++;
		n = n * -1;
	}
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static char	*creat_char(int n)
{
	int		i;
	int		nb_c;
	char	*text_nb;

	i = 0;
	nb_c = decomp(n);
	text_nb = malloc(sizeof(char) * (nb_c + 1));
	if (text_nb == NULL)
		return (NULL);
	text_nb[nb_c] = '\0';
	if (n < 0)
	{
		n = n * -1;
		text_nb[0] = '-';
	}
	while (n > 0)
	{
		nb_c--;
		text_nb[nb_c] = (n % 10) + '0';
		n = n / 10;
		i++;
	}
	return (text_nb);
}

char	*ft_itoa(int n)
{
	char	*text_nb;

	if (n == -2147483648)
		return (ft_strdups("-2147483648"));
	if (n == 0 || n == -0)
		return (ft_strdups("0"));
	text_nb = creat_char(n);
	return (text_nb);
}
/*
int	main()
{
	printf("%s", ft_itoa(-0));
	return (0);
}
*/