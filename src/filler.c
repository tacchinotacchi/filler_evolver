/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 09:52:27 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/06 03:22:32 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"

static void	update_pos(t_filler *pc, int tmp_sum, int map_y, int map_x)
{
	if (pc->start_pos == ABOVE)
	{
		if (tmp_sum <= pc->sum)
		{
			pc->sum = tmp_sum;
			pc->put_y = map_y;
			pc->put_x = map_x;
		}
	}
	else
	{
		if (tmp_sum < pc->sum)
		{
			pc->sum = tmp_sum;
			pc->put_y = map_y;
			pc->put_x = map_x;
		}
	}
}

static void	sum(t_filler *pc, int map_y, int map_x)
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
			if (pc->piece[y][x] == '*' &&
					pc->nmap[map_y + y][map_x + x] != pc->nbr_me)
				tmp_sum += pc->nmap[map_y + y][map_x + x];
			x++;
		}
		y++;
	}
	update_pos(pc, tmp_sum, map_y, map_x);
}

static void	check_piece(t_filler *pc, int map_y, int map_x)
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
			if (pc->piece[y][x] == '*' &&
					pc->nmap[map_y + y][map_x + x] == pc->nbr_me)
				cnt++;
			if (pc->piece[y][x] == '*' &&
					pc->nmap[map_y + y][map_x + x] == pc->nbr_op)
				return ;
			x++;
		}
		y++;
	}
	if (cnt == 1)
		sum(pc, map_y, map_x);
}

int			filler(t_filler *pc)
{
	int	x;
	int	y;

	pc->sum = INT_MAX;
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
		return (FT_SUCCESS);
	else
		return (FT_FAIL);
}
