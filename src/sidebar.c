#include <rnd.h>

int				check_buttons(t_rnd *rnd, int x, int y)
{
	if (rnd->opt->sidebar_mode == 0)
	{
		if (sqrt(pow((x - rnd->btn->grad_up.x), 2) + pow((y - rnd->btn->grad_up.y), 2)) < BUTTON_RAD + 1)
			rnd->opt->graph_rad += 2;
		else if ((sqrt(pow((x - rnd->btn->grad_down.x), 2) + pow((y - rnd->btn->grad_down.y), 2)) < BUTTON_RAD + 1) && rnd->opt->graph_rad >= 0)
			rnd->opt->graph_rad = (rnd->opt->graph_rad >= 2) ? rnd->opt->graph_rad - 2 : 0;
		else if (sqrt(pow((x - rnd->btn->nrad_up.x), 2) + pow((y - rnd->btn->nrad_up.y), 2)) < BUTTON_RAD + 1)
			rnd->opt->node_rad += 2;
		else if ((sqrt(pow((x - rnd->btn->nrad_down.x), 2) + pow((y - rnd->btn->nrad_down.y), 2)) < BUTTON_RAD + 1) && rnd->opt->node_rad >= 0)
			rnd->opt->node_rad = (rnd->opt->node_rad >= 2) ? rnd->opt->node_rad - 2 : 0;
		else if ((sqrt(pow((x - rnd->btn->thresh_up.x), 2) + pow((y - rnd->btn->thresh_up.y), 2)) < BUTTON_RAD + 1) && rnd->opt->threshold < 8)
			rnd->opt->threshold++;
		else if ((sqrt(pow((x - rnd->btn->thresh_down.x), 2) + pow((y - rnd->btn->thresh_down.y), 2)) < BUTTON_RAD + 1) && rnd->opt->threshold > 0)
			rnd->opt->threshold--;
	}
	if (x >= rnd->btn->settings.x && x < rnd->btn->settings.x + (SIDEBAR_LEN / 4.5) && y >= rnd->btn->settings.y && y < rnd->btn->settings.y + 20)
		return (0);
	else if (x >= rnd->btn->songs.x && x < rnd->btn->songs.x + (SIDEBAR_LEN / 6) && y >= rnd->btn->songs.y && y < rnd->btn->songs.y + 20)
		return (1);
	else if (x >= rnd->btn->user.x && x < rnd->btn->user.x + (SIDEBAR_LEN / 6) && y >= rnd->btn->user.y && y < rnd->btn->user.y + 20)
		return (2);
	return (rnd->opt->sidebar_mode);
}

void		draw_stat(t_rnd *rnd, int x, int y, t_song *s, double min, double max, double stat, int color)
{
	int		i;
	int		j;
	int		wid;

	if (stat < min)
		stat = min;
	if (stat > max)
		stat = max;
	wid = STAT_WID * s->stat_scale * (stat - min) / (max - min); 
	i = 0;
	while (i < STAT_LEN)
	{
		j = 0;
		while (j < wid)
		{
			img_pixel_put(rnd->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
	if (s->stat_scale < 1)
		s->stat_scale += (1 - s->stat_scale) / 150;
}

void		draw_user_stats(t_rnd *rnd, int x, int y)
{
	t_song		s;

	if (rnd->opt->sidebar_mode == 2)
	{
		s.acousticness = rnd->user->acousticness;
		s.danceability = rnd->user->danceability;
		s.energy = rnd->user->energy;
		s.instrumentalness = rnd->user->instrumentalness;
		s.loudness = rnd->user->loudness;
		s.speechiness = rnd->user->speechiness;
		s.tempo = rnd->user->tempo;
		s.valence = rnd->user->valence;
		s.stat_scale = rnd->user->stat_scale;
		draw_stat(rnd, x, y, &s, 0, 1, s.acousticness, 0x22ee00);
		draw_stat(rnd, x, y + 100, &s, 0, 1, s.danceability, 0x22ee00);
		draw_stat(rnd, x, y + 200, &s, 0, 1, s.energy, 0x22ee00);
		draw_stat(rnd, x, y + 300, &s, 0, 1, s.instrumentalness, 0x22ee00);
		draw_stat(rnd, x, y + 400, &s, -60, 0, s.loudness, 0x22ee00);
		draw_stat(rnd, x, y + 500, &s, 0, 1, s.speechiness, 0x22ee00);
		draw_stat(rnd, x, y + 600, &s, 60, 200, s.tempo, 0x22ee00);
		draw_stat(rnd, x, y + 700, &s, 0, 1, s.valence, 0x22ee00);
		rnd->user->stat_scale = s.stat_scale + (1 - s.stat_scale) / 150;
	}
	else
		rnd->user->stat_scale = 0;
}

void		draw_stats(t_rnd *rnd, t_song *s, int x, int y)
{
	t_song	*s1;
	t_song	*s2;
	int		node_num;

	node_num = (rnd->opt->selected_node == -1) ? rnd->opt->highlighted_node : rnd->opt->selected_node;
	s1 = rnd->data->songs[node_num];
	s2 = (rnd->opt->highlighted_node > -1 && rnd->opt->highlighted_node != node_num) ? rnd->data->songs[rnd->opt->highlighted_node] : 0;
	if (s->num == s1->num)
	{
		draw_stat(rnd, x, y, s, 0, 1, s->acousticness, (s2 != 0 && s2->acousticness > s->acousticness) ? 0xff0000 : 0x22ee00);
		draw_stat(rnd, x, y + 25, s, 0, 1, s->danceability, (s2 != 0 && s2->danceability > s->danceability) ? 0xff0000 : 0x22ee00);
		draw_stat(rnd, x, y + 50, s, 0, 1, s->energy, (s2 != 0 && s2->energy > s->energy) ? 0xff0000 : 0x22ee00);
		draw_stat(rnd, x, y + 75, s, 0, 1, s->instrumentalness, (s2 != 0 && s2->instrumentalness > s->instrumentalness) ? 0xff0000 : 0x22ee00);
		draw_stat(rnd, x, y + 100, s, -60, 0, s->loudness, (s2 != 0 && s2->loudness > s->loudness) ? 0xff0000 : 0x22ee00);
		draw_stat(rnd, x, y + 125, s, 0, 1, s->speechiness, (s2 != 0 && s2->speechiness > s->speechiness) ? 0xff0000 : 0x22ee00);
		draw_stat(rnd, x, y + 150, s, 60, 200, s->tempo, (s2 != 0 && s2->tempo > s->tempo) ? 0xff0000 : 0x22ee00);
		draw_stat(rnd, x, y + 175, s, 0, 1, s->valence, (s2 != 0 && s2->valence > s->valence) ? 0xff0000 : 0x22ee00);
	}
	else
	{
		draw_stat(rnd, x, y, s, 0, 1, s->acousticness, (s->acousticness < s1->acousticness) ? 0xff0000 : 0x22ee00);
		draw_stat(rnd, x, y + 25, s, 0, 1, s->danceability, (s->danceability < s1->danceability) ? 0xff0000 : 0x22ee00);
		draw_stat(rnd, x, y + 50, s, 0, 1, s->energy, (s->energy < s1->energy) ? 0xff0000 : 0x22ee00);
		draw_stat(rnd, x, y + 75, s, 0, 1, s->instrumentalness, (s->instrumentalness < s->instrumentalness) ? 0xff0000 : 0x22ee00);
		draw_stat(rnd, x, y + 100, s, -60, 0, s->loudness, (s->loudness < s1->loudness) ? 0xff0000 : 0x22ee00);
		draw_stat(rnd, x, y + 125, s, 0, 1, s->speechiness, (s->speechiness < s1->speechiness) ? 0xff0000 : 0x22ee00);
		draw_stat(rnd, x, y + 150, s, 60, 200, s->tempo, (s->tempo < s1->tempo) ? 0xff0000 : 0x22ee00);
		draw_stat(rnd, x, y + 175, s, 0, 1, s->valence, (s->valence < s1->valence) ? 0xff0000 : 0x22ee00);
	}
}

void			draw_tabs(t_rnd *rnd)
{
	draw_rectangle(rnd->img, rnd->btn->settings.x, rnd->btn->settings.y, SIDEBAR_LEN / 4.5, 20, 0x999999);
	draw_rectangle(rnd->img, rnd->btn->songs.x, rnd->btn->songs.y, SIDEBAR_LEN / 6, 20, 0x999999);
	draw_rectangle(rnd->img, rnd->btn->user.x, rnd->btn->user.y, SIDEBAR_LEN / 6, 20, 0x999999);
}

void			draw_song_template(t_rnd *rnd, int x, int y)
{
	mlx_string_put(rnd->mlx, rnd->win, x, y, 0x999999, "Song: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 50, 0x999999, "Album: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 100, 0x999999, "Artist: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 160, 0x999999, "A: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 185, 0x999999, "D: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 210, 0x999999, "E: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 235, 0x999999, "I: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 260, 0x999999, "L: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 285, 0x999999, "S: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 310, 0x999999, "T: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 335, 0x999999, "V: ");
}

void			draw_song_info(t_rnd *rnd, t_song *s, int x, int y)
{
	int			bar_width;

	mlx_string_put(rnd->mlx, rnd->win, x, y, 0xffffff, s->title);
	mlx_string_put(rnd->mlx, rnd->win, x, y + 50, 0xffffff, s->album);
	mlx_string_put(rnd->mlx, rnd->win, x, y +100, 0xffffff, s->artist);
	bar_width = STAT_WID * s->stat_scale * s->acousticness;
	mlx_string_put(rnd->mlx, rnd->win, x + bar_width + 10, y + 135, 0xffffff, ft_itoa((int)(s->acousticness * 100)));
	bar_width = STAT_WID * s->stat_scale * s->danceability;
	mlx_string_put(rnd->mlx, rnd->win, x + bar_width + 10, y + 160, 0xffffff, ft_itoa((int)(s->danceability * 100)));
	bar_width = STAT_WID * s->stat_scale * s->energy;
	mlx_string_put(rnd->mlx, rnd->win, x + bar_width + 10, y + 185, 0xffffff, ft_itoa((int)(s->energy * 100)));
	bar_width = STAT_WID * s->stat_scale * s->instrumentalness;
	mlx_string_put(rnd->mlx, rnd->win, x + bar_width + 10, y + 210, 0xffffff, ft_itoa((int)(s->instrumentalness * 100)));
	bar_width = STAT_WID * s->stat_scale * (s->loudness + 60) / 60;
	mlx_string_put(rnd->mlx, rnd->win, x + bar_width + 10, y + 235, 0xffffff, ft_itoa((int)(s->loudness)));
	bar_width = STAT_WID * s->stat_scale * s->speechiness;
	mlx_string_put(rnd->mlx, rnd->win, x + bar_width + 10, y + 260, 0xffffff, ft_itoa((int)(s->speechiness * 100)));
	bar_width = STAT_WID * s->stat_scale * (s->tempo - 60) / 140;
	mlx_string_put(rnd->mlx, rnd->win, x + ((bar_width > 0) ? bar_width : 0) + 10, y + 285, 0xffffff, ft_itoa(s->tempo));
	bar_width = STAT_WID * s->stat_scale * s->valence;
	mlx_string_put(rnd->mlx, rnd->win, x + bar_width + 10, y + 310, 0xffffff, ft_itoa((int)(s->valence * 100)));
}

void			draw_user_summaries(t_rnd *rnd, int x, int y)
{
	if (rnd->user->acousticness > 0.5)
		mlx_string_put(rnd->mlx, rnd->win, x - 10, y + 55, 0xffffff, "You seem to prefer acoustic songs.");
	else
	{
		mlx_string_put(rnd->mlx, rnd->win, x - 10, y + 55, 0xffffff, "You seem to prefer non-acoustic");
		mlx_string_put(rnd->mlx, rnd->win, x, y + 75, 0xffffff, "songs.");
	}
	if (rnd->user->danceability > 0.5)
	{
		mlx_string_put(rnd->mlx, rnd->win, x - 10, y + 155, 0xffffff, "You seem to prefer rythmic songs");
		mlx_string_put(rnd->mlx, rnd->win, x, y + 175, 0xffffff, "with strong beats");
	}
	else
	{
		mlx_string_put(rnd->mlx, rnd->win, x - 10, y + 155, 0xffffff, "You seem to prefer songs with");
		mlx_string_put(rnd->mlx, rnd->win, x, y + 175, 0xffffff, "with vague rhythms or beats.");
	}
	if (rnd->user->energy > 0.5)
	{
		mlx_string_put(rnd->mlx, rnd->win, x - 10, y + 255, 0xffffff, "You seem to prefer songs that are");
		mlx_string_put(rnd->mlx, rnd->win, x, y + 275, 0xffffff, "intense, fast, and loud.");
	}
	else
	{
		mlx_string_put(rnd->mlx, rnd->win, x - 10, y + 255, 0xffffff, "You seem to prefer songs that are");
		mlx_string_put(rnd->mlx, rnd->win, x, y + 275, 0xffffff, "calm, slow, and quiet.");
	}
	if (rnd->user->instrumentalness > 0.5)
	{
		mlx_string_put(rnd->mlx, rnd->win, x - 10, y + 355, 0xffffff, "You seem to prefer instrumental");
		mlx_string_put(rnd->mlx, rnd->win, x, y + 375, 0xffffff, "songs.");
	}
	else
	{
		mlx_string_put(rnd->mlx, rnd->win, x - 10, y + 355, 0xffffff, "You seem to prefer songs that");
		mlx_string_put(rnd->mlx, rnd->win, x, y + 375, 0xffffff, "feature vocals.");
	}
	if (rnd->user->loudness > -30)
		mlx_string_put(rnd->mlx, rnd->win, x - 10, y + 455, 0xffffff, "You seem to prefer louder songs.");
	else
		mlx_string_put(rnd->mlx, rnd->win, x - 10, y + 455, 0xffffff, "You seem to prefer softer songs.");
	if (rnd->user->speechiness > 0.5)
	{
		mlx_string_put(rnd->mlx, rnd->win, x - 10, y + 555, 0xffffff, "You seem to prefer tracks focused");
		mlx_string_put(rnd->mlx, rnd->win, x, y + 575, 0xffffff, "on vocal performance.");
	}
	else
	{
		mlx_string_put(rnd->mlx, rnd->win, x - 10, y + 555, 0xffffff, "You seem to prefer tracks that");
		mlx_string_put(rnd->mlx, rnd->win, x, y + 575, 0xffffff, "feature instruments.");
	}
	if (rnd->user->tempo > 140)
	{
		mlx_string_put(rnd->mlx, rnd->win, x - 10, y + 655, 0xffffff, "You seem to prefer songs with");
		mlx_string_put(rnd->mlx, rnd->win, x, y + 675, 0xffffff, "a faster pace.");
	}
	else
	{
		mlx_string_put(rnd->mlx, rnd->win, x - 10, y + 655, 0xffffff, "You seem to prefer songs with");
		mlx_string_put(rnd->mlx, rnd->win, x, y + 675, 0xffffff, "a slower pace.");
	}
	if (rnd->user->valence > 0.5)
	{
		mlx_string_put(rnd->mlx, rnd->win, x - 10, y + 755, 0xffffff, "You seem to prefer happier,");
		mlx_string_put(rnd->mlx, rnd->win, x, y + 775, 0xffffff, "upbeat songs.");
	}
	else
	{
		mlx_string_put(rnd->mlx, rnd->win, x - 10, y + 755, 0xffffff, "You seem to prefer sad");
		mlx_string_put(rnd->mlx, rnd->win, x, y + 775, 0xffffff, "or angry songs.");
	}
}

void			draw_user_info(t_rnd *rnd, int x, int y)
{
	int			bar_width;

	mlx_string_put(rnd->mlx, rnd->win, x, y, 0x999999, "Averages: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 25, 0x999999, "A: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 125, 0x999999, "D: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 225, 0x999999, "E: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 325, 0x999999, "I: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 425, 0x999999, "L: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 525, 0x999999, "S: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 625, 0x999999, "T: ");
	mlx_string_put(rnd->mlx, rnd->win, x, y + 725, 0x999999, "V: ");
	bar_width = STAT_WID * rnd->user->stat_scale * rnd->user->acousticness;
	mlx_string_put(rnd->mlx, rnd->win, x + bar_width + 30, y + 25, 0xffffff, ft_itoa((int)(rnd->user->acousticness * 100)));
	bar_width = STAT_WID * rnd->user->stat_scale * rnd->user->danceability;
	mlx_string_put(rnd->mlx, rnd->win, x + bar_width + 30, y + 125, 0xffffff, ft_itoa((int)(rnd->user->danceability * 100)));
	bar_width = STAT_WID * rnd->user->stat_scale * rnd->user->energy;
	mlx_string_put(rnd->mlx, rnd->win, x + bar_width + 30, y + 225, 0xffffff, ft_itoa((int)(rnd->user->energy * 100)));
	bar_width = STAT_WID * rnd->user->stat_scale * rnd->user->instrumentalness;
	mlx_string_put(rnd->mlx, rnd->win, x + bar_width + 30, y + 325, 0xffffff, ft_itoa((int)(rnd->user->instrumentalness * 100)));
	bar_width = STAT_WID * rnd->user->stat_scale * (rnd->user->loudness + 60) / 60;
	mlx_string_put(rnd->mlx, rnd->win, x + bar_width + 30, y + 425, 0xffffff, ft_itoa((int)(rnd->user->loudness)));
	bar_width = STAT_WID * rnd->user->stat_scale * rnd->user->speechiness;
	mlx_string_put(rnd->mlx, rnd->win, x + bar_width + 30, y + 525, 0xffffff, ft_itoa((int)(rnd->user->speechiness * 100)));
	bar_width = STAT_WID * rnd->user->stat_scale * (rnd->user->tempo - 60) / 140;
	mlx_string_put(rnd->mlx, rnd->win, x + bar_width + 30, y + 625, 0xffffff, ft_itoa(rnd->user->tempo));
	bar_width = STAT_WID * rnd->user->stat_scale * rnd->user->valence;
	mlx_string_put(rnd->mlx, rnd->win, x + bar_width + 30, y + 725, 0xffffff, ft_itoa((int)(rnd->user->valence * 100)));
	draw_user_summaries(rnd, x, y);
}

void			draw_sidebar(t_rnd *rnd)
{
	int		x;
	int		y;
	int		node_num;

	node_num = (rnd->opt->selected_node == -1) ? rnd->opt->highlighted_node : rnd->opt->selected_node;
	y = 0;
	while (y < LEN)
	{
			x = WID - SIDEBAR_LEN;
			while (x < WID)
				img_pixel_put(rnd->img, x++, y, 0x373737);
			y++;
	}
	draw_tabs(rnd);
	if (rnd->opt->sidebar_mode == 0)
		draw_buttons(rnd);
	else if (rnd->opt->sidebar_mode == 1)
	{
		if (node_num != -1)
			draw_stats(rnd, rnd->data->songs[node_num], WID - SIDEBAR_LEN + 30, 200);
		if (rnd->opt->highlighted_node != -1 && rnd->opt->highlighted_node != node_num)
			draw_stats(rnd, rnd->data->songs[rnd->opt->highlighted_node], WID - SIDEBAR_LEN + 30, 565);
	}
	draw_user_stats(rnd, WID - SIDEBAR_LEN + 45, 70);
}

void		draw_text(t_rnd *rnd)
{
	int		node_num;

	node_num = (rnd->opt->selected_node == -1) ? rnd->opt->highlighted_node : rnd->opt->selected_node;
	mlx_string_put(rnd->mlx, rnd->win, rnd->btn->settings.x, 4, 0xffffff, "Settings");
	mlx_string_put(rnd->mlx, rnd->win, rnd->btn->songs.x + 5, 4, 0xffffff, "Songs");
	mlx_string_put(rnd->mlx, rnd->win, rnd->btn->user.x + 11, 4, 0xffffff, "User");
	if (rnd->opt->sidebar_mode == 0)
	{
		mlx_string_put(rnd->mlx, rnd->win, rnd->btn->grad_up.x - BUTTON_RAD + 6, rnd->btn->grad_up.y - BUTTON_RAD - 1, 0xffffff, "+");
		mlx_string_put(rnd->mlx, rnd->win, rnd->btn->grad_down.x - BUTTON_RAD + 6, rnd->btn->grad_down.y - BUTTON_RAD - 1, 0xffffff, "-");
		mlx_string_put(rnd->mlx, rnd->win, rnd->btn->grad_up.x + 20, rnd->btn->grad_up.y, 0x999999, "Graph Size:");
		mlx_string_put(rnd->mlx, rnd->win, rnd->btn->grad_up.x + 130, rnd->btn->grad_up.y, 0xffffff, ft_itoa(rnd->opt->graph_rad));
		mlx_string_put(rnd->mlx, rnd->win, rnd->btn->nrad_up.x - BUTTON_RAD + 6, rnd->btn->nrad_up.y - BUTTON_RAD - 1, 0xffffff, "+");
		mlx_string_put(rnd->mlx, rnd->win, rnd->btn->nrad_down.x - BUTTON_RAD + 6, rnd->btn->nrad_down.y - BUTTON_RAD - 1, 0xffffff, "-");
		mlx_string_put(rnd->mlx, rnd->win, rnd->btn->nrad_up.x + 20, rnd->btn->nrad_up.y, 0x999999, "Song Size:");
		mlx_string_put(rnd->mlx, rnd->win, rnd->btn->nrad_up.x + 120, rnd->btn->nrad_up.y, 0xffffff, ft_itoa(rnd->opt->node_rad));
		mlx_string_put(rnd->mlx, rnd->win, rnd->btn->thresh_up.x - BUTTON_RAD + 6, rnd->btn->thresh_up.y - BUTTON_RAD - 1, 0xffffff, "+");
		mlx_string_put(rnd->mlx, rnd->win, rnd->btn->thresh_down.x - BUTTON_RAD + 6, rnd->btn->thresh_down.y - BUTTON_RAD - 1, 0xffffff, "-");
		mlx_string_put(rnd->mlx, rnd->win, rnd->btn->thresh_up.x + 20, rnd->btn->thresh_up.y, 0x999999, "Connections Threshold:");
		mlx_string_put(rnd->mlx, rnd->win, rnd->btn->thresh_up.x + 240, rnd->btn->thresh_up.y, 0xffffff, ft_itoa(rnd->opt->threshold));
	}
	else if (rnd->opt->sidebar_mode == 1)
	{
		draw_song_template(rnd, WID - SIDEBAR_LEN + 10, 35);
		if (node_num > -1)
			draw_song_info(rnd, rnd->data->songs[node_num], WID - SIDEBAR_LEN + 25, 60);
		if (rnd->opt->highlighted_node > -1 && rnd->opt->highlighted_node != node_num)
		{
			draw_song_template(rnd, WID - SIDEBAR_LEN + 10, 400);
			draw_song_info(rnd, rnd->data->songs[rnd->opt->highlighted_node], WID - SIDEBAR_LEN + 25, 425);
		}
	}
	else if (rnd->opt->sidebar_mode == 2)
		draw_user_info(rnd, WID - SIDEBAR_LEN + 20, 40);
}