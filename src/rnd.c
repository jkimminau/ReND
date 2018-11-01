#include <rnd.h>

int		loop_events(t_rnd *rnd)
{
	if (rnd->opt->autorotate && rnd->opt->highlighted_node == -1 && rnd->opt->selected_node == -1)
		rnd->opt->degree += (rnd->menu->active) ? 0.02 : 0.1;
	if ((int)rnd->opt->degree > 359)
		rnd->opt->degree = 0;
		rnd->opt->brightness -= 0.1;
	if (rnd->opt->brightness < -99)
		rnd->opt->brightness = 99;
	rnd->opt->offset += 0.5;
	if (rnd->opt->offset > rnd->data->num_songs)
		rnd->opt->offset = 0;
	mlx_destroy_image(rnd->mlx, rnd->img->ptr);
	(rnd->menu->active) ? render_menu(rnd) : render(rnd);
	return (0);
}

int		main(int ac, char **av)
{
	t_rnd	*rnd;

	if (!(rnd = init_rnd(ac, av)))
		return (printf("error initializing rnd\n"));
	//create_connections(rnd);
	mlx_hook(rnd->win, 2, 0, handle_keys, rnd);
	mlx_hook(rnd->win, 6, 1L << 6, mouse_move, rnd);
	mlx_mouse_hook(rnd->win, mouse_click, rnd);
	mlx_loop_hook(rnd->mlx, loop_events, rnd);
	mlx_hook(rnd->win, 17, 0, handle_exit, rnd);
	render_menu(rnd);
	mlx_loop(rnd->mlx);
	return (0);
}
