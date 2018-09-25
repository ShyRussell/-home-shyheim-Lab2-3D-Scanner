import serial
from datetime import datetime
import numpy as np
import matplotlib.pyplot as plt
from drawnow import *
import time
from mpl_toolkits import mplot3d



arduinoComPort = "/dev/ttyACM0"
currentcounter = 0
previouscounter = 0

baudRate = 9600

# open the serial port
arduinoData = serial.Serial(arduinoComPort, baudRate, timeout = 1.0)
arduinoData.write(b'1')

print(arduinoData)
plt.ion()
cnt = 0
servo1 = []
servo2 =[]
distance = []
#
# main loop to read data from the Arduino, then display it
#
#///////////////////////////////////////////////////////////////////////////////

def makefig():
    plt.title('Visualization')
    plt.grid(True)
    plt.plot(servo1,servo2,distance, 'ro', 'bs', 'go')
    plt.show()

fig = plt.figure()
ax = plt.axes(projection = '3d')


ax.scatter3D(servo1, servo2, distance)
#//////////////////////////////////////////////////////////////////////////////

while True:
    while (arduinoData.inWaiting()==0): #Wait here until there is data
        pass
  #
    arduinoString = arduinoData.readline()
    dataArray = arduinoString.decode().split(',')
    # print(type(dataArray))
    # print(len(dataArray))
    # print(dataArray)
    try:
        s1 = int( dataArray[0])
        s2 = int( dataArray[1])
        sensor = int( dataArray[2])
        dist = 0.0000196*pow(sensor,3) + 0.0251*pow(sensor,2) - 7.3743*sensor + 678.303
        servo1.append(s1)
        servo2.append(s2)
        distance.append(dist)
        if dist < 40:
            drawnow(makefig)
            plt.pause(.000001)
            cnt=cnt+1
    except ValueError:
        pass
