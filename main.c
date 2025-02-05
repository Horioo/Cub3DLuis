#include "../Includes/cub3d.h"

void raycaster(t_cube *cube)
{
    int x;

    x = 0;
    while(x < SCREEN_W)
    {
        cube->ray = ft_calloc(1, sizeof(t_ray));
        init_ray(cube->data, cube->player, cube->ray, x);
        calculate_dist(cube->player, cube->ray);
        DDA(cube->data, cube->player, cube->ray);
        wall_render(cube->player, cube->ray);
        get_pixel_map(cube->data, cube->ray, x);
        free(cube->ray);
        x++;
    }
}

void render(t_cube *cube)
{
    raycaster(cube);
    draw_pixel_map(cube, cube->data);
}

void init_images(t_cube *cube)
{
	int i;

	i = 0;
	cube->anim = malloc(sizeof(void *) * 11);
	if(!cube->anim)
		return ;
	cube->anim[0] = mlx_xpm_file_to_image(cube->mlx, \
		"xpm/tocha_1.xpm", &i, &i);
	cube->anim[1] = mlx_xpm_file_to_image(cube->mlx, \
		"xpm/tocha_2.xpm", &i, &i);
	cube->anim[2] = mlx_xpm_file_to_image(cube->mlx, \
		"xpm/tocha_3.xpm", &i, &i);
	cube->anim[3] = mlx_xpm_file_to_image(cube->mlx, \
		"xpm/tocha_4.xpm", &i, &i);
	cube->anim[4] = mlx_xpm_file_to_image(cube->mlx, \
		"xpm/tocha_5.xpm", &i, &i);
	cube->anim[5] = mlx_xpm_file_to_image(cube->mlx, \
		"xpm/tocha_6.xpm", &i, &i);
	cube->anim[6] = mlx_xpm_file_to_image(cube->mlx, \
		"xpm/tocha_7.xpm", &i, &i);
	cube->anim[7] = mlx_xpm_file_to_image(cube->mlx, \
		"xpm/tocha_8.xpm", &i, &i);
	cube->anim[8] = mlx_xpm_file_to_image(cube->mlx, \
		"xpm/tocha_9.xpm", &i, &i);
	cube->anim[9] = mlx_xpm_file_to_image(cube->mlx, \
		"xpm/tocha_10.xpm", &i, &i);
	cube->anim[10] = mlx_xpm_file_to_image(cube->mlx, \
		"xpm/tocha_11.xpm", &i, &i);
}

int animation(t_cube *cube)
{
	static int index = 0;

	mlx_put_image_to_window(cube->mlx, cube->win, cube->anim[index], SCREEN_W/2, 550);
	index++;
	if(index > 10)
		index = 0;
	return(0);
}

int update_game(t_cube *cube)
{
    clear_pixel_map(cube->data);
    clear_image(cube);
    move_player(cube->player, cube->data->map);
    render(cube);
    if (cube->player->minimap)
        draw_minimap(cube);
    mlx_put_image_to_window(cube->mlx, cube->win, cube->img->img, 0, 0);
	animation(cube);
    return 0;
}



int main(int argc, char **argv)
{
    t_cube cube;

    check_errors(argc, argv);
    init_cube(&cube, argv[1]);
    load_textures(&cube, cube.data);
    mlx_hook(cube.win, 2, 1L<<0, key_press, &cube);
    mlx_hook(cube.win, 3, 1L<<1, key_release, &cube);
	mlx_loop_hook(cube.mlx, animation, &cube);
    mlx_loop_hook(cube.mlx, update_game, &cube);
    mlx_hook(cube.win, 17, 0, close_window, &cube);
    mlx_loop(cube.mlx);
    return 0;
}
