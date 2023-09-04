import cv2 as cv
import numpy as np

# colors for drawing on frames of stream
red = (0,0 ,255)
green = (0,255,0)
blue = (255,0,0)

base_path = '../ColorCalibration/'
filenames = ['blue' , 'pink' , 'yellow']

def Set_Colors_limits():
    for item in range(len(filenames)):
        # to debug
        # print(base_path + 'tune_' + filenames[item] +'.txt')  
        
        fileOpen = open(base_path + 'tune_' + filenames[item] +'.txt' , "r")
        fileRead = fileOpen.readlines()

        hmin = int(fileRead[0])
        hmax = int(fileRead[1])
        smin = int(fileRead[2])
        smax = int(fileRead[3])
        vmin = int(fileRead[4])
        vmax = int(fileRead[5])
        print(hmin , hmax )
        print(smin , smax )
        print(vmin , vmax )

        fileOpen.close()