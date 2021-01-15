/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:19:20 by okimdil           #+#    #+#             */
/*   Updated: 2021/01/15 19:50:13 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"
#include "../includes/ray.h"

void	draw_sprite(t_mapdata *map, int id)
{
	int		i;
	int		j;
	int		c;
	float	size;

	i = -1;
	size = map->sprites[id].size;
	while (++i < size - 1)
	{
		if (map->sprites[id].x_off + i <= 0 || map->sprites[id].x_off + i > map->width - 1)
			continue ;
		if (map->raydist[(int)(map->sprites[id].x_off + i)] <= map->sprites[id].dist)
			continue ;
		j = -1;
		while (++j < size - 1)
		{
			if (map->sprites[id].y_off + j <= 0 || map->sprites[id].y_off + j > map->height - 1)
				continue ;
			c = map->sdata[(int)((g_tiles) *
					(g_tiles * j / (int)size) + (g_tiles * i / (int)size))];
			if (c != map->sdata[0])
				map->mlxdata[(int)((j + map->sprites[id].y_off) *
				map->width + (i + map->sprites[id].x_off))] = c;
		}
	}
}

void	to_sort(t_mapdata *map)
{
	int				i;
	int				j;
	t_sprite		tmp;

	i = 0;
	while (i < g_count - 1)
	{
		j = i;
		while (j < g_count - 1)
		{
			if (map->sprites[j].dist < map->sprites[j + 1].dist)
			{
				tmp = map->sprites[j];
				map->sprites[j] = map->sprites[j + 1];
				map->sprites[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	to_sprite(t_mapdata *map, int m)
{
	float	angle;
	int		k;

	m = -1;
	k = -1;
	to_sort(map);
	angle = 0;
	while (++k < g_count)
	{
		map->sprites[k].dist = sqrtf(((map->sprites[k].x) - map->playerx) * ((map->sprites[k].x) - map->playerx)
			+ ((map->sprites[k].y) - map->playery) * ((map->sprites[k].y) - map->playery));
		angle = atan2f(map->sprites[k].y - map->playery, map->sprites[k].x - map->playerx);
		while (angle - map->angle > M_PI)
			angle -= 2 * M_PI;
		while (angle - map->angle < -M_PI)
			angle += 2 * M_PI;
		map->sprites[k].size = (map->width / map->sprites[k].dist) * g_tiles;
		map->sprites[k].y_off = map->height / 2 - (int)map->sprites[k].size / 2;
		map->sprites[k].x_off = ((DEG(angle) - DEG(map->angle)) * map->width)
		/ (float)g_tiles + ((map->width / 2.0f) - (int)map->sprites[k].size / 2.0f);
		draw_sprite(map, k);
	}
}

void	init_spt(t_mapdata *map)
{
	int			i;
	int			j;
	int			k;

	i = -1;
	k = 0;
	if (!(map->sprites = malloc(sizeof(t_sprite) * (g_count + 1))))
		ft_error("");
	ft_lstadd_front(&g_mylist, ft_lstnew(map->sprites));
	(map->simg = mlx_xpm_file_to_image(map->mlx, map->sprite, &SH, &SW)) ==
		0 ? ft_error("wrong sprite extension") : 0;
	map->sdata = (int *)mlx_get_data_addr(map->simg, &DT, &DT1, &DT1);
	while (map->map2d[++i] != 0 && (j = -1) && (k < g_count))
		while (map->map2d[i][++j] != 0 && (k < g_count))
			if (map->map2d[i][j] == '2')
			{
				map->sprites[k].x_off = 0;
				map->sprites[k].y_off = 0;
				map->sprites[k].size = 0;
				map->sprites[k].x = (j + 0.5f) * g_tiles;
				map->sprites[k].y = (i + 0.5f) * g_tiles;
				map->sprites[k].dist = sqrtf(((map->sprites[k].x) - map->playerx) * ((map->sprites[k].x)
					- map->playerx) + ((map->sprites[k].y) - map->playery) * ((map->sprites[k].y) - map->playery));
				k++;
			}
}
