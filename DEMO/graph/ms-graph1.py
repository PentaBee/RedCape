#!/usr/bin/python 

import datetime
import plotly.plotly as py
import time
import math
import time

from smbus import SMBus

username = 'bartgarcia'
api_key = 'j4x55jeevs'# view api key here: https://plot.ly/settings
tokens = ['6eurdw3blj', 'token2'] # generate stream tokens here: https://plot.ly/settings
 
 
print " Obtaining User Id \n"
py.sign_in(username, api_key)
streams = [py.Stream(token) for token in tokens]
for stream in streams:
  stream.open()
print " Stream is now open \n"
py.plot([
    {'x': [],
    'y': [],
    'name': 'pressure',
    'type': 'scatter',
    'stream': {
        'token': tokens[0],
        'maxpoints': 200
        }
    }],
    layout= {
        'yaxis': {'title':'Pressure'}
#        'yaxis2': {'title':'mBar', 'overlaying': 'y', 'side':'right'}
        },
    filename='Pressure Sensor Data',
    fileopt='overwrite')

#    layout= {
#       'yaxis': { 'title':'dOxy mg/L' }
#        },
#    filename='Pressure Sensor Data',
#    fileopt='overwrite')




## Initialize the bus.  (If you have a Rev 2 Raspberry Pi the 0 needs to be changed to a 1)
bus = SMBus(1)


C1 = bus.read_i2c_block_data(0x76, 0xA2) #Pressure Sensitivity
time.sleep(0.05)
C2 = bus.read_i2c_block_data(0x76, 0xA4) #Pressure Offset
time.sleep(0.05)
C3 = bus.read_i2c_block_data(0x76, 0xA6) #Temperature coefficient of pressure sensitivity
time.sleep(0.05)
C4 = bus.read_i2c_block_data(0x76, 0xA8) #Temperature coefficient of pressure offset
time.sleep(0.05)
C5 = bus.read_i2c_block_data(0x76, 0xAA) #Reference temperature
time.sleep(0.05)
C6 = bus.read_i2c_block_data(0x76, 0xAC) #Temperature coefficient of the temperature
time.sleep(0.05)

## Again here we are converting the 2 8bit packages into a single decimal
C1 = C1[0] * 256.0 + C1[1]
C2 = C2[0] * 256.0 + C2[1]
C3 = C3[0] * 256.0 + C3[1]
C4 = C4[0] * 256.0 + C4[1]
C5 = C5[0] * 256.0 + C5[1]
C6 = C6[0] * 256.0 + C6[1]



while True:

    bus.write_byte(0x76, 0x48)
    time.sleep(0.05)
    D1 = bus.read_i2c_block_data(0x76, 0x00)  
    time.sleep(0.05)
    
    bus.write_byte(0x76, 0x58)
    time.sleep(0.05)
    D2 = bus.read_i2c_block_data(0x76, 0x00)
    time.sleep(0.05)
    
    D1 = D1[0] * 65536 + D1[1] * 256.0 + D1[2]
    D2 = D2[0] * 65536 + D2[1] * 256.0 + D2[2]
    
    
    dT = D2 - C5 * 2**8
    TEMP = 2000 + dT * C6 / 2**23
    
    print "Temperature: ", TEMP/100.0
    
    OFF = C2 * 2**16 + (C4 * dT) / 2**7
    SENS = C1 * 2**15 + (C3 * dT) / 2**8
    P = (D1 * SENS / 2**21 - OFF) / 2**15
    
    
    print "Pressure: ", P/100.0
    time_now = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S.%f')
    streams[0].write({'x': time_now, 'y': P/100})
    time.sleep(0.05)
