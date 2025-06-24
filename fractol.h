/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiwang <leiwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:00:17 by leiwang           #+#    #+#             */
/*   Updated: 2025/06/23 23:18:35 by leiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 600
# define MAX_ITER 60

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		color_scheme;
	double	min_re;
	double	max_re;
	double	min_im;
	double	max_im;

	double	c_re;
	double	c_im;
	int		type;

}			t_data;

typedef struct s_draw_helper
{
	int		x;
	int		y;
	int		iter;
	int		color;
	double	z_re;
	double	z_im;
}			t_draw;

double		map_to_c(double min, double max, int win_x, int win_y);
int			count_julia_iterations(double z_re, double z_im, double c_re,
				double c_im);
int			count_man_iterations(double c_re, double c_im);
void		draw_mandelbrot(t_data *data);
void		draw_julia(t_data *data);
int			handle_key(int keycode, void *param);
int			handle_mouse(int button, int x, int y, void *param);
int			get_color(int iter, int palette_index);
int			ft_strcmp(const char *s1, const char *s2);
int			is_float(const char *s);
int			parse_args(int argc, char **argv, t_data *data);
int			get_palette_count(void);
double		ft_atof(const char *str);
int			free_all(void *param);

#endif
