import serial
from datetime import datetime
import numpy
import matplotlib.pyplot as pyplot
from drawnow import *
#
# Note 1: This python script was designed to run with Python 3.
#
# Note 2: The script uses "pyserial" which must be installed.  If you have
#         previously installed the "serial" package, it must be uninstalled
#         first.
#
# Note 3: While this script is running you can not re-program the Arduino.
#         Before downloading a new Arduino sketch, you must exit this
#         script first.
#


#
# Set the name of the serial port.  Determine the name as follows:
#	1) From Arduino's "Tools" menu, select "Port"
#	2) It will show you which Port is used to connect to the Arduino
#
# For Windows computers, the name is formatted like: "COM6"
# For Apple computers, the name is formatted like: "/dev/tty.usbmodemfa141"
#
arduinoComPort = "/dev/ttyACM0"
currentcounter = 0
previouscounter = 0




#
# Set the baud rate
# NOTE1: The baudRate for the sending and receiving programs must be the same!
# NOTE2: For faster communication, set the baudRate to 115200 below
#        and check that the arduino sketch you are using is updated as well.
#
baudRate = 9600


#
# open the serial port
#
arduinoData = serial.Serial(arduinoComPort, baudRate, timeout = 10.0)

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
#Calculate and store data in both inches and centimeters
# Calculate distance in CM
# distancecm = -0.0000196*pow(arduinoData,3) + 0.0251*pow(arduinoData,2) - 7.3743*arduinoData + 678.303
# # Write data to file
# path = "distcmdata.txt" % (str(datetime.now()),distancecm)
# sercm = serial.Serial(distancecm,baudRate)
# with open(path,'wt') as f:
#     while True:
#         linecm = sercm.readline()
#         f.writelines([linecm.strip(),"t= %s \n" %(datetime.now())])


#Calculate distance in IN
#distancein = 4192.936 * pow(arduinoData,-0.935) - 3.93
# Write data to file
#path = "distindata.txt" % (str(datetime.now()),distancein)
#serin = serial.Serial(distancein,baudRate)
#with open(path,'wt') as f:
#    while True:
#        linein = serin.readline()
#        f.writelines([linein.strip(),"t= %s \n" %(datetime.now())])
# def makefig():
#     plt.title('Visualization')
#     plt.grid(True)
#     plt.plot(servo1,servo2, 'ro')

#//////////////////////////////////////////////////////////////////////////////
#Store raw data
def string_to_float(number):
    if type(number) == float:
        return number
    else:
        results = ''
        # for character in number:
            # if not character == ',':
                # results += character
        return float(results)

while True:

    while (arduinoData.inWaiting()==0): #Wait here until there is data
        pass
  #
  # ask for a line of data from the serial port, the ".decode()" converts the
  # data from an "array of bytes", to a string
  #
    arduinoString = arduinoData.readline()
    #string_to_float(arduinoString)
    dataArray = arduinoString.split()
    # int(str(arduinoString))
    print(type(len(dataArray)))
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
    print(servo1, servo2, distance)
      # if(cnt>50):
      #     servo1.pop(0)
      #     servo2.pop(0)


  # check if data was recieved
  # if len(arduinoString) > 0:
  #   currentcounter = previouscounter + 1
  # if currentcounter > previouscounter:
  #   previouscounter = currentcounter
  #   # write data to file
  #   path = "datalog.txt" % (str(datetime.now()),sensor);
  #   ser = serial.Serial(arduinoData,baudrate)
  #   with open(path,'wt') as f:
  #   	while True:
  #   		line = ser.readline()
  #   		f.writelines([line.strip(),"t= %s \n" %(datetime.now())])
