/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:15:35 by okimdil           #+#    #+#             */
/*   Updated: 2021/01/16 18:49:54 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"
#include "../includes/ray.h"

int		ft_atoi(const char *str)
{
	int result;
	int signe;

	result = 0;
	signe = 1;
	while (((*str >= 9 && *str <= 13) || *str == 32) && *str)
		str++;
	if (*str == '-')
	{
		signe = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		if (result < 0 && signe < 0)
			return (0);
		if (result < 0 && signe > 0)
			return (-1);
		result = result * 10 + *str - '0';
		str++;
	}
	return (signe * result);
}

void	ft_init(t_mapdata *map)
{
	map->width = 0;
	map->height = 0;
	map->north = 0;
	map->south = 0;
	map->east = 0;
	map->maponestr = 0;
	map->sprite = 0;
	map->west = 0;
	map->mapcheck = 0;
	map->mlx = 0;
	map->map2d = 0;
	map->map2dbefore = 0;
	map->mlxdata = 0;
	map->mlximage = 0;
	map->playery = 0;
	map->keys1 = 0;
	map->keyv1 = 0;
	map->keyv2 = 0;
	map->keyv0 = 0;
	map->keys0 = 0;
	map->keys2 = 0;
	map->pp = 0;
	map->screen = 0;
}

void	ft_read(int fd, t_mapdata *map)
{
	char		*line;
	int			ret;
	static int	notmap = 1;

	while (1)
	{
		ret = get_next_line(fd, &line);
		if ((line[0] == '1' || line[0] == ' ') && map->mapcheck < 8)
			ft_error("map isn't last in the file");
		if (map->mapcheck == 8 && (line[0] == ' ' || line[0] == '1')
			&& notmap == 1)
			notmap = 0;
		if (map->mapcheck == 8 && line[0] != '\0' && notmap == 1)
			ft_error("not an empty line");
		ft_small_check(line, map, notmap);
		if (map->mapcheck == 8 && notmap == 0)
		{
			(map->pp < ft_strlen(line)) ? map->pp = ft_strlen(line) : map->pp;
			if (helpread(line, map))
				continue;
		}
		free(line);
		if (ret == 0)
			break ;
	}
}

void	map_one_line(t_mapdata *map, char *line)
{
	char		*box;
	int			i;

	i = 0;
	box = ft_strdup(line);
	if (!map->maponestr)
		map->maponestr = ft_strdup("");
	map->maponestr = ft_strjoin(map->maponestr, box);
	map->maponestr = ft_strjoin(map->maponestr, ft_strdup("\n"));
}

void	square_helper(t_mapdata *map)
{
	static int tmp = 0;

	if (tmp == 0)
	{
		map->raydist = malloc(sizeof(int *) * map->width);
		ft_lstadd_front(&g_mylist, ft_lstnew(map->raydist));
		tmp = 1;
	}
	draw_player(map);
}
