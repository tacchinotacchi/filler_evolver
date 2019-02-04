/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 21:23:13 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/28 09:20:21 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"
#include "get_next_line.h"

static void	parse_piece(t_filler *pc, char **split, int fd)
{
	int		index;
	int		cnt;

	pc->pc_h = ft_atoi(split[1]);
	pc->pc_w = ft_atoi(split[2]);
	(pc->pc_h > 0 && pc->pc_w > 0) ? 0 : error(pc);
	index = 0;
	cnt = 0;
	if (!(pc->piece = ft_memalloc(sizeof(char*) * (pc->pc_h + 1))))
		error(pc);
	while (index < pc->pc_h)
	{
		if ((get_next_line(fd, &(pc->piece[index]))) < 1)
			error(pc);
		pc->pc_w == (int)ft_strlen(pc->piece[index]) ? 0 : error(pc);
		if (ft_strchr(pc->piece[index], '*'))
			cnt++;
		index++;
	}
	cnt > 0 ? 0 : error(pc);
}

static void	parse_map(t_filler *pc, char **split, int fd)
{
	int		index;
	char	*line;

	pc->map_h = ft_atoi(split[1]);
	pc->map_w = ft_atoi(split[2]);
	(pc->map_h > 0 && pc->map_w > 0) ? 0 : error(pc);
	index = 0;
	if (!(pc->map = ft_memalloc(sizeof(char*) * (pc->map_h + 1))))
		error(pc);
	(get_next_line(fd, &line)) < 1 ? error(pc) : 0;
	free(line);
	while (index < pc->map_h)
	{
		(get_next_line(fd, &line)) < 1 ? error(pc) : 0;
		ft_strlen(line) < 4 ? error(pc) : 0;
		if (!(pc->map[index] = ft_strdup(line + 4)))
			error(pc);
		pc->map_w == (int)ft_strlen(pc->map[index]) ? 0 : error(pc);
		index++;
		free(line);
	}
}

static void	get_start_pos(t_filler *pc)
{
	int	x;
	int	y;
	int	y_me;
	int	y_op;

	y_me = -1;
	y_op = -1;
	y = 0;
	while (y < pc->map_h)
	{
		x = 0;
		while (x < pc->map_w)
		{
			if (pc->map[y][x] == pc->me)
				y_me = y;
			if (pc->map[y][x] == pc->op)
				y_op = y;
			x++;
		}
		y++;
	}
	if (y_me < 0 || y_op < 0)
		error(pc);
	pc->start_pos = (y_me < y_op) ? ABOVE : BELOW;
}

static int	verify_split(char **split)
{
	int		cnt;

	cnt = 0;
	while (split[cnt])
		cnt++;
	if (cnt != 3)
		return (FT_FAIL);
	if (ft_strcmp("Plateau", split[0]) && ft_strcmp("Piece", split[0]))
		return (FT_FAIL);
	if (!ft_str_is_digit(split[1]) || !ft_str_is_digit(split[2]))
		return (FT_FAIL);
	return (FT_SUCCESS);
}

void		parse_input(t_filler *pc, int fd)
{
	char	*line;
	char	**split;

	init_filler(pc);
	(get_next_line(fd, &line) < 1) ? error(pc) : 0;
	if (!(split = ft_strsplit(line, ' ')))
	{
		free(line);
		error(pc);
	}
	free(line);
	(verify_split(split) == FT_FAIL) ? error(pc) : 0;
	parse_map(pc, split, fd);
	ft_splitdel(split);
	pc->start_pos == 0 ? get_start_pos(pc) : 0;
	(get_next_line(fd, &line) < 1) ? error(pc) : 0;
	if (!(split = ft_strsplit(line, ' ')))
	{
		free(line);
		error(pc);
	}
	free(line);
	(verify_split(split) == FT_FAIL) ? error(pc) : 0;
	parse_piece(pc, split, fd);
}
