# Proyecto-DiploIoT
<h1> HOME WATER FLOW MONITORING SYSTEM BASED ON IOT </h1>
<p>
This repository contains the description and scripts implemented for the development of a prototype device for monitoring water flow based on the Internet of things. The system prototype has two main elements, a GATEWAY NODE and a SENSOR NODE. The GATEWAY NODE is in charge of collecting the information from the SENSOR NODES and through its Ethernet port it is in charge of sending the information through the MQTT protocol to a defined broker. It also proposes the implementation of a basic web interface that serves to visualize the status of the sensors, display an alarm in case of a leak in the water network and be able to remotely control the actuators of the network.
</p>

<h2> Working general description </h2>
<p>
The SENSOR NODE is an Arduino (Microcontroller) which is attached to a flow sensor meter and a servomotor (to meassure the water flow rate and control a valve with the servo), additionally the Arduino sends its information trough serial port which is attached to a Xbee. The Xbee sends the information to the GATEWAY NODE. The GATEWAY NODE is a Raspberry pi that reads the information of SENSOR NODES trough another Xbee and its connected to Ethernet to send the information trough MQTT protocol, a general overview can be seen in the following image: 
  
</p>

<img src="https://user-images.githubusercontent.com/11477020/236908173-d27b71bb-c645-4060-b120-bb983d1a7814.PNG">
<p>
  A very simple web interface was developed in order to read the lecture of the sensors and activate or disactivate the servomotors, this interface is:
 </p>
<img src="https://user-images.githubusercontent.com/11477020/236908182-e7086c51-492a-48b3-b2a5-f8612895aaaa.PNG" align="center">
<img src="https://user-images.githubusercontent.com/11477020/236908165-d393fabb-6963-49f4-b735-2c284b8143c4.PNG">


<p> You can run this project using the Raspberry pi, Arduino and HTML Files attached </p>
