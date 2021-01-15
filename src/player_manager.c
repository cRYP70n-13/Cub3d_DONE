/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:17:54 by okimdil           #+#    #+#             */
/*   Updated: 2021/01/15 19:41:39 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"
#include "../includes/ray.h"

int		ft_quit(void)
{
	ft_error("game over");
	return (0);
}

int		key_released(int key, t_mapdata *map)
{
	if (key == 259)
	{
		KEY_0 = 0;
		KEY_1 = 0;
		KEY_2 = 0;
	}
	(key == LEFT || key == RIGHT) ? KEY_S0 = 0 : 0;
	(key == DOWN || key == UP) ? KEY_S1 = 0 : 0;
	(key == WLEFT || key == WRIGHT) ? KEY_S2 = 0 : 0;
	if (key == WLEFT || key == WRIGHT)
	{
		if (key == WLEFT)
			KEY_2 = 0;
		if (key == WRIGHT)
			KEY_2 = 0;
	}
	if (key == DOWN || key == UP)
	{
		if (key == DOWN)
			KEY_1 = 0;
		if (key == UP)
			KEY_1 = 0;
	}
	(key == 53) ? ft_error("game over") : 0;
	return (0);
}

int		key_pressed(int key, t_mapdata *map)
{
	if (key == LEFT || key == RIGHT)
	{
		if (key == LEFT)
			KEY_0 = 1;
		if (key == RIGHT)
			KEY_0 = -1;
		KEY_S0 = 1;
	}
	if (key == WLEFT || key == WRIGHT)
	{
		if (key == WLEFT)
			KEY_2 = -1;
		if (key == WRIGHT)
			KEY_2 = 1;
		KEY_S2 = 1;
	}
	if (key == DOWN || key == UP)
	{
		if (key == DOWN)
			KEY_1 = -1;
		if (key == UP)
			KEY_1 = 1;
		KEY_S1 = 1;
	}
	return (0);
}

void	ft_movewasd(t_mapdata *map)
{
	float	x;
	float	y;
	float	x1;
	float	y1;
	int		t;

	t = g_tiles;
	y = map->map2d[(int)(map->playery + (KEY_1 * sin(ANGLE) * 10)) / (t)][(int)map->playerx / (t)];
	y1 = map->map2d[(int)(map->playery + (KEY_2 * sin(RAD(ANGLE + 90)) * 10))
	/ (t)][(int)map->playerx / (t)];
	x = map->map2d[(int)map->playery / (t)][(int)(map->playerx + (KEY_1 * cos(ANGLE) * 10)) / (t)];
	x1 = map->map2d[(int)map->playery / (t)][(int)(map->playerx + (KEY_2
	* cos(RAD(ANGLE + 90)) * 10)) / (t)];
	ANGLE = fmod(ANGLE, 2 * M_PI);
	if (ANGLE < 0)
		ANGLE += 2 * M_PI;
	if (y != '1' && y != '2' && y1 != '1' && y1 != '2')
		map->playery = map->playery + (KEY_1 * sin(ANGLE) * 4) +
			(KEY_2 * sin(RAD(ANGLE + 90)) * 2);
	if (x != '1' && x != '2' && x1 != '1' && x1 != '2')
		map->playerx = map->playerx + (KEY_1 * cos(ANGLE) * 4) +
			(KEY_2 * cos(RAD(ANGLE + 90)) * 2);
}

int		loop_me(t_mapdata *map)
{
	mlx_hook(g_mlx_win, 2, 0, &key_pressed, map);
	mlx_hook(g_mlx_win, 3, 0, &key_released, map);
	mlx_hook(g_mlx_win, 17, 0L, &ft_quit, map);
	ANGLE = fmod(ANGLE, 2 * M_PI);
	if (ANGLE < 0)
		ANGLE += 2 * M_PI;
	if (KEY_S0 == 1)
		ANGLE = ANGLE + ((KEY_0) * 0.06);
	ft_movewasd(map);
	mlx_destroy_image(map->mlx, map->mlximage);
	map->mlximage = mlx_new_image(map->mlx, map->width, map->height);
	map->mlxdata = (int *)mlx_get_data_addr(map->mlximage, &map->size_line, &map->endian, &map->endian);
	ft_helpdrawasquare(map);
	mlx_put_image_to_window(map->mlx, g_mlx_win, map->mlximage, 0, 0);
	return (0);
}
