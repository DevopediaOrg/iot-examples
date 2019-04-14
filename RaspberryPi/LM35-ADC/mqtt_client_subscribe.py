import os
import paho.mqtt.subscribe as subscribe

def on_message(client, userdata, msg):
    print(msg.topic, msg.payload)

subscribe.callback(on_message, "channels/758180/subscribe/fields/field1",
    hostname="mqtt.thingspeak.com",
    auth = {'username': "someone", 'password': os.environ['TS_MQTT_API_KEY']})
