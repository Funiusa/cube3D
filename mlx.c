/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevelyne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 23:52:39 by tevelyne          #+#    #+#             */
/*   Updated: 2021/03/22 23:52:44 by tevelyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void			my_mlx_pixel_put(t_vbls *vbls, int x, int y, int color)
{
	char	*dst;

	dst = vbls->img->i_addr +
						(y * vbls->img->i_lnl + x * (vbls->img->i_bpp / 8));
	*(unsigned int*)dst = color;
}

unsigned int	my_mlx_pixel_get(t_vbls *vbls, int x, int y)
{
	char	*dst;

	dst = vbls->img->tx_addr +
						(y * vbls->img->tx_lnl + x * (vbls->img->tx_bpp / 8));
	return (*(unsigned int*)dst);
}
