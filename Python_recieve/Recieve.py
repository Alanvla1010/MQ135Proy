import serial
import numpy as np
import matplotlib.pyplot as plt


data1=[]
data2=[]
data3=[]
ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
#time.sleep(2)

for i in range(350):
    line = ser.read(15)
    if line:
        string = line.decode('utf-8')
        print(string)
        field0, field1, field2 = string.splitlines()
        data1.append(field0)
        data2.append(field1)
        data3.append(field2)

        #plt.plot(data1, c='black', marker='o',linestyle='dotted')
        #plt.show()


ser.close()
plt.plot(data2, c='black', marker='o',linestyle='dotted')
plt.plot(data3, c='red', marker='o', linestyle='dotted')
plt.xlabel('Cuentas')
plt.ylabel('ppm CO2, Temp°C')
print(data1)
print(data2)
print(data3)
plt.show()



#response =  ser.read(60)
#my_str = response.decode('utf-8')
#field0, field1, field2, field3, field4 = my_str.splitlines()
#data1.append(field0)
#data2.append(field1)
