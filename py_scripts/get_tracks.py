import spotipy
import spotipy.util as util
import json
from spotipy.oauth2 import SpotifyClientCredentials
import wikipedia

# CLEAN JSON PRINT
#print(json.dumps(JSON, sort_keys=True, indent=4, separators=(',', ': ')))

user_id ='1225066737'
#user_id ='21ugwl7ayvs2tifld27pmls7y'
scope = 'user-top-read user-read-recently-played' 
token = util.prompt_for_user_token(user_id, scope, redirect_uri='https://example.com/callback')
sp = spotipy.Spotify(auth=token)
sp.trace = False

recents = sp.current_user_recently_played(limit=50)

tracks = []
for item in recents['items']:
	tracks.append({
		'name': item['track']['name'],
		'artist': item['track']['artists'][0]['name'],
		'album': item['track']['album']['name'],
		'id': item['track']['id']
		})

id_list = []
for track in tracks:
	id_list.append(track['id'])

features_list = sp.audio_features(id_list)
for feature in features_list:
	for track in tracks:
		if track['id'] == feature['id']:
			track['acousticness'] = feature['acousticness']
			track['danceability'] = feature['danceability']
			track['energy'] = feature['energy']
			track['loudness'] = feature['loudness']
			track['speechiness'] = feature['speechiness']
			track['tempo'] = feature['tempo']
			track['valence'] = feature['valence']

file = open('data.txt', 'w')
for track in tracks:
	file.write("\"" + track['name'] + "\" ")
	file.write("\"" + track['artist'] + "\" ")
	file.write("\"" + track['album'] + "\" ")
	file.write("\"" + str(track['acousticness']) + "\" ")
	file.write("\"" + str(track['danceability']) + "\" ")
	file.write("\"" + str(track['energy']) + "\" ")
	file.write("\"" + str(track['loudness']) + "\" ")
	file.write("\"" + str(track['speechiness']) + "\" ")
	file.write("\"" + str(track['tempo']) + "\" ")
	file.write("\"" + str(track['valence']) + "\"\n")