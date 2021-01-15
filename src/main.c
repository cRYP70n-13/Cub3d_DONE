/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okimdil <okimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 19:17:15 by okimdil           #+#    #+#             */
/*   Updated: 2021/01/15 19:31:17 by okimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"
#include "../includes/ray.h"

void	init(t_horizontal *it, t_mapdata *map)
{
	it->dx = 0;
	it->x = 0;
	it->wallx = 0;
	it->dy = 0;
	it->y = 0;
	it->wally = 0;
	it->facedown = 0;
	it->faceup = 0;
	it->faceleft = 0;
	it->faceright = 0;
	map->floor[0] = 0;
	C[0] = 0;
	map->floor[1] = 0;
	C[1] = 0;
	map->floor[2] = 0;
	C[2] = 0;
}

void	mlx_stuff(t_mapdata *map)
{
	static int c = 0;

	g_mlx_win = mlx_new_window(MLX, map->width, map->height, "CUB3D");
	IMAGE = mlx_new_image(MLX, map->width, map->height);
	DATA = (int *)mlx_get_data_addr(IMAGE, &SIZELINE, &ENDIAN, &ENDIAN);
	if (c == 0)
	{
		init_spt(map);
		c = 1;
	}
	ft_helpdrawasquare(map);
	mlx_put_image_to_window(MLX, g_mlx_win, IMAGE, 0, 0);
	if (SCREEN == 1)
	{
		save_bmp(map);
		ft_lstclear(&g_mylist);
		exit(1);
	}
	mlx_loop_hook(MLX, &loop_me, map);
	mlx_loop(MLX);
}

int		ft_checkex(char *s)
{
	int	end;
	int i;

	i = 0;
	end = ft_strlen(s) - 1;
	if (s[end] == 'b' && s[end - 1] == 'u'
		&& s[end - 2] == 'c' && s[end - 3] == '.')
		return (1);
	return (0);
}

int		main(int argc, char **argv)
{
	int			fd;
	t_mapdata	*map;

	g_tiles = 64;
	g_count = 0;
	if (!(map = malloc(sizeof(t_mapdata))))
		ft_error("can't be allocated");
	ft_init(map);
	g_mylist = ft_lstnew(0);
	MLX = mlx_init();
	fd = open(argv[1], O_RDONLY);
	if (argc == 3)
		((ft_strncmp(argv[2], "--save", 6) == 0)) ?
			SCREEN = 1 : ft_error("wrong argument");
	((argc == 2 && fd > 0) || (argc == 3 && SCREEN == 1)) ? ft_intro(fd, map)
		: ft_error("where is my map");
	(ft_checkex(argv[1])) ? 0 : ft_error("wrong extension");
	texture(map);
	ANGLE = sean(map);
	mlx_stuff(map);
	ft_lstclear(&g_mylist);
}
