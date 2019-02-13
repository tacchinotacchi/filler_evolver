/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_digit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 04:44:09 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/05 01:37:47 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_str_nbr(const char *str)
{
	ssize_t index;

	index = 0;
	while (str[index] != '\0')
	{
		if (ft_isdigit(str[index] == 0))
			return (0);
		index++;
	}
	return (1);
}
