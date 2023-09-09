import cv2 as cv
import numpy as np

# colors for drawing on frames of stream
red = (0,0 ,255)
green = (0,255,0)
blue = (255,0,0)

base_path = '../ColorCalibration/'
filenames = ['blue' , 'pink' , 'yellow']
hmin = hmax = smin = smax = vmin = vmax = []
print(len(filenames))

def Set_Colors_limits():
    for item in range(len(filenames)):
        # to debug
        # print(base_path + 'tune_' + filenames[item] +'.txt')  
        
        fileOpen = open(base_path + 'tune_' + filenames[item] +'.txt' , "r")
        fileRead = fileOpen.readlines()

        hmin.append(int(fileRead[0])) 
        print('hmin done \n')
        hmax.append(int(fileRead[1])) 
        
        smin.append(int(fileRead[2])) 
        smax.append(int(fileRead[3])) 
        vmin.append(int(fileRead[4])) 
        vmax.append(int(fileRead[5])) 
        # hmax[item] = int(fileRead[1])
        # smin[item] = int(fileRead[2])
        # smax[item] = int(fileRead[3])
        # vmin[item] = int(fileRead[4])
        # vmax[item] = int(fileRead[5])

        

        fileOpen.close()

Set_Colors_limits()
# print(hmin )
# print(smin , smax )
# print(vmin , vmax )