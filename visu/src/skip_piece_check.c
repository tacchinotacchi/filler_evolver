/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_piece_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 02:10:33 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/05 02:16:04 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	skip_piece_check(t_visu *v, char **temp)
{
	if (!temp[0] || !temp[1] || !temp[2] ||
		!ft_str_nbr(temp[1]) || !ft_str_nbr(temp[2]))
	{
		ft_splitdel(temp);
		ft_exit(v);
	}
}
