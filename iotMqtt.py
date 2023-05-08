# MQTT Client demo
# Continuously monitor two different MQTT topics for data,
# check if the received data matches two predefined 'commands'
import serial 
import time
import paho.mqtt.publish as publish
import paho.mqtt.client as mqtt

XBee = serial.Serial('/dev/ttyUSB0',9600)


 
# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
 
    # Subscribing in on_connect() - if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("smartWater/motor1")
    client.subscribe("smartWater/motor2")

# funciones de los motores
    
def read_sensor(motor):
    identidad=str(motor)
    XBee.write(identidad+",2*")
    return

    
def activar_motor(motor):
    identidad=str(motor)
    XBee.write(identidad+",1*")
    return

def desactivar_motor(motor):
    identidad=str(motor)
    XBee.write(identidad+",0*")
    return
    


 
# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

    if msg.topic == "smartWater/motor1" and msg.payload == "1":
        print("Activar motor 1")
        activar_motor(1)
        
    if msg.topic == "smartWater/motor1" and msg.payload == "0":
        print("Desactivar motor 1")
        desactivar_motor(1)

    if msg.topic == "smartWater/motor2" and msg.payload == "1":
        print("Activar motor 2")
        activar_motor(2)

    if msg.topic == "smartWater/motor2" and msg.payload == "0":
        print("Desactivar motor 2")
        desactivar_motor(2)
 
# Create an MQTT client and attach our routines to it.
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
 
 
#client.username_pw_set("tjsospya","9ZViYic1BYWE") 
#client.connect("test.mosquitto.org", 1883, 60)
client.connect("broker.hivemq.com", 1883, 60)
# Process network traffic and dispatch callbacks. This will also handle
# reconnecting. Check the documentation at
# https://github.com/eclipse/paho.mqtt.python
# for information on how to use other loop*() functions
client.loop_start()
while True:
	#client.publish("CoreElectronics/test", "Hello")
    #publish.single("CoreElectronics/topic", "World!", hostname="broker.hivemq.com")
	
	time.sleep(4)
	read_sensor(1)
	print("se envio peticion 1")
	lectura1=XBee.readline()
	print("Sensor1 "+lectura1)
	client.publish("smartWater/Sensor1", lectura1)
	
	read_sensor(2)
	print("se envio peticion2")
	lectura2=XBee.readline()
	print("Sensor2 "+lectura2)
	client.publish("smartWater/Sensor2", lectura2)
	
	
	diferencia=float(lectura1)-float(lectura2)
	
	if diferencia>0.4:
		print("Alerta de fuga")
		client.publish("smartWater/Alerta", "Alerta de fuga")
	else:
		print("Todo en orden")
		client.publish("smartWater/Alerta", "todo en orden")	
	time.sleep(10)
	
client.loop_stop()
	
#client.loop_forever()
