/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leiwang <leiwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 10:18:18 by leia              #+#    #+#             */
/*   Updated: 2025/06/23 18:56:40 by leiwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_palette_count(void)
{
	return (5);
}

int	get_color(int iter, int palette_index)
{
	static const int	palettes[5][5] = {{0x1F3B4D, 0x32746D, 0x66A5AD,
		0x9CC5A1, 0xD1EFB5}, {0xFFB347, 0xFF7F50, 0xFF6347, 0xFF4500,
		0xCC3700}, {0x2E2E2E, 0x444444, 0x666666, 0x999999, 0xCCCCCC},
	{0x0F0F0F, 0x1F1F1F, 0x3F3F3F, 0x5F5F5F, 0x9F9F9F}, {0x0047AB,
		0x0055DD, 0x2277EE, 0x4488FF, 0x77AAFF}};
	int					valid_index;

	if (iter == MAX_ITER)
		return (0x000000);
	valid_index = palette_index;
	while (valid_index < 0)
		valid_index += get_palette_count();
	valid_index = valid_index % get_palette_count();
	return (palettes[valid_index][iter % 5]);
}
