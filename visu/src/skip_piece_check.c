/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_piece_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 02:10:33 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/01 19:49:10 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	skip_piece_check(t_visu *v, char **temp)
{
	if (!temp[0] || !temp[1] || !temp[2])
	{
		ft_splitdel(temp);
		ft_exit(v);
	}
}
