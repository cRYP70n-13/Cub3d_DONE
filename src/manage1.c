/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:17:29 by okimdil           #+#    #+#             */
/*   Updated: 2021/01/16 17:05:43 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"

void	east(t_mapdata *map, char *line)
{
	static int i = 1;

	while (line[++i])
	{
		if (line[i] == '.' || ft_isalpha(line[i]))
		{
			map->east = ft_substr(line, i, ft_strlen(line));
			ft_lstadd_front(&g_mylist, ft_lstnew(map->east));
			map->mapcheck++;
			break ;
		}
	}
}

void	ft_sprite(t_mapdata *map, char *line)
{
	static int i = 1;

	while (line[++i])
	{
		if (line[i] == '.' || ft_isalpha(line[i]))
		{
			map->sprite = ft_substr(line, i, ft_strlen(line));
			ft_lstadd_front(&g_mylist, ft_lstnew(map->sprite));
			map->mapcheck++;
			break ;
		}
	}
}

void	draw_floor(t_mapdata *map, char *line)
{
	static int	i = 0;
	static int	j = 0;

	map->mapcheck++;
	if (line[i] == 'F' && line[i + 1] != ' ')
		ft_error("Something is wrong with the path F");
	while (line[i] == ' ' || (line[i - 1] != ' ' && line[i] == 'F'))
		i++;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
		{
			map->floor[j] = ft_atoi(line + i);
			i += ft_intlen(map->floor[j]) - 1;
			(map->floor[j] >= 0 && map->floor[j] <= 255) ? 0
				: ft_error("it's the wrong F number");
			j++;
		}
		(line[i] == ' ' || (line[i] == ',' && ft_isdigit(line[i + 1]) &&
			ft_isdigit(line[i - 1])) || ft_isdigit(line[i])) ? 0 :
				ft_error("not a valid F color");
		i++;
	}
	map->nhexfloor = (map->floor[0] << 16)
		| (map->floor[1] << 8) | map->floor[2];
	(j != 3) ? ft_error("not a valid F color") : 0;
}

void	ft_ceeling(t_mapdata *map, char *line)
{
	static int	i = 0;
	static int	j = 0;

	map->mapcheck++;
	if (line[i] == 'C' && line[i + 1] != ' ')
		ft_error("Something is wrong with the path ");
	while (line[i] == ' ' || (line[i - 1] != ' ' && line[i] == 'C'))
		i++;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
		{
			map->ceeling[j] = ft_atoi(line + i);
			i += ft_intlen(map->ceeling[j]) - 1;
			(map->ceeling[j] >= 0 && map->ceeling[j] <= 255) ? 0
				: ft_error("it's the wrong C number");
			j++;
		}
		(line[i] == ' ' || (line[i] == ',' && ft_isdigit(line[i + 1]) &&
			ft_isdigit(line[i - 1])) || ft_isdigit(line[i])) ? 0 :
				ft_error("not a valid C color");
		i++;
	}
	map->nhexceeling = (map->ceeling[0] << 16)
		| (map->ceeling[1] << 8) | map->ceeling[2];
	(j != 3) ? ft_error("not a valid C color") : 0;
}

void	ft_intro(int fd, t_mapdata *map)
{
	g_rows = 0;
	ft_lstadd_front(&g_mylist, ft_lstnew(map));
	ft_read(fd, map);
	if (map->mapcheck != 8)
		ft_error("something is miss stated");
	if (!map->map2dbefore)
		map->map2dbefore = ft_split(map->maponestr, '\n');
	g_rows = count_words(map->maponestr, '\n');
	if (!map->map2d)
		map_manager(map);
	ft_lstadd_front(&g_mylist, ft_lstnew(map->maponestr));
	ft_lstadd_front(&g_mylist, ft_lstnew((map->map2d)));
	ft_lstadd_front(&g_mylist, ft_lstnew((map->map2dbefore)));
	treatthatmap(map);
}
