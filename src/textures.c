/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:18:33 by okimdil           #+#    #+#             */
/*   Updated: 2021/01/16 12:58:40 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"
#include "../includes/ray.h"

float	sean(t_mapdata *map)
{
	if (map->map2d[(int)map->playery / g_tiles]
					[(int)map->playerx / g_tiles] == 'N')
		return (RAD(270));
	else if (map->map2d[(int)map->playery / g_tiles]
						[(int)map->playerx / g_tiles] == 'W')
		return (RAD(180));
	else if (map->map2d[(int)map->playery / g_tiles]
						[(int)map->playerx / g_tiles] == 'S')
		return (RAD(90));
	else if (map->map2d[(int)map->playery / g_tiles]
						[(int)map->playerx / g_tiles] == 'E')
		return (RAD(0));
	return (0);
}

void	picktxt(t_horizontal *it)
{
	if (it->faceup && it->hith)
		it->textnum = 1;
	if (it->faceleft && it->hitv)
		it->textnum = 2;
	if (it->facedown && it->hith)
		it->textnum = 3;
	if (it->faceright && it->hitv)
		it->textnum = 0;
}

void	texture(t_mapdata *map)
{
	int	usless;
	int uslesser;

	(map->textureimage = mlx_xpm_file_to_image(map->mlx, map->east,
			&uslesser, &uslesser)) ? 0 : ft_error("wrong ea path");
	map->texturedata[0] = (int *)mlx_get_data_addr(map->textureimage,
							&usless, &usless, &usless);
	(map->textureimage = mlx_xpm_file_to_image(map->mlx, map->north,
						&uslesser, &uslesser)) ? 0 : ft_error("wrong no path");
	map->texturedata[1] = (int *)mlx_get_data_addr(map->textureimage,
						&usless, &usless, &usless);
	(map->textureimage = mlx_xpm_file_to_image(map->mlx, map->west,
						&uslesser, &uslesser)) ? 0 : ft_error("wrong we path");
	map->texturedata[2] = (int *)mlx_get_data_addr(map->textureimage,
						&usless, &usless, &usless);
	(map->textureimage = mlx_xpm_file_to_image(map->mlx, map->south,
						&uslesser, &uslesser)) ? 0 : ft_error("wrong so path");
	map->texturedata[3] = (int *)mlx_get_data_addr(map->textureimage,
						&usless, &usless, &usless);
}
