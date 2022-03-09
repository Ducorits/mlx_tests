#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/mlx_tests.h"

int	rgb_to_int(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}

void rgb_to_hsv(float *r, float *g, float *b, float *h, float *s, float *v)
{
	float x_min, x_max, c;

	*v = fmaxf(*r, *g);
	*v = fmaxf(*v, *b);
	x_max = *v;
	x_min = fminf(*r, *g);
	x_min = fminf(x_min, *b);
	c = x_max - x_min;
	if (c == 0)
		*h = 0;
	else if (*v == *r)
		*h = 1.0 / 6 * (0 + (*g - *b) / c);
	else if (*v == *g)
		*h = 1.0 / 6 * (2 + (*b - *r) / c);
	else if (*v == *b)
		*h = 1.0 / 6 * (4 + (*r - *g) / c);
	if (*h < 0)
		*h += 1;
	if (*v == 0)
		*s = 0;
	else
		*s = c / *v;
}

void hsv_to_rgb(float *h, float *s, float *v, float *r, float *g, float *b)
{
	float	h_priem;
	float 	m, x, c, r1 = 0, g1 = 0, b1 = 0;

	h_priem = *h / (1.0 / 6);
	c = *v * *s;
	x = c * (1 - fabs(fmod(h_priem, 2.0) - 1));
	if (0 <= h_priem && h_priem < 1)
		r1 = c, g1 = x, b1 = 0;
	else if (1 <= h_priem && h_priem < 2)
		r1 = x, g1 = c, b1 = 0;
	else if (2 <= h_priem && h_priem < 3)
		r1 = 0, g1 = c, b1 = x;
	else if (3 <= h_priem && h_priem < 4)
		r1 = 0, g1 = x, b1 = c;
	else if (4 <= h_priem && h_priem < 5)
		r1 = x, g1 = 0, b1 = c;
	else if (5 <= h_priem && h_priem < 6)
		r1 = c, g1 = 0, b1 = x;
	m = *v - c;
	*r = r1 + m;
	*g = g1 + m;
	*b = b1 + m;
}

void	split_rgb(int base_color, float *r, float *g, float *b)
{
	*r = (base_color >> 24 & 0xFF) / 255.0;
	*g = (base_color >> 16 & 0xFF) / 255.0;
	*b = (base_color >> 8 & 0xFF) / 255.0;
}

void create_chip_colors(game_t *game)
{
	int 	base_color_p1 = 0xFF0000FF;
	int 	base_color_p2 = 0x0000FFFF;
	int		colors = 16;
	// int		player_colors[colors];
	float	h_increase;
	float	r, g, b;
	float	h, s, v;
	// int		new_color;

	h_increase = 1.0 / (colors * 3);
	printf("h increase = %f, previous increase: %f\n", h_increase, 1.0 / 12);
	split_rgb(base_color_p1, &r, &g, &b);
	rgb_to_hsv(&r, &g, &b, &h, &s, &v);
	for (int i = 0; i < colors; i += 1) {
		hsv_to_rgb(&h, &s, &v, &r, &g, &b);
		if (i == colors / 2)
			split_rgb(base_color_p2, &r, &g, &b);
		rgb_to_hsv(&r, &g, &b, &h, &s, &v);
		game->colors[i] = rgb_to_int(r * 255, g * 255, b * 255);
		h = fmod(h + h_increase, 1.0);
	}
	printf("starting colors: P1 %x, P2 %x\n", base_color_p1, base_color_p2);
	for (int i = 0; i < colors; i += 1)
	{
		printf("color: %d: %x\n", i, game->colors[i]);

	}
}
	// printf("new color: 0x%x in decimal: %d\n", new_color, new_color);
	// printf("R: %f, G: %f, B: %f\nH: %f, S: %f, V: %f\n", r, g, b, h, s, v);
// int	main(void)
// {
// 	create_chip_colors();
// 	return(1);
// }
