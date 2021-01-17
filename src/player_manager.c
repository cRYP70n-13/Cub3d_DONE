/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:17:54 by okimdil           #+#    #+#             */
/*   Updated: 2021/01/17 17:41:01 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"
#include "../includes/ray.h"

int		ft_exit(void)
{
	err("game over");
	return (0);
}

int		key_released(int key, t_mapdata *map)
{
	if (key == 259)
	{
		map->keyv0 = 0;
		map->keyv1 = 0;
		map->keyv2 = 0;
	}
	(key == LEFT || key == RIGHT) ? map->keys0 = 0 : 0;
	(key == DOWN || key == UP) ? map->keys1 = 0 : 0;
	(key == WLEFT || key == WRIGHT) ? map->keys2 = 0 : 0;
	if (key == WLEFT || key == WRIGHT)
	{
		if (key == WLEFT)
			map->keyv2 = 0;
		if (key == WRIGHT)
			map->keyv2 = 0;
	}
	if (key == DOWN || key == UP)
	{
		if (key == DOWN)
			map->keyv1 = 0;
		if (key == UP)
			map->keyv1 = 0;
	}
	(key == 53) ? err("game over") : 0;
	return (0);
}

int		key_pressed(int key, t_mapdata *map)
{
	if (key == LEFT || key == RIGHT)
	{
		if (key == LEFT)
			map->keyv0 = 1;
		if (key == RIGHT)
			map->keyv0 = -1;
		map->keys0 = 1;
	}
	if (key == WLEFT || key == WRIGHT)
	{
		if (key == WLEFT)
			map->keyv2 = -1;
		if (key == WRIGHT)
			map->keyv2 = 1;
		map->keys2 = 1;
	}
	if (key == DOWN || key == UP)
	{
		if (key == DOWN)
			map->keyv1 = -1;
		if (key == UP)
			map->keyv1 = 1;
		map->keys1 = 1;
	}
	return (0);
}

void	movements(t_mapdata *map)
{
	float	x;
	float	y;
	float	x1;
	float	y1;
	int		t;

	t = g_tiles;
	y = map->map2d[(int)(map->playery + (map->keyv1 * sin(map->angle) * 10))
			/ (t)][(int)map->playerx / (t)];
	y1 = map->map2d[(int)(map->playery +
			(map->keyv2 * sin(ft_rad(map->angle + 90)) * 10))
			/ (t)][(int)map->playerx / (t)];
	x = map->map2d[(int)map->playery / (t)]
		[(int)(map->playerx + (map->keyv1 * cos(map->angle) * 10)) / (t)];
	x1 = map->map2d[(int)map->playery / (t)][(int)(map->playerx + (map->keyv2
	* cos(ft_rad(map->angle + 90)) * 10)) / (t)];
	map->angle = fmod(map->angle, 2 * M_PI);
	if (map->angle < 0)
		map->angle += 2 * M_PI;
	if (y != '1' && y != '2' && y1 != '1' && y1 != '2')
		map->playery = map->playery + (map->keyv1 * sin(map->angle) * 4) +
			(map->keyv2 * sin(ft_rad(map->angle + 90)) * 2);
	if (x != '1' && x != '2' && x1 != '1' && x1 != '2')
		map->playerx = map->playerx + (map->keyv1 * cos(map->angle) * 4) +
			(map->keyv2 * cos(ft_rad(map->angle + 90)) * 2);
}

int		create_frame(t_mapdata *map)
{
	mlx_hook(g_mlx_win, 2, 0, &key_pressed, map);
	mlx_hook(g_mlx_win, 3, 0, &key_released, map);
	mlx_hook(g_mlx_win, 17, 0L, &ft_exit, map);
	map->angle = fmod(map->angle, 2 * M_PI);
	if (map->angle < 0)
		map->angle += 2 * M_PI;
	if (map->keys0 == 1)
		map->angle = map->angle + ((map->keyv0) * 0.06);
	movements(map);
	mlx_destroy_image(map->mlx, map->mlximage);
	map->mlximage = mlx_new_image(map->mlx, map->width, map->height);
	map->mlxdata = (int *)mlx_get_data_addr(map->mlximage,
						&map->size_line, &map->endian, &map->endian);
	square_helper(map);
	mlx_put_image_to_window(map->mlx, g_mlx_win, map->mlximage, 0, 0);
	return (0);
}
