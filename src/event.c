#include <rnd.h>

/*
 * Macros for keys.
 */

#define KEY_ESC 53
#define KEY_LEFT 123
#define KEY_RIGHT 124
#define KEY_UP 125
#define KEY_DOWN 126
#define KEY_SPACE 49
#define KEY_W 13
#define KEY_S 1
#define KEY_P 35

int		mouse_move(int x, int y, t_rnd *rnd)
{
	rnd->opt->mouse_x = x;
	rnd->opt->mouse_y = y;
	//printf("mouse (%d, %d)\n", x, y);
	return (0);
}

int		mouse_click(int button, int x, int y, t_rnd *rnd)
{
	(void)x;
	(void)y;
	if (button == 1)
		rnd->opt->selected_node = rnd->opt->highlighted_node;
	return (0);
}

int		handle_exit(t_rnd *rnd)
{
	//system( "read -n 1 -s -p \"Press any key to continue...\"" );
	free_all(rnd);
	//system( "read -n 1 -s -p \"Press any key to continue...\"" );
	exit(EXIT_SUCCESS);
	return (0);
}

int		handle_keys(int key, t_rnd *rnd)
{
	if (key == KEY_ESC)
		handle_exit(rnd);
	if (key == KEY_SPACE)
		rnd->opt->autorotate = !rnd->opt->autorotate;	
	return (0);
}
