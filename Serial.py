import serial
import requests
import json

API_ENDPOINT = "https://bmgxwpyyd2.execute-api.us-east-1.amazonaws.com/prod/sensordata"

#create new serial object
arduino = serial.Serial('COM3', 9600, timeout=.1)

print("hello")
while True:
    data = arduino.readline()[:-4]

    if data:
        print (data.decode("utf-8")+"}\"}") #change this in arduino code
        postdata = json.loads(data.decode("utf-8")+"}\"}") #change this in arduino code
        r = requests.post(url = API_ENDPOINT, json = postdata)
        print("Data returned =%s"%r.text)