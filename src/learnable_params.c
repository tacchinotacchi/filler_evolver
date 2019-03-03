/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   learnable_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 19:14:07 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/03 22:24:34 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

const float	g_op_decay = 0.95f;
const float	g_me_decay = 0.99f;
const float	g_wall_decay = 0.99f;
const float	g_penetration_bonus = 0.2f;
const float	g_wall_bonus = 0.04f;