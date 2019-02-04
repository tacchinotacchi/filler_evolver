/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_nmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 09:12:41 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/05 12:43:16 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"

static void	process_zone(t_filler *pc, int i, int y, int x)
{
	if (x + 1 < pc->map_w && pc->nmap[y][x + 1] == i)
		pc->nmap[y][x] = i + 1;
	else if (x - 1 > 0 && pc->nmap[y][x - 1] == i)
		pc->nmap[y][x] = i + 1;
	else if (y + 1 < pc->map_h && pc->nmap[y + 1][x] == i)
		pc->nmap[y][x] = i + 1;
	else if (y - 1 > 0 && pc->nmap[y - 1][x] == i)
		pc->nmap[y][x] = i + 1;
	else if (x + 1 < pc->map_w && y + 1 < pc->map_h &&
			pc->nmap[y + 1][x + 1] == i)
		pc->nmap[y][x] = i + 1;
	else if (x + 1 < pc->map_w && y - 1 > 0 && pc->nmap[y - 1][x + 1] == i)
		pc->nmap[y][x] = i + 1;
	else if (x - 1 > 0 && y + 1 < pc->map_h && pc->nmap[y + 1][x - 1] == i)
		pc->nmap[y][x] = i + 1;
	else if (x - 1 > 0 && y - 1 > 0 && pc->nmap[y - 1][x - 1] == i)
		pc->nmap[y][x] = i + 1;
}

void		process_nmap(t_filler *pc)
{
	int	i;
	int	x;
	int	y;
	int	max;

	i = 1;
	max = ft_max(pc->map_h, pc->map_w);
	while (i < max)
	{
		x = 0;
		y = 0;
		while (y < pc->map_h)
		{
			x = 0;
			while (x < pc->map_w)
			{
				pc->nmap[y][x] == OPEN ? process_zone(pc, i, y, x) : 0;
				x++;
			}
			y++;
		}
		i++;
	}
}
