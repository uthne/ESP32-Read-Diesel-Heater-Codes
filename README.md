# ESP32-Read-Diesel-Heater-Codes

A simple tool for ESP32 to collect RF-codes from 
a 433.92 MHz Key Fob / remote for a diesel heater, 
using receiver supported by the RCSwitch.h library.

In the test setup a Chinese receiver XLC-RF-5V was used.

On a ESP32-C mini board i recommend using GPIO 4 while on 
a board like ESP32 DevKit C (Wroom) you can use GPIO 16.

Remember that most 433MHz receivers are 5 volt and you
*** MUST USE *** a voltage divider to pull down the voltage.
A 10 kOhm resistor between the DATA pin on the receiver and 
the GPIO pin, and a 20 or 22 kOhm between the GPIO and GND. 
This will give about 3.33 to 3.44 volt on the GPIO.

   ┌──────────┐                         ┌──────────┐
   │ RECEIVER │       10kOhm            │  ESP32   │
   │          │     ┌────────┐          │          │
   │      DATA│─────│        │────+─────│GPIO      │
   │          │     └────────┘    │     │          │
   │          │                   │     │          │
   └──────────┘                 ┌───┐   └──────────┘
                                │   │               
                          22kOhm│   │               
                                │   │               
                                └───┘               
                                  │                 
                                  │                 
                                ##### GND           

SE ALSO ILLUSTRATION schema.svg

Use the Serial Monitor while the ESP32 is connected via USB.
Follow the intructions and press the called out buttons 
on your remote / Key Fob, and copy the list of received
codes from the Serial Monitor.




The Serial Monitor communication will look like this:

	Listening for 433 MHz codes...
	 
	  
	Press ON
	----------------
	Code: 15973236
	Bits: 24
	Protocol: 1
	----------------
	OK
	----------------
	Press OFF
	----------------
	Code: 15973240
	Bits: 24
	Protocol: 1
	----------------
	OK
	----------------
	Press UP
	----------------
	Code: 15973233
	Bits: 24
	Protocol: 1
	----------------
	OK
	----------------
	Press DOWN
	----------------
	Code: 15973234
	Bits: 24
	Protocol: 1
	----------------
	OK
	----------------
	Received codes: 
	ON: 15973236
	OFF: 15973240
	UP: 15973233
	DOWN: 15973234
	----------------
	To start over: 
	Press ON
	----------------
