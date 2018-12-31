/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 20:46:27 by jaelee            #+#    #+#             */
/*   Updated: 2018/12/27 11:00:58 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"

int	ft_atoi_ptr(char **str)
{
	int i;
	int nb;
	int neg;

	i = 0;
	nb = 0;
	neg = 1;
	while (**str == ' ' || **str == '\n' || **str == '\t' || **str == '\r' ||
			**str == '\v' || **str == '\f' || **str < '0' || **str > '9')
		(*str)++;
	if (**str == '-')
		neg = -1;
	if (**str == '-' || **str == '+')
		(*str)++;
	while (**str >= '0' && **str <= '9')
	{
		nb *= 10;
		nb += **str - '0';
		(*str)++;
	}
	nb = nb * neg;
	return (nb);
}
