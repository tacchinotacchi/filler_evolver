/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 07:50:42 by jaelee            #+#    #+#             */
/*   Updated: 2018/12/30 00:29:49 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"

void	print_coord(int y, int x)
{
	ft_putnbr(y);
	ft_putchar(' ');
	ft_putnbr(x);
	ft_putchar('\n');
}

int		main(int ac, char **av)
{
	t_filler	pc;
	int			fd;
	int			success;

	fd = open(av[1], O_RDONLY);
	ft_bzero(&pc, sizeof(pc));
	pc.sum = INT_MAX;
//	get_player(&pc, fd);
	parse_input(&pc, fd);
	create_nmap(&pc);
	process_map(&pc);
	success = filler(&pc);
	if (success == 1)
		print_coord(pc.put_y, pc.put_x);
	else
		print_coord(0, 0);
	for (int i=0; i < pc.map_h; i++)
	{
		for (int j=0; j < pc.map_w; j++)
			printf("%2d ", pc.nmap[i][j]);
		printf("\n");
	}
	free_struct(&pc);
	return (0);
}
