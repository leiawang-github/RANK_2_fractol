/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiwang <leiwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:10:25 by leia              #+#    #+#             */
/*   Updated: 2025/06/23 22:53:28 by leiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	is_float(const char *s)
{
	int	i;
	int	has_digit;
	int	has_dot;

	i = 0;
	has_digit = 0;
	has_dot = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (s[i] == '.')
		{
			if (has_dot)
				return (0);
			has_dot = 1;
		}
		else if (s[i] >= '0' && s[i] <= '9')
			has_digit = 1;
		else
			return (0);
		i++;
	}
	return (has_digit);
}

double	ft_atof(const char *str)
{
	double	result;
	double	sign;
	double	frac;

	result = 0.0;
	sign = 1.0;
	frac = 0.1;
	if (*str == '-')
	{
		sign = -1.0;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	if (*str == '.')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result += (*str++ - '0') * frac;
		frac *= 0.1;
	}
	return (result * sign);
}

int	free_all(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->img)
	{
		mlx_destroy_image(data->mlx, data->img);
		data->img = NULL;
	}
	if (data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	exit(0);
	return (0);
}
