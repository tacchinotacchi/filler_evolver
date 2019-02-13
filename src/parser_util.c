/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 06:03:06 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/06 03:59:54 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		verify_split(char **split)
{
	int		cnt;

	cnt = 0;
	if (!split)
		return (FT_FAIL);
	while (split[cnt] != NULL)
		cnt++;
	if (cnt != 3)
		return (FT_FAIL);
	if (ft_strcmp("Plateau", split[0]) && ft_strcmp("Piece", split[0]))
		return (FT_FAIL);
	return (FT_SUCCESS);
}

int		get_start_pos(t_filler *pc)
{
	int	x;
	int	y;
	int	y_me;
	int	y_op;

	y_me = -1;
	y_op = -1;
	y = 0;
	while (y < pc->map_h)
	{
		x = 0;
		while (x < pc->map_w)
		{
			if (pc->map[y][x] == pc->me)
				y_me = y;
			if (pc->map[y][x] == pc->op)
				y_op = y;
			x++;
		}
		y++;
	}
	if (y_me < 0 || y_op < 0)
		return (FT_FAIL);
	pc->start_pos = (y_me < y_op) ? ABOVE : BELOW;
	return (FT_SUCCESS);
}
