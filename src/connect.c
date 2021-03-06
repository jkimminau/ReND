#include <rnd.h>

int		are_similar(double stat1, double stat2, double threshold)
{
	if (fabs(stat2 - stat1) > threshold)
		return (0);
	else
		return (1);
	return (0);
}

int		songcmp(t_song *s1, t_song *s2)
{
	int		similarities;

	similarities = 0;
	similarities += are_similar(s1->acousticness, s2->acousticness, 0.2);
	similarities += are_similar(s1->danceability, s2->danceability, 0.2);
	similarities += are_similar(s1->energy, s2->energy, 0.2);
	similarities += are_similar(s1->instrumentalness, s2->instrumentalness, 0.2);
	similarities += are_similar(s1->loudness, s2->loudness, 10);
	similarities += are_similar(s1->speechiness, s2->speechiness, 0.2);
	similarities += are_similar(s1->tempo, s2->tempo, 20);
	similarities += are_similar(s1->valence, s2->valence, 0.2);
	return (similarities);
}

void	create_connections(t_rnd *rnd)
{
	int		i;
	int		j;
	int		num_connects;
	int		similarities;

	num_connects = 0;
	i = 0;
	while (i < rnd->data->num_songs - 1)
	{
		j = i + 1;
		while (j < rnd->data->num_songs)
		{
			num_connects++;
			j++;
		}
			//num_connects += songcmp(rnd->data->songs[i], rnd->data->songs[j++]) > CONNECTION_THRESHOLD;
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
			//OLD METHOD
			//if ((similarities = songcmp(rnd->data->songs[i], rnd->data->songs[j])) > CONNECTION_THRESHOLD)
			similarities = songcmp(rnd->data->songs[i], rnd->data->songs[j]);
			rnd->data->connections[num_connects++] = init_connection(rnd->data->songs[i], rnd->data->songs[j], similarities);
			j++;
		}
		i++;
	}
}