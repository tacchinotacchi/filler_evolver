/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 07:41:10 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/04 18:45:36 by aamadori         ###   ########.fr       */
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

static void	free_opmap(t_filler *pc)
{
	int	index;

	index = 0;
	while (index < pc->map_h)
	{
		free(pc->opmap[index]);
		free(pc->memap[index]);
		free(pc->wall_map[index]);
		index++;
	}
	free(pc->opmap);
	free(pc->memap);
	free(pc->wall_map);
	pc->opmap = NULL;
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
	if (pc->opmap != NULL)
		free_opmap(pc);
	ft_putstr("0 0\n");
}

void		free_all(t_filler *pc)
{
	if (pc->map != NULL)
		free_map(pc);
	if (pc->piece != NULL)
		free_piece(pc);
	if (pc->opmap != NULL)
		free_opmap(pc);
}
