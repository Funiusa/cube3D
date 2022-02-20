/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevelyne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 23:55:35 by tevelyne          #+#    #+#             */
/*   Updated: 2021/03/23 00:10:38 by tevelyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_cail_floor(t_vbls *vbls)
{
	int		x;
	int		y;

	vbls->img->i_addr = mlx_get_data_addr(vbls->img->image,
		&vbls->img->i_bpp, &vbls->img->i_lnl, &vbls->img->i_endian);
	y = 0;
	while (y < vbls->maph / 2)
	{
		x = 0;
		while (x < vbls->mapw)
		{
			my_mlx_pixel_put(vbls, x, y, vbls->ceiling_color);
			x++;
		}
		y++;
	}
	y = vbls->maph / 2;
	while (y < vbls->maph)
	{
		x = 0;
		while (x < vbls->mapw)
			my_mlx_pixel_put(vbls, x++, y, vbls->floor_color);
		y++;
	}
}

int		render_next_frame(t_vbls *vbls)
{
	vbls->wall_size = (vbls->maph) / 90;
	if (vbls->draw)
	{
		vbls->img->image = mlx_new_image(vbls->win->mlx, vbls->mapw,
															vbls->maph);
		draw_cail_floor(vbls);
		draw_3d(vbls);
		draw_sprite(vbls);
		draw_map2d(vbls);
		draw_player_2d(vbls);
		if (!vbls->save)
			mlx_put_image_to_window(vbls->win->mlx, vbls->win->win_mlx,
									vbls->img->image, 0, 0);
		mlx_destroy_image(vbls->win->mlx, vbls->img->image);
	}
	vbls->draw = 0;
	return (0);
}

void	renderings(t_vbls vbls)
{
	vbls.win->mlx = mlx_init();
	get_path(&vbls);
	if (!vbls.save)
	{
		vbls.win->win_mlx =
			mlx_new_window(vbls.win->mlx, vbls.mapw, vbls.maph, "3DClUB");
		mlx_hook(vbls.win->win_mlx, 2, 0, move_and_destroy, &vbls);
		mlx_loop_hook(vbls.win->mlx, &render_next_frame, &vbls);
		mlx_hook(vbls.win->win_mlx, 17, 0, close_window, &vbls);
		mlx_loop(vbls.win->mlx);
	}
	else
		screenshot(&vbls);
}

int		main(int argc, char **argv)
{
	t_vbls	vbls;

	vbls.draw = 1;
	if ((!(vbls.win = malloc(sizeof(t_win))))
	|| !(vbls.img = malloc(sizeof(t_img))))
		bad_malloc(&vbls);
	if (argc == 2 && checker_name(argv[1]))
		create_tmp(&vbls, argv[1]);
	else if (argc == 3 && checker_name(argv[1]) && checker_save(argv[2]))
	{
		vbls.save = 1;
		create_tmp(&vbls, argv[1]);
	}
	else
		error_exit("Invalid! Be careful!\n");
	player(&vbls);
	if (!(vbls.z_buf = malloc(sizeof(double) * vbls.mapw)))
		bad_malloc(&vbls);
	bad_malloc(&vbls);
	renderings(vbls);
	return (0);
}
