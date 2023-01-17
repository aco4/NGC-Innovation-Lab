# https://github.com/slawomirkorbas/robotics/blob/main/python_jetson/serial_comm.py

import serial 
import time

#arduino = serial.Serial('/dev/ttyACM0', 115200, timeout=5)

arduino = serial.Serial(
port = '/dev/ttyACM0',
baudrate = 115200,
bytesize = serial.EIGHTBITS, 
parity = serial.PARITY_NONE,
stopbits = serial.STOPBITS_ONE, 
timeout = 5,
xonxoff = False,
rtscts = False,
dsrdtr = False,
writeTimeout = 2
)

def sendCommand(command):
    TERMINATOR = '|'
    arduino.write((command + TERMINATOR).encode())

def startCollection():
    sendCommand("start collection")

def stopCollection():
    sendCommand("stop collection")

# When receiving data from the Arduino, it is returned in encoded format: b' the_values_that_i_want'
# This removes the outer encoding
def decodeArduinoData(data):
    return data.decode("utf-8")

while True:
    try:
        sendCommand("Command from Jetson")
        data = arduino.readline()
        if data:
            print(data) # print received data from arduino to console
        time.sleep(1)
    except Exception as e:
        print(e)
        arduino.close()