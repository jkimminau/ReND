#include <rnd.h>

void			press_start(t_rnd *rnd)
{
	mlx_string_put(rnd->mlx, rnd->win, WID / 2 - 15, LEN / 2, brightness(0xffffff, fabs(rnd->opt->brightness)), "ReND");
}

void			menu(t_rnd *rnd)
{
	mlx_string_put(rnd->mlx, rnd->win, WID / 2 - 15, (LEN / 2) - 80, 0xffffff, "ReND");
	mlx_string_put(rnd->mlx, rnd->win, WID / 2 - 200, (LEN / 2) - 50, 0x999999, "Select options and push [Space] to continue");
	mlx_string_put(rnd->mlx, rnd->win, WID / 2 - 70, (LEN / 2) - 20, (rnd->menu->recently_played) ? 0x00ff00 : 0xff0000, "1) Recently Played");
	mlx_string_put(rnd->mlx, rnd->win, WID / 2 - 70, (LEN / 2), (rnd->menu->discover_weekly) ? 0x00ff00 : 0xff0000, "2) Discover Weekly");
	mlx_string_put(rnd->mlx, rnd->win, WID / 2 - 70, (LEN / 2) + 20, 0xff0000, "3) Add Album");
}

void			render_menu(t_rnd *rnd)
{
	rnd->img = init_img(rnd->mlx);
	draw_node_map(rnd, WID / 2, LEN / 2);
	mlx_put_image_to_window(rnd->mlx, rnd->win, rnd->img->ptr, 0, 0);
	if (rnd->menu->start_pressed)
		menu(rnd);
	else
		press_start(rnd);
}