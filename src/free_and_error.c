/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 07:41:10 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/01 19:25:10 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"

static void	free_map(t_filler *pc)
{
	int index;

	index = 0;
	while (pc->map[index] != NULL)
	{
		free(pc->map[index]);
		index++;
	}
	free(pc->map);
	pc->map = NULL;
}

static void	free_nmap(t_filler *pc)
{
	int	index;

	index = 0;
	while (index < pc->map_h)
	{
		free(pc->nmap[index]);
		index++;
	}
	free(pc->nmap);
	pc->nmap = NULL;
}

static void	free_piece(t_filler *pc)
{
	int index;

	index = 0;
	while (pc->piece[index] != NULL)
	{
		free(pc->piece[index]);
		index++;
	}
	free(pc->piece);
	pc->piece = NULL;
}

void		error(t_filler *pc)
{
	if (pc->map != NULL)
		free_map(pc);
	if (pc->piece != NULL)
		free_piece(pc);
	if (pc->nmap != NULL)
		free_nmap(pc);
	ft_putstr("0 0\n");
}

void		free_all(t_filler *pc)
{
	if (pc->map != NULL)
		free_map(pc);
	if (pc->piece != NULL)
		free_piece(pc);
	if (pc->nmap != NULL)
		free_nmap(pc);
}
