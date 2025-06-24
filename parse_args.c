/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiwang <leiwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:11:34 by leia              #+#    #+#             */
/*   Updated: 2025/06/23 22:43:16 by leiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	print_usage(void)
{
	write(1, "Usage:\n", 7);
	write(1, "  ./fractol mandelbrot\n", 24);
	write(1, "  ./fractol julia | julia [float 1][float 2]\n", 46);
}

static int	init_mandelbrot(t_data *data)
{
	data->type = 0;
	return (1);
}

static int	init_julia(int argc, char **argv, t_data *data)
{
	data->type = 1;
	data->c_re = -0.8;
	data->c_im = 0.156;
	if (argc == 4)
	{
		if (!is_float(argv[2]) || !is_float(argv[3]))
		{
			print_usage();
			return (0);
		}
		if (ft_atof(argv[2]) < -2.0 || ft_atof(argv[2]) > 2.0
			|| ft_atof(argv[3]) < -2.0 || ft_atof(argv[3]) > 2.0)
		{
			write(1, "!Parameter floats must range from [-2, 2]\n", 43);
			return (0);
		}
		data->c_re = ft_atof(argv[2]);
		data->c_im = ft_atof(argv[3]);
	}
	else if (argc != 2)
	{
		print_usage();
		return (0);
	}
	return (1);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	data->min_re = -2.0;
	data->max_re = 2.0;
	data->min_im = -1.5;
	data->max_im = 1.5;
	data->color_scheme = 0;
	data->type = -1;
	if (argc == 2 && ft_strcmp(argv[1], "mandelbrot") == 0)
		return (init_mandelbrot(data));
	if ((argc == 2 || argc == 4) && ft_strcmp(argv[1], "julia") == 0)
		return (init_julia(argc, argv, data));
	print_usage();
	return (0);
}
