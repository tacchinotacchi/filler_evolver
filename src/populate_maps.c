/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_maps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 16:03:28 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/01 22:22:28 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int     populate_maps(t_filler *pc)
{
    int y;

    y = 0;
    pc->nmap = ft_memalloc(sizeof(float*) * pc->map_h);
    while (y < pc->map_h)
    {
        pc->nmap[y] = ft_memalloc(sizeof(float) * pc->map_w);
        y++;
    }
    y = 0;
    pc->wall_map = ft_memalloc(sizeof(float*) * pc->map_h);
    while (y < pc->map_h)
    {
        pc->wall_map[y] = ft_memalloc(sizeof(float) * pc->map_w);
        y++;
    }
    return (1);
}