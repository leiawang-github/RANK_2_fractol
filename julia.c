/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiwang <leiwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 21:53:47 by leiwang           #+#    #+#             */
/*   Updated: 2025/06/23 23:04:36 by leiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	map_to_c_julia(double min, double max, int win_x, int win_y)
{
	return (min + win_x * (max - min) / win_y);
}

int	count_julia_iterations(double z_re, double z_im, double c_re, double c_im)
{
	int		iter;
	double	tmp;

	iter = 0;
	while (z_re * z_re + z_im * z_im <= 4.0 && iter < MAX_ITER)
	{
		tmp = z_re * z_re - z_im * z_im + c_re;
		z_im = 2 * z_re * z_im + c_im;
		z_re = tmp;
		iter++;
	}
	return (iter);
}

static void	put_pixel_julia(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	init_ime_buffer(t_data *data)
{
	if (data->img)
	{
		mlx_destroy_image(data->mlx, data->img);
		data->img = NULL;
	}
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
	{
		write(2, "Error: failed to create ime\n", 31);
		free_all(data);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	if (!data->addr)
	{
		write(2, "Error: failed to get ime data address\n", 40);
		free_all(data);
	}
}

void	draw_julia(t_data *data)
{
	t_draw	d;

	init_ime_buffer(data);
	d.x = 0;
	while (d.x < WIDTH)
	{
		d.y = 0;
		while (d.y < HEIGHT)
		{
			d.z_re = map_to_c(data->min_re, data->max_re, d.x, WIDTH);
			d.z_im = map_to_c(data->min_im, data->max_im, d.y, HEIGHT);
			d.iter = count_julia_iterations(d.z_re, d.z_im, data->c_re,
					data->c_im);
			d.color = get_color(d.iter, data->color_scheme);
			put_pixel_julia(data, d.x, d.y, d.color);
			d.y++;
		}
		d.x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
