/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:18:33 by okimdil           #+#    #+#             */
/*   Updated: 2021/01/15 19:41:39 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"
#include "../includes/ray.h"

float	sean(t_mapdata *map)
{
	if (map->map2d[(int)map->playery / g_tiles][(int)map->playerx / g_tiles] == 'N')
		return (RAD(270));
	else if (map->map2d[(int)map->playery / g_tiles][(int)map->playerx / g_tiles] == 'W')
		return (RAD(180));
	else if (map->map2d[(int)map->playery / g_tiles][(int)map->playerx / g_tiles] == 'S')
		return (RAD(90));
	else if (map->map2d[(int)map->playery / g_tiles][(int)map->playerx / g_tiles] == 'E')
		return (RAD(0));
	return (0);
}

void	picktxt(t_horizontal *it)
{
	if (FCEUP && HH)
		TXTNUM = 1;
	if (FCELEFT && HV)
		TXTNUM = 2;
	if (FCEDOWN && HH)
		TXTNUM = 3;
	if (FCERIGHT && HV)
		TXTNUM = 0;
}

void	texture(t_mapdata *map)
{
	int	usless;
	int uslesser;

	(TXTIMG = mlx_xpm_file_to_image(map->mlx, map->east, &uslesser, &uslesser))
		? 0 : ft_error("wrong ea path");
	TXTDATA[0] = (int *)mlx_get_data_addr(TXTIMG, &usless, &usless, &usless);
	(TXTIMG = mlx_xpm_file_to_image(map->mlx, map->north, &uslesser, &uslesser))
		? 0 : ft_error("wrong no path");
	TXTDATA[1] = (int *)mlx_get_data_addr(TXTIMG, &usless, &usless, &usless);
	(TXTIMG = mlx_xpm_file_to_image(map->mlx, map->west, &uslesser, &uslesser))
		? 0 : ft_error("wrong we path");
	TXTDATA[2] = (int *)mlx_get_data_addr(TXTIMG, &usless, &usless, &usless);
	(TXTIMG = mlx_xpm_file_to_image(map->mlx, map->south, &uslesser, &uslesser))
		? 0 : ft_error("wrong so path");
	TXTDATA[3] = (int *)mlx_get_data_addr(TXTIMG, &usless, &usless, &usless);
}
