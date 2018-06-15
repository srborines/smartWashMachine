# SmartWashMachine

This is project a project to do that a washer machine notifies you by email when it finish.

## Architecture

To this project is neccessary a ESP8266 device with wifi, a LDR, a button and a server where to run the php script.

## How to build the hardware

The componets used in this projects has an easy way to connect. The device was stored inside a plastic box and the LDR inside a black paperboard box to avoid the external light.

## How to configurate the software

In the top of the arduino script you can select the pinout to the buttom, led and LDR and you also can change the secretKey. In the top of the php script you should modify the gmail username and password and also there you can modify the secretKey. Important both secretKey (arduino script and php script) must be the same.


<p align="center">
  <img src="https://i.imgur.com/1EUDboG.jpg" width="350"/>
  <img src="https://i.imgur.com/DEu5k6Z.jpg" width="350"/>
</p>

<p align="center">
  <img src="https://i.imgur.com/KJl4omt.jpg" width="350"/>
  <img src="https://i.imgur.com/ZM7miCV.jpg" width="350"/>
</p>

## ESP script

Arduino script change the status of the device depends of the button and the LDR. It will show how is the status with the led, this is the led code:
* **Turned off:** The device is disarmed or off.
* **Blinking slow:** The device is armed waiting for the light LDR event.
* **Blinking fast:** Armed status has been canceled pressing the button. Unpluging the button the device will come back to disarmed status.
* **Turned on:** The device detedted the event from the LDR. Pressing the button the device will come back to disarmed status.

## PHP script

The php script has a secketKey that is shared also with the arduino script, when this php script receive a request with the right secretKey it will notify you by email.

## How to use

By the default the arduino script starts in 'desarmed' mode so you haave to click to activate. When you active the device the led will start to blink, when the LDR detects light it notify the server which will send an email to your account and the led will be on. To come back to the desarmed status you can press the button and the led will turn off. If when the device is armed you want to cancel it you just have to press the button until it start to blink faster.