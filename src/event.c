#include <rnd.h>

/*
 * Macros for keys.
 */

#define KEY_ESC 53
#define KEY_BACK 51
#define KEY_LEFT 123
#define KEY_RIGHT 124
#define KEY_UP 125
#define KEY_DOWN 126
#define KEY_SPACE 49
#define KEY_W 13
#define KEY_S 1
#define KEY_P 35
#define KEY_1 18
#define KEY_2 19
#define KEY_3 20
#define KEY_4 21
#define KEY_5 23
#define KEY_6 22
#define KEY_7 26
#define KEY_8 28
#define KEY_9 25
#define KEY_0 29

int		mouse_move(int x, int y, t_rnd *rnd)
{
	rnd->opt->mouse_x = x;
	rnd->opt->mouse_y = y;
	rnd->opt->mouse_degree = get_mouse_degree(rnd, x, y);
	return (0);
}

int		mouse_click(int button, int x, int y, t_rnd *rnd)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		if (rnd->menu->active)
			rnd->menu->start_pressed = 1;
		else
			rnd->opt->selected_node = rnd->opt->highlighted_node;
	}
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
	if (rnd->menu->active)
	{
		if (key == KEY_BACK)
			rnd->menu->start_pressed = 0;
		if (key == KEY_1)
			rnd->menu->recently_played = !rnd->menu->recently_played;
		if (key == KEY_2)
			rnd->menu->discover_weekly = !rnd->menu->discover_weekly;
		if (key == KEY_SPACE && rnd->menu->start_pressed)
		{
			free(rnd->data);
			if (!(read_data(rnd)))
				return (0); 
			create_connections(rnd);
			rnd->menu->active = 0;
		}
	}
	else
	{
		if (key == KEY_SPACE)
			rnd->opt->autorotate = !rnd->opt->autorotate;
		if (key == KEY_BACK)
		{
			free(rnd->data->connections);
			free(rnd->data);
			rnd->opt->highlighted_node = -1;
			rnd->opt->selected_node = -1;
			if (!(rnd->data = init_menu_data()))
				return (0);
			free(rnd->menu);
			if (!(rnd->menu = init_menu()))
				return (0);
		}
	}	
	return (0);
}
