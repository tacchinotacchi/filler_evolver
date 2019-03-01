/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 03:54:09 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/01 19:49:42 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "get_next_line.h"

static void		skip_line(t_visu *v)
{
	char *line;

	(void)v;
	if (get_next_line(0, &line) < 1)
		ft_exit_parsing(v, line);
	free(line);
}

static int		case_plateau(char *line, t_visu *v)
{
	free(line);
	if (get_next_line(0, &line) < 1)
		ft_exit_parsing(v, line);
	free(line);
	return (1);
}

static int		case_piece(char *line, t_visu *v)
{
	char	**temp;
	int		index;

	index = 0;
	if (!(temp = ft_strsplit(line, ' ')))
		ft_exit(v);
	free(line);
	while (index < ft_atoi(temp[1]) + 3)
	{
		skip_line(v);
		index++;
	}
	ft_splitdel(temp);
	return (1);
}

int				special_case(t_visu *v)
{
	char	*line;
	int		ret;

	if (get_next_line(0, &line) < 1)
		ft_exit_parsing(v, line);
	if (ft_strstr(line, "Plateau"))
	{
		ret = case_plateau(line, v);
		return (ret);
	}
	else if (ft_strstr(line, "Piece"))
	{
		ret = case_piece(line, v);
		return (ret);
	}
	else if (ft_strstr(line, "fin"))
	{
		free(line);
		return (FINISH);
	}
	free(line);
	ft_exit(v);
	return (0);
}
