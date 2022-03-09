/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/06 15:28:20 by dritsema      #+#    #+#                 */
/*   Updated: 2022/03/09 14:51:45 by rvan-mee      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/mlx_tests.h"

mlx_image_t	*g_img;

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
	if (mlx_is_key_down(param, MLX_KEY_UP))
		g_img->instances[0].y -= 5;
	if (mlx_is_key_down(param, MLX_KEY_DOWN))
		g_img->instances[0].y += 5;
	if (mlx_is_key_down(param, MLX_KEY_LEFT))
		g_img->instances[0].x -= 5;
	if (mlx_is_key_down(param, MLX_KEY_RIGHT))
		g_img->instances[0].x += 5;
}

int	create_color(int r, int g, int b, int t)
{
	return (r << 24 | g << 16 | b << 8 | t);
}

int main(void)
{
	mlx_t		*mlx;
	game_t		game;
	int			color_count;
	int			width;
	int			height;
	mlx_image_t	**images;
	int 	base_color_p1 = 0xFF0000FF;
	int 	base_color_p2 = 0x640064FF;

	color_count = 16;
	height = 100;
	width = 100;
	mlx = mlx_init(800, 600, "cluster", 1);
	game.colors = malloc(color_count * sizeof(*game.colors));
	images = malloc(color_count * sizeof(mlx_image_t *));
	create_chip_colors(&game, base_color_p1, base_color_p2);
	for (int i = 0; i < color_count; i++)
	{
		images[i] = malloc(sizeof(mlx_image_t));
		images[i] = mlx_new_image(mlx, 40, 40);
		for (int y = 0; y < 40; y++)
		{
			for (int x = 0; x < 40; x++)
			{
				mlx_put_pixel(images[i], x, y, game.colors[i]);
			}
		}
	}

	for (size_t i = 0; i < color_count; i++)
		mlx_image_to_window(mlx, images[i], i * 40,  1);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	return (EXIT_SUCCESS);
}
