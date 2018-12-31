/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 18:28:38 by jaelee            #+#    #+#             */
/*   Updated: 2018/12/30 00:22:56 by jaelee           ###   ########.fr       */
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
			else if (pc->map[y][x] == 'O' || pc->map[y][x] == 'o')
				pc->nmap[y][x] = ME;
			else if (pc->map[y][x] == 'X' || pc->map[y][x] == 'x')
				pc->nmap[y][x] = OP;
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
		if (!(pc->nmap[index] = (int*)ft_memalloc(sizeof(int) * pc->map_w)))
			error(pc);
		index++;
	}
	init_nmap(pc);
	y = 0;
	while (y < pc->map_h)
	{
		x = 0;
		while (x < pc->map_w)
		{
			pc->nmap[y][x] == OP ? init_nmap2(pc, y, x) : 0;
			x++;
		}
		y++;
	}
}
