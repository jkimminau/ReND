#include <rnd.h>

int		are_similar(double stat1, double stat2, double min, double max)
{
	double	d;

	d = (max - min) / 4;
	if (stat1 < min || stat2 < min)
		return (stat1 < min && stat2 < min ? 1 : 0);
	if (stat1 < min + d * 1 || stat2 < min + d * 1)
		return (stat1 < min + d * 1 && stat2 < min + d * 1);
	if (stat1 < min + d * 2 || stat2 < min + d * 2)
		return (stat1 < min + d * 2 && stat2 < min + d * 2);
	if (stat1 < min + d * 3 || stat2 < min + d * 3)
		return (stat1 < min + d * 3 && stat2 < min + d * 3);
	if (stat1 >= min + d * 3 || stat2 >= min + d * 3)
		return (stat1 >= min + d * 3 && stat2 >= min + d * 3);
	return (0);
}

int		songcmp(t_song *s1, t_song *s2)
{
	int		similarities;

	similarities = 0;
	similarities += are_similar(s1->acousticness, s2->acousticness, 0.2, 1.0);
	similarities += are_similar(s1->danceability, s2->danceability, 0.2, 1.0);
	similarities += are_similar(s1->energy, s2->energy, 0.2, 1.0);
	similarities += are_similar(s1->loudness, s2->loudness, 0.2, 1.0);
	similarities += are_similar(s1->speechiness, s2->speechiness, 0.2, 1.0);
	similarities += are_similar(s1->tempo, s2->tempo, 80, 200);
	similarities += are_similar(s1->valence, s2->valence, 0.2, 1.0);
	return (similarities);
}

void	create_connections(t_rnd *rnd)
{
	int		i;
	int		j;
	int		num_connects;
	double	similarities;

	num_connects = 0;
	i = 0;
	while (i < rnd->data->num_songs - 1)
	{
		j = i + 1;
		while (j < rnd->data->num_songs)
			num_connects += songcmp(rnd->data->songs[i], rnd->data->songs[j++]) > 3;
		i++;
	}
	//printf("found %d connections\n", num_connects);
	rnd->data->connections = (t_connection **)malloc(sizeof(t_connection) * num_connects);
	rnd->data->num_connections = num_connects;
	i = 0;
	num_connects = 0;
	while (i < rnd->data->num_songs - 1)
	{
		j = i + 1;
		while (j < rnd->data->num_songs)
		{
			if ((similarities = songcmp(rnd->data->songs[i], rnd->data->songs[j])) > 3)
				rnd->data->connections[num_connects++] = init_connection(rnd->data->songs[i], rnd->data->songs[j], similarities / FEATURES * 100);
			j++;
		}
		i++;
	}
}