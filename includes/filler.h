/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 23:03:21 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/01 22:22:06 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "libft.h"
# include <fcntl.h>
# include <limits.h>
# define OPEN 1e+6
# define ABOVE 1
# define BELOW 2
# define FT_FAIL 0
# define FT_SUCCESS 1

typedef struct	s_filler
{
	int		pc_h;
	int		pc_w;
	int		map_h;
	int		map_w;
	int		start_pos;
	int		put_y;
	int		put_x;
	char	**piece;
	char	**map;
	float	**wall_map;
	float	**nmap;
	char	me;
	char	op;
}				t_filler;

int				parse_input(t_filler *pc, int fd);
int				parse_input2(t_filler *pc, int fd);
int				verify_split(char **split);
int				get_start_pos(t_filler *pc);
void			init_filler(t_filler *pc);
int				create_nmap(t_filler *pc);
void			process_nmap(t_filler *pc);
int				filler(t_filler *pc);
int				ft_atoi_ptr(char **str);
void			error(t_filler *pc);
void			free_all(t_filler *pc);
int     		populate_maps(t_filler *pc);

#endif
