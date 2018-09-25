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
arduinoComPort = "COM6"
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
serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)

print(serialPort)
plt.ion()
cnt = 0
value = []
#
# main loop to read data from the Arduino, then display it
#
#///////////////////////////////////////////////////////////////////////////////
#Calculate and store data in both inches and centimeters
# Calculate distance in CM
distancecm = -0.0000196*pow(serialPort,3) + 0.0251*pow(serialPort,2) - 7.3743*serialPort + 678.303
# Write data to file
path = "distcmdata.txt" % (str(datetime.now()),distancecm)
sercm = serial.Serial(distancecm,baudRate)
with open(path,'wt') as f:
    while True:
        linecm = sercm.readline()
        f.writelines([linecm.strip(),"t= %s \n" %(datetime.now())])


#Calculate distance in IN
#distancein = 4192.936 * pow(serialPort,-0.935) - 3.93
# Write data to file
#path = "distindata.txt" % (str(datetime.now()),distancein)
#serin = serial.Serial(distancein,baudRate)
#with open(path,'wt') as f:
#    while True:
#        linein = serin.readline()
#        f.writelines([linein.strip(),"t= %s \n" %(datetime.now())])
def makefig():
    plt.title('Visualization')
    plt.grid(True)
    plt.plot(value, 'ro')

#//////////////////////////////////////////////////////////////////////////////
#Store raw data
while True:
  #
  # ask for a line of data from the serial port, the ".decode()" converts the
  # data from an "array of bytes", to a string
  #
  lineOfData = serialPort.readline().decode()
  # check if data was recieved
  if len(lineOfData) > 0:
    currentcounter = previouscounter + 1
  if currentcounter > previouscounter:
    previouscounter = currentcounter
    # write data to file
    path = "datalog.txt" % (str(datetime.now()),sensor);
    ser = serial.Serial(serialport,baudrate)
    with open(path,'wt') as f:
    	while True:
    		line = ser.readline()
    		f.writelines([line.strip(),"t= %s \n" %(datetime.now())])
