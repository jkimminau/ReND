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
	rnd->opt->mouse.x = x;
	rnd->opt->mouse.y = y;
	rnd->opt->mouse_degree = get_mouse_degree(rnd, x, y);
	return (0);
}

int		mouse_click(int button, int x, int y, t_rnd *rnd)
{
	if (button == 1)
	{
		if (rnd->menu->active)
			rnd->menu->start_pressed = 1;
		else
		{
			if (x < WID - SIDEBAR_LEN)
			{
				if (rnd->opt->selected_node != -1 && rnd->opt->highlighted_node != -1 && rnd->opt->selected_node != rnd->opt->highlighted_node)
					rnd->data->songs[rnd->opt->highlighted_node]->stat_scale = 0;
				rnd->opt->selected_node = rnd->opt->highlighted_node;
			}
			rnd->opt->sidebar_mode = check_buttons(rnd, x, y);
		}
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
		/*if (key == KEY_1)
			rnd->menu->recently_played = !rnd->menu->recently_played;*/
		if (key == KEY_SPACE && rnd->menu->start_pressed)
		{
			free(rnd->data);
			if (!(read_data(rnd)))
				return (0); 
			create_connections(rnd);
			generate_user_stats(rnd);
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
			if (!(rnd->data = menu_data()))
				return (0);
			free(rnd->menu);
			if (!(rnd->menu = init_menu()))
				return (0);
			free(rnd->user);
			if (!(rnd->user = init_user()))
				return (0);
		}
	}	
	return (0);
}
