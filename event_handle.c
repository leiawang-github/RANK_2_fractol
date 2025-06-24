/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiwang <leiwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:02:12 by leiwang           #+#    #+#             */
/*   Updated: 2025/06/23 23:10:22 by leiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	update_position(int keycode, t_data *data, double re_range,
		double im_range)
{
	double	shift;

	shift = 0.1;
	if (keycode == 123)
	{
		data->min_re -= re_range * shift;
		data->max_re -= re_range * shift;
	}
	else if (keycode == 124)
	{
		data->min_re += re_range * shift;
		data->max_re += re_range * shift;
	}
	else if (keycode == 125)
	{
		data->min_im += im_range * shift;
		data->max_im += im_range * shift;
	}
	else if (keycode == 126)
	{
		data->min_im -= im_range * shift;
		data->max_im -= im_range * shift;
	}
}

int	handle_key(int keycode, void *param)
{
	t_data	*data;
	double	re_range;
	double	im_range;

	data = (t_data *)param;
	re_range = data->max_re - data->min_re;
	im_range = data->max_im - data->min_im;
	if (keycode == 53)
		return (free_all(data));
	if (keycode == 8)
		data->color_scheme = (data->color_scheme + 1) % get_palette_count();
	else
		update_position(keycode, data, re_range, im_range);
	if (data->type == 1)
		draw_julia(data);
	else
		draw_mandelbrot(data);
	return (0);
}

static void	apply_zoom(t_data *data, double zoom, int x, int y)
{
	double	mouse_re;
	double	mouse_im;

	mouse_re = map_to_c(data->min_re, data->max_re, x, WIDTH);
	mouse_im = map_to_c(data->min_im, data->max_im, y, HEIGHT);
	data->min_re = mouse_re + (data->min_re - mouse_re) * zoom;
	data->max_re = mouse_re + (data->max_re - mouse_re) * zoom;
	data->min_im = mouse_im + (data->min_im - mouse_im) * zoom;
	data->max_im = mouse_im + (data->max_im - mouse_im) * zoom;
}

int	handle_mouse(int button, int x, int y, void *param)
{
	t_data	*data;
	double	zoom;

	data = (t_data *)param;
	zoom = 1.0;
	if (button == 4)
		zoom = 0.9;
	else if (button == 5)
		zoom = 1.1;
	if (zoom == 1.0)
		return (0);
	apply_zoom(data, zoom, x, y);
	if (data->type == 1)
		draw_julia(data);
	else
		draw_mandelbrot(data);
	return (0);
}
