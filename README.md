# Smart_Irrigation_System

AIM : To design a smart irrigation system for efficient use of supply water

Components and technologies used : C++, ESP32, ac motor, solenoid valves, soil moisture sensor, ac and dc power supply

The sample land is divided into different plots and every plot contains a soil moisture sensor. It reads the moisture level of each plot and feeds it to the ESP32.
when the water level of a certain plot falls below the set threshold value, the ac motor is turned on and a solenoid valve that is connected to the pipe of that 
perticular plot is turned on and water reaches only to that plot. When the water level reaches the threshold value again the motor turns off and the process continues.

All the readings from the moisture sensor is sent to the cloud every 5 seconds. This data is shown in a dashbord in the form of a graph representing the water level
of each plot throughout the day. Also, a different graph is made for the turning ON/OFF of the motor.

Every activity of each of the sensor can be seen in the dashbord.
