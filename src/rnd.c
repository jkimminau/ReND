#include <rnd.h>

int		loop_events(t_rnd *rnd)
{
	if (rnd->opt->autorotate)
		rnd->opt->degree += 0.02;
	if ((int)rnd->opt->degree > 359)
		rnd->opt->degree = 0;
	rnd->opt->brightness -= 0.5;
	if (rnd->opt->brightness < -99)
		rnd->opt->brightness = 99;
	//printf("brightness = %f\n", rnd->opt->brightness);
	//mlx_destroy_image(rnd->mlx, rnd->img->ptr);
	//free(rnd->img);
	render(rnd);
	return (0);
}

int		main(int ac, char **av)
{
	t_rnd	*rnd;

	if (!(rnd = init_rnd(read_params(ac, av))))
		return (printf("error initializing rnd\n"));
	mlx_hook(rnd->win, 2, 0, handle_keys, rnd);
	mlx_hook(rnd->win, 6, 1L << 6, mouse_move, rnd);
	mlx_loop_hook(rnd->mlx, loop_events, rnd);
	mlx_hook(rnd->win, 17, 0, handle_exit, rnd);
	create_connections(rnd);
	//render(rnd);
	mlx_loop(rnd->mlx);
	return (0);
}
