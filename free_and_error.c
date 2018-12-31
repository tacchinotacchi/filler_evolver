/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 15:56:33 by jaelee            #+#    #+#             */
/*   Updated: 2018/12/29 05:34:41 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"

void	free_map(t_filler *pc)
{
	int index;

	index = 0;
	while (pc->map[index] != NULL)
	{
		free(pc->map[index]);
		index++;
	}
	free(pc->map);
}

void	free_piece(t_filler *pc)
{
	int index;

	index = 0;
	while (pc->piece[index] != NULL)
	{
		free(pc->piece[index]);
		index++;
	}
	free(pc->piece);
}

void	error(t_filler *pc)
{
	if (pc->map != NULL)
		free_map(pc);
	if (pc->piece != NULL)
		free_piece(pc);
	write(1, "ERROR\n", 6);
	exit(EXIT_FAILURE);
}

void	free_struct(t_filler *pc)
{
	if (pc->map != NULL)
		free_map(pc);
	if (pc->piece != NULL)
		free_piece(pc);
}
