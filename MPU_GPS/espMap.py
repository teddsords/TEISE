#%%
import gmaps
import gmaps.datasets
import gmplot
import webbrowser

import time
import firebase_admin
from firebase_admin import db

db_obj = firebase_admin.credentials.Certificate('./esp32-and-gps-module-firebase-adminsdk-mzmty-20d911a17b.json')
default_app = firebase_admin.initialize_app(db_obj, {'databaseURL':'https://esp32-and-gps-module-default-rtdb.firebaseio.com/'})

refLat = db.reference('/lat')
refLng = db.reference('/lng')
refTmp = db.reference('/tmp')

location = (refLat.get(), refLng.get())
tmp = refTmp.get()
print(location)
print(tmp)

#gmaps.configure(api_key='AIzaSyDFsH7PPTsSYVfRDFmgETPKimmeg6TSLk0') 
#fig = gmaps.figure(center=location, zoom_level = 12, map_type= 'HYBRID')
#fig

map = gmplot.GoogleMapPlotter(refLat.get(), refLng.get(), 12)
map.apikey = 'AIzaSyDFsH7PPTsSYVfRDFmgETPKimmeg6TSLk0'
map.marker(refLat.get(), refLng.get(), color='cornflowerblue', label="Temperatura: " + str(tmp))
map.draw("mapa.html")
webbrowser.open("mapa.html")

print("Terminou o programa")
# %%
