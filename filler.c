/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 09:52:27 by jaelee            #+#    #+#             */
/*   Updated: 2018/12/30 00:16:20 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"

void	sum(t_filler *pc, int map_y, int map_x)
{
	int x;
	int y;
	int tmp_sum;

	y = 0;
	tmp_sum = 0;
	while (y < pc->pc_h)
	{
		x = 0;
		while (x < pc->pc_w)
		{
			if (pc->piece[y][x] == '*' && pc->nmap[map_y + y][map_x + x] != ME)
				tmp_sum += pc->nmap[map_y + y][map_x + x];
			x++;
		}
		y++;
	}
	if (tmp_sum < pc->sum)
	{
		pc->sum = tmp_sum;
		pc->put_y = map_y;
		pc->put_x = map_x;
	}
}

void	check_piece(t_filler *pc, int map_y, int map_x)
{
	int	x;
	int	y;
	int	cnt;

	y = 0;
	cnt = 0;
	while (y < pc->pc_h)
	{
		x = 0;
		while (x < pc->pc_w)
		{
			if (cnt > 1)
				return ;
			if (pc->piece[y][x] == '*' && pc->nmap[map_y + y][map_x + x] == ME)
				cnt++;
			if (pc->piece[y][x] == '*' && pc->nmap[map_y + y][map_x + x] == OP)
				return ;
			x++;
		}
		y++;
	}
	if (cnt == 1)
		sum(pc, map_y, map_x);
}

int		filler(t_filler *pc)
{
	int	x;
	int	y;

	y = 0;
	while (y + pc->pc_h <= pc->map_h)
	{
		x = 0;
		while (x + pc->pc_w <= pc->map_w)
		{
			check_piece(pc, y, x);
			x++;
		}
		y++;
	}
	if (pc->sum != INT_MAX)
		return (1);
	else
		return (0);
}
