import paho.mqtt.client as mqtt
import os
import json
import time
from datetime import datetime
import seeed_dht

broker=""
topic="seproject"
port=1883

def on_publish(client,userdata,result): #create function for callback
  print("published data is : ")
  pass

client1= mqtt.Client("control1")
client1.on_publish = on_publish
client1.connect(broker,port,keepalive=60)
sensor= seeed_dht.DHT("11",12)
#publishing after every 5 secs
while True:
    humidity, temp= sensor.read()
    payload= temp
    ret= client1.publish(topic,payload)
    print(payload)
    time.sleep(5)