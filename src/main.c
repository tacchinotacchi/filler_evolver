/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 07:50:42 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/01 18:45:29 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"
#include "get_next_line.h"

void		init_filler(t_filler *pc)
{
	pc->pc_h = 0;
	pc->pc_w = 0;
	pc->map_h = 0;
	pc->map_w = 0;
	pc->put_y = 0;
	pc->put_x = 0;
	pc->map = NULL;
	pc->piece = NULL;
}

static int	get_player(t_filler *pc, int fd)
{
	char	*line;

	if (get_next_line(fd, &line) < 1)
		return (FT_FAIL);
	if (ft_strstr(line, "p1") && ft_strstr(line, "jaelee.filler"))
	{
		pc->me = 'O';
		pc->op = 'X';
	}
	else if (ft_strstr(line, "p2") && ft_strstr(line, "jaelee.filler"))
	{
		pc->me = 'X';
		pc->op = 'O';
	}
	else
	{
		free(line);
		return (FT_FAIL);
	}
	free(line);
	return (FT_SUCCESS);
}

static void	print_coord(int y, int x)
{
	ft_putnbr(y);
	ft_putchar(' ');
	ft_putnbr(x);
	ft_putchar('\n');
}

int			main(void)
{
	t_filler	pc;
	int			success;

	ft_bzero(&pc, sizeof(pc));
	if (get_player(&pc, 0) == FT_FAIL)
		return (0);
	while (1)
	{
		init_filler(&pc);
		if (parse_input(&pc, 0) == FT_FAIL)
			break ;
		/* TODO */
		if (populate_maps(&pc) == FT_FAIL)
			break ;
		/* TODO fuzzy decision */
		success = filler(&pc);
		if (success == 1)
			print_coord(pc.put_y, pc.put_x);
		else
			break ;
		free_all(&pc);
	}
	error(&pc);
	return (0);
}
