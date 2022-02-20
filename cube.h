/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tevelyne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 00:07:57 by tevelyne          #+#    #+#             */
/*   Updated: 2021/03/23 00:08:06 by tevelyne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "minilibx_mms_20200219/mlx.h"
# include <math.h>
# include "source/get_next_line.h"
# include <errno.h>
# include <fcntl.h>

# define RED  "\x1B[31m"
# define YEL  "\x1B[33m"

typedef struct	s_sprite {
	double		x;
	double		y;
}				t_sprite;

typedef struct	s_win {
	void		*mlx;
	void		*win_mlx;
}				t_win;

typedef struct	s_img {
	void		*image;
	char		*i_addr;
	int			i_bpp;
	int			i_lnl;
	int			i_endian;

	char		*tx_addr;
	int			tx_bpp;
	int			tx_lnl;
	int			tx_endian;
	int			tex_x;
	int			tex_y;
	double		wall_x;
}				t_img;

typedef struct	s_vbls {
	t_win		*win;
	t_img		*img;
	t_sprite	*sprites;
	int			resolution;
	int			texture_no;
	int			texture_so;
	int			texture_ea;
	int			texture_we;
	int			sprite;
	int			floor;
	int			ceiling;
	int			count_line_tmp;
	int			first_line_map;
	int			max_str;
	int			params;
	int			ceiling_color_r;
	int			ceiling_color_g;
	int			ceiling_color_b;
	int			ceiling_color;
	int			floor_color;
	int			floor_color_r;
	int			floor_color_g;
	int			floor_color_b;
	int			tmp_color;
	int			count_colors;
	int			mapw;
	int			maph;
	char		**tmp;
	char		**map;
	int			hero;
	int			line_in_map;
	int			map_end;
	char		*n_tex_path;
	char		*s_tex_path;
	char		*e_tex_path;
	char		*w_tex_path;
	char		*sp_tex_path;
	void		*n_tex;
	int			n_width;
	int			n_height;
	void		*s_tex;
	int			s_width;
	int			s_height;
	void		*w_tex;
	int			w_width;
	int			w_height;
	void		*e_tex;
	int			e_width;
	int			e_height;
	void		*sp_tex;
	int			sp_width;
	int			sp_height;
	int			count_sprites;
	int			save;
	int			pl_color;
	double		plx;
	double		ply;
	int			draw;
	int			map_x;
	int			map_y;
	double		cmra_x;
	double		ray_dir_x;
	double		ray_dir_y;
	char		walldir;
	double		*z_buf;
	double		side_dst_x;
	double		side_dst_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		prp_wall_dist;
	int			step_x;
	int			step_y;
	int			side;
	int			line_hght;
	int			drw_start;
	int			drw_end;
	int			color;
	int			wall_size;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		spr_x;
	double		spr_y;
	double		invers_det;
	double		trnsfrm_x;
	double		trnsfrm_y;
	int			spr_screen_x;
	int			draw_start_y;
	int			draw_end_y;
	int			spr_wdt;
	int			spr_hgt;
	int			draw_strt_x;
	int			draw_end_x;
	int			tex_x;
	int			tex_y;
	int			stripe;
	int			res_w;
	int			res_h;
	int			tex_width;
	int			tex_height;
	double		speed;
}				t_vbls;

void			parser(t_vbls *vbls);
void			player(t_vbls *vbls);
void			create_tmp(t_vbls *vbls, char *file);
int				tmp_mass(t_vbls *vbls, char *line);
void			color_pars(char *s, t_vbls *vbls);
int				create_trgb(int t, int r, int g, int b);
int				checker_name(const char *arg);
int				checker_save(const char *arg);
void			cheak_xpm(const char *s);
int				check_path(char *path);
int				cheak_textures(t_vbls *vbls);
void			cheak_all_path(t_vbls *vbls);
int				check_empty_line_in_map(const char *str);
void			check_map(t_vbls *vbls, int *i, int *j, int *c);
void			check_null(t_vbls *vbls, int i, int j);
void			end_line_check(t_vbls *vbls, int line, int i);
int				null_end_line(t_vbls *vbls, int i, int j);
void			wall_around_sprite(t_vbls *vbls, int i, int j);
void			hero_in_the_map(t_vbls *vbls, int c, int i, int j);
int				ft_atoi(const char *str);
void			ft_bzero(void *s, size_t n);
int				ft_isdigit(int c);
char			*ft_strlcpy(char *dst, const char *src);
void			get_path(t_vbls *vbls);
void			get_sprites(t_vbls *vbls);
void			choose_textures(t_vbls *vbls);
void			sp_tex_path(char *s, t_vbls *vbls);
void			resolution_path(char *line_map, t_vbls *vbls);
void			my_mlx_pixel_put(t_vbls *vbls, int x, int y, int color);
unsigned int	my_mlx_pixel_get(t_vbls *vbls, int x, int y);
int				render_next_frame(t_vbls *vbls);
int				close_window(int keycode, t_vbls *vbls);
void			screenshot(t_vbls *vbls);
void			tex_path(char *s, t_vbls *vbls);
void			draw_cail_floor(t_vbls *vbls);
void			draw_player_2d(t_vbls *vbls);
void			draw_map2d(t_vbls *vbls);
void			ray_position_direction(t_vbls *vbls);
void			draw_3d(t_vbls *vbls);
void			draw_sprite(t_vbls *vbls);
int				move_and_destroy(int keycode, t_vbls *vbls);
void			free_tmp_mass(t_vbls *vbls);
void			bad_malloc(t_vbls *vbls);
void			error_exit(char *message);
void			init_vars_map(t_vbls *vbls);
int				check_space(t_vbls *vbls, int i, int j);
void			get_textures(t_vbls *vbls, void *tex);

#endif
