/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiwang <leiwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:59:41 by leiwang           #+#    #+#             */
/*   Updated: 2025/06/24 19:46:52 by leiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	start_fractol(t_data *data, char *fractol_name)
{
	if (ft_strcmp(fractol_name, "mandelbrot") == 0)
	{
		draw_mandelbrot(data);
		mlx_key_hook(data->win, handle_key, data);
		mlx_mouse_hook(data->win, handle_mouse, data);
	}
	else if (ft_strcmp(fractol_name, "julia") == 0)
	{
		draw_julia(data);
		mlx_key_hook(data->win, handle_key, data);
		mlx_mouse_hook(data->win, handle_mouse, data);
	}
	mlx_hook(data->win, 17, 0, free_all, data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!parse_args(argc, argv, &data))
		return (1);
	data.mlx = mlx_init();
	if (!data.mlx)
	{
		write(2, "Error: failed to initiate mlx\n", 31);
		return (1);
	}
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, argv[1]);
	if (!data.win)
	{
		write(2, "Error: failed to create a window\n", 33);
		free(data.mlx);
		return (1);
	}
	start_fractol(&data, argv[1]);
	mlx_loop(data.mlx);
	return (0);
}
