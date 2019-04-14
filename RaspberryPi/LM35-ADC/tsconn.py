import random
import string
import requests
import paho.mqtt.publish as publish


class ThingSpeakConnector:
    def __init__(self, api_key, mqtt_api_key=None):
        self.sess = requests.Session()
        self.client_id = ''.join(random.sample(string.ascii_lowercase, 16)) 
        self.api_key = api_key
        self.mqtt_api_key = mqtt_api_key

    def send(self, temperature, keep_alive=False):
        if keep_alive:
            req = requests.Request('POST', 'https://api.thingspeak.com/update.json',
                data = {
                'api_key': self.api_key,
                'field1': temperature
                })
            prepped = req.prepare()
            rsp = self.sess.send(prepped)
        else:
            rsp = requests.post('https://api.thingspeak.com/update.json',
                data = {
                'api_key': self.api_key,
                'field1': temperature
                })

        if rsp.status_code != 200:
            print("Error: Unable to send to ThingSpeak cloud; status code {}".format(rsp.status_code))

    def send_mqtt(self, channel_id, temperature):
        try:
            topic = "channels/{}/publish/{}".format(channel_id, self.api_key)
            payload = "field1={}".format(temperature)
            publish.single(topic, payload, hostname='mqtt.thingspeak.com', transport='websockets', port=80,auth={'username':'devopedia','password':self.mqtt_api_key})
        except Exception as e:
            print("Error: Unable to send to ThingSpeak cloud; error {}".format(e))
