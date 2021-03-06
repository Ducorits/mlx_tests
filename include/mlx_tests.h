#ifndef MLX_TESTS_H
#define MLX_TESTS_H

/* All game logic is stored in here
int *colors
int *chip_counts
*/
typedef struct game game_t;

struct game {
	int			*colors;
	int			color_count;
	int			chip_count;
};

void create_chip_colors(game_t *game, unsigned base_color_p1, unsigned base_color_p2);
#endif
