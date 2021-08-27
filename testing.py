#%%
message = 'Hello World!'
print(message)

# %%
import gmaps
import gmaps.datasets

file = open('token.txt', 'r')
api_key = file.readline()


gmaps.configure(api_key)

earthquake_df = gmaps.datasets.load_dataset_as_df('earthquakes')
earthquake_df.head()
# %%
locations = earthquake_df[['latitude', 'longitude']]
weights = earthquake_df['magnitude']

fig = gmaps.figure()
fig.add_layer(gmaps.heatmap_layer(locations, weights = weights))
fig
# %%
gmaps.configure(api_key)

fig = gmaps.figure()
fig
# %%
gmaps.configure(api_key)

fig = gmaps.figure(map_type = 'SATELLITE')

#generate some (latitude, longitude) pairs

locations = [(14.1,  -87.2167), (15.5, -88.0)]
heatmap_layer = gmaps.heatmap_layer(locations)
fig.add_layer(heatmap_layer)
fig

# %%
gmaps.configure(api_key)
new_york_coordinates = (40.75, -74.0)

gmaps.figure(center=new_york_coordinates, zoom_level = 12, map_type = 'TERRAIN')
# %%
tegus_coordinates = (14.1,  -87.2167)
gmaps.figure(center = tegus_coordinates, zoom_level = 12, map_type = 'HYBRID')
# %%
gmaps.marker(tegus_coordinates)
# %%
