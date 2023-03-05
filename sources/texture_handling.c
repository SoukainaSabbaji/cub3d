
#include "../includes/minimap.h"

void	get_texture(t_game_data *game)
{
	if (game->side == 0 && game->step.x == -1)
		game->text.ptr = mlx_xpm_file_to_image(game->mlx, game->\
		map->n_texture, &game->text.width, &game->text.height);
	if (game->side == 0 && game->step.x == 1)
		game->text.ptr = mlx_xpm_file_to_image(game->mlx, game->\
		map->s_texture, &game->text.width, &game->text.height);
	if (game->side == 1 && game->step_y == -1)
		game->text.ptr = mlx_xpm_file_to_image(game->mlx, game->\
		ma->w_texture, &game->text.width, &game->text.height);
	if (game->side == 1 && game->step_y == 1)
		game->text.ptr = mlx_xpm_file_to_image(game->mlx, game->\
		ma->e_texture, &game->text.width, &game->text.height);
	game->text.buff = (int *)mlx_get_data_addr(game->text.ptr, &game->\
		text.len, &game->text.bpp, &game->text.endian);
}

void    init_textures(t_game_data *game)
{
    if (game->side == 0)
        game->wall.x = game->pos.y + game->perp_wall_dis *\
        game->ray_dir.y;
    else 
        game->wall.x =  game->pos.x + game->perp_wall_dis *\
        game->ray_dir.x;
    game->wall.x -= (int)((game->wall.x) * (double)(game->text.width))
   game->text.x = (int)(game->wall.x * (double)(game->text.width));
	if (game->side == 0 && game->raydir_x > 0)
		game->text.x = game->text.width - game->text.x - 1;
	if (game->side == 1 && game->raydir_x < 0)
		game->text.x = game->text.width - game->text.x - 1;
	game->text.step = 1.0 * game->text.height / game->line_height;
	game->text.pos = (game->draw_start - game->screen_height \
		/ 2 + game->line_height / 2) * game->text.step;
}

void	put_texture(t_game_data *game)
{
	int	y;

	y = game->draw_start;
	while (y < game->draw_end)
	{
		game->text.y = (int)game->text.pos & (game->text.height - 1);
		game->text.pos += game->text.step;
		color = game->text.buff[game->text.height * game->text.y \
			+ game->text.x];
		if (game->side == 1)
			color = (color >> 1) & 8355711;
		game->img.arr[y * (game->screen_w) + (game->x)] = color;
		y++;
	}
}