/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_nmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 07:40:17 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/11 17:44:38 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"

static void		init_nmap2(t_filler *pc, int y, int x)
{
	if (x + 1 < pc->map_w && pc->nmap[y][x + 1] == OPEN)
		pc->nmap[y][x + 1] = 1;
	if (x - 1 > 0 && pc->nmap[y][x - 1] == OPEN)
		pc->nmap[y][x - 1] = 1;
	if (y + 1 < pc->map_h && pc->nmap[y + 1][x] == OPEN)
		pc->nmap[y + 1][x] = 1;
	if (y - 1 > 0 && pc->nmap[y - 1][x] == OPEN)
		pc->nmap[y - 1][x] = 1;
	if (x + 1 < pc->map_w && y + 1 < pc->map_h
			&& pc->nmap[y + 1][x + 1] == OPEN)
		pc->nmap[y + 1][x + 1] = 1;
	if (x + 1 < pc->map_w && y - 1 > 0 && pc->nmap[y - 1][x + 1] == OPEN)
		pc->nmap[y - 1][x + 1] = 1;
	if (x - 1 > 0 && y + 1 < pc->map_h && pc->nmap[y + 1][x - 1] == OPEN)
		pc->nmap[y + 1][x - 1] = 1;
	if (x - 1 > 0 && y - 1 > 0 && pc->nmap[y - 1][x - 1] == OPEN)
		pc->nmap[y - 1][x - 1] = 1;
}

static void		init_nmap(t_filler *pc)
{
	int	x;
	int	y;

	y = 0;
	while (y < pc->map_h)
	{
		x = 0;
		while (x < pc->map_w)
		{
			if (pc->map[y][x] == '.')
				pc->nmap[y][x] = OPEN;
			else if (pc->map[y][x] == pc->me || pc->map[y][x] == pc->me + 32)
				pc->nmap[y][x] = pc->nbr_me;
			else if (pc->map[y][x] == pc->op || pc->map[y][x] == pc->op + 32)
				pc->nmap[y][x] = pc->nbr_op;
			else
				error(pc);
			x++;
		}
		y++;
	}
}

void			create_nmap(t_filler *pc)
{
	int	index;
	int	x;
	int	y;

	if (!(pc->nmap = (int**)ft_memalloc(sizeof(int*) * pc->map_h)))
		error(pc);
	index = 0;
	while (index < pc->map_h)
	{
		pc->index_nmap = index;
		if (!(pc->nmap[index] = (int*)ft_memalloc(sizeof(int) * pc->map_w)))
			error(pc);
		index++;
	}
	init_nmap(pc);
	y = -1;
	while (++y < pc->map_h)
	{
		x = -1;
		while (++x < pc->map_w)
			pc->nmap[y][x] == pc->nbr_op ? init_nmap2(pc, y, x) : 0;
	}
}
