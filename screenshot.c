/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevelyne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:12:22 by tevelyne          #+#    #+#             */
/*   Updated: 2021/03/23 00:12:24 by tevelyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	meta_bmp_header(t_vbls *vbls, unsigned char *header)
{
	ft_bzero(header, 54);
	header[0] = 'B';
	header[1] = 'M';
	header[2] = ((vbls->mapw * vbls->maph) + 54);
	header[3] = ((vbls->mapw * vbls->maph) + 54) >> 8;
	header[4] = ((vbls->mapw * vbls->maph) + 54) >> 16;
	header[5] = ((vbls->mapw * vbls->maph) + 54) >> 24;
	header[10] = 54;
	header[14] = 40;
	header[18] = vbls->mapw;
	header[19] = vbls->mapw >> 8;
	header[20] = vbls->mapw >> 16;
	header[21] = vbls->mapw >> 24;
	header[22] = (vbls->maph);
	header[23] = vbls->maph >> 8;
	header[24] = vbls->maph >> 16;
	header[25] = vbls->maph >> 24;
	header[26] = 1;
	header[28] = vbls->img->i_bpp;
}

void		screenshot(t_vbls *vbls)
{
	int				fd;
	int				i;
	int				j;
	unsigned char	bmp_header[54];

	render_next_frame(vbls);
	meta_bmp_header(vbls, bmp_header);
	fd = open("screenshot.bmp", O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
	write(fd, &bmp_header, 54);
	i = vbls->maph - 1;
	j = (vbls->img->i_bpp / 8) * vbls->mapw;
	while (i >= 0)
		write(fd, &vbls->img->i_addr[vbls->img->i_lnl * i--], j);
	close(fd);
	exit(0);
}
