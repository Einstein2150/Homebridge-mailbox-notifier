# Homebridge mailbox notifier


## Parts

* ESP8266 (model of your choise)
* 1 Ballswitch
* 2AA-Battery-Pack (3 Volt)


## Wiring

* Batterypack + to VCC (not VIN)
* Batterypack - to GND
* GPIO16 to RST (Reset)
* Ballswitch to RST and GND


## Communication with Homebridge

You need the webhook-plugin in Homebridge: [https://www.npmjs.com/package/homebridge-http-webhooks]()

Define the config and set the URL in the ino-Code to the webhook-destination.

Here ist a example-json for homebridge:



```
		{
            "platform": "HttpWebHooks",
            "webhook_port": "8888",
            "cache_directory": "./.node-persist/storage",
            "sensors": [
                {
                    "id": "sensor1",
                    "name": "Bewegung",
                    "type": "motion",
                    "autoRelease": true
                }
            ]
 		} 
```     
## Config in Home-App

Go to the Settings of the new Sensor and activate the status and notification. Activate the notification and enable push-notifications. For tryout leave the persons off and the time to everytime.

## Config in ino-Code

Look at this two lines. One is for your wifi-config:
`  WiFi.begin("SSID", "PASSWORD");`

The other one is for the webhook as described above:
`http.begin("http://HOMEBRIDGE-IP:WEBHOOKPORT/?accessoryId=sensor1&state=true");`

## Flash the ESP and finetuning

Flash the ESP. If you have a nodeMCU-Board it will be very simple. Check out this video for the correct wiring:
[https://www.youtube.com/watch?v=zwp9E37ioVw]()

If you are using a ESP-01 you have to hardware-hack it for deepsleep wakeup like here:
[https://www.instructables.com/id/Enable-DeepSleep-on-an-ESP8266-01/]()

To save energy cut every existing smd-led on the ESP-Board 🔪 (yes - destroy it 😅)
