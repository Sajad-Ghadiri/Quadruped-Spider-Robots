import cv2 as cv
import numpy as np
from time import sleep
import serial
import requests
import datetime
import time

Area = 0 
width = 0

green = (0,255,0)
blue = (255,0,0)

# lower_blue = np.array([88 , 80 , 63])
# upper_blue = np.array([136 , 255 , 255])

lower_blue = np.array([90 , 65 , 110])
upper_blue = np.array([134 , 159 , 222])

lower_green = np.array([44 , 21 , 82])
upper_green = np.array([69 , 64 , 234])

# lower_pink = np.array([159 , 53 , 67])
# upper_pink = np.array([232 , 134 , 185])

lower_pink = np.array([129 , 20 , 118])
upper_pink = np.array([198 , 120 , 250])

lower_yellow = np.array([0 , 47 , 78])
upper_yellow = np.array([48 , 116 , 200])

def nothing():
    pass

def Blue(frame):
    hsv=cv.cvtColor(frame,cv.COLOR_BGR2HSV)
    mask=cv.inRange(hsv,lower_blue,upper_blue)
    _,mask1=cv.threshold(mask,254,255,cv.THRESH_BINARY)
    cnts,_=cv.findContours(mask1,cv.RETR_EXTERNAL,cv.CHAIN_APPROX_NONE)
    global Area
    global width
    for c in cnts:
        x=600
        if cv.contourArea(c)>x:
            x,y,width,h=cv.boundingRect(c)
            cv.rectangle(frame,(x,y),(x+width,y+h),blue,2) 
            Area = width*h
            # global_Area = w*h
            cv.putText(frame,(f'Blue DETECTED, ${width} '),(10,60),cv.FONT_HERSHEY_SIMPLEX,0.6,(0,0,255),2)
            return (1,width)
    # return (0,global_Area)
    return (0,width)


def Pink(frame):
    hsv=cv.cvtColor(frame,cv.COLOR_BGR2HSV)
    mask=cv.inRange(hsv,lower_pink,upper_pink)
    _,mask1=cv.threshold(mask,254,255,cv.THRESH_BINARY)
    cnts,_=cv.findContours(mask1,cv.RETR_EXTERNAL,cv.CHAIN_APPROX_NONE)
    global Area
    global width
    for c in cnts:
        x=600
        if cv.contourArea(c)>x:
            x,y,width,h=cv.boundingRect(c)
            cv.rectangle(frame,(x,y),(x+w,y+h),blue,2) 
            Area = width*h
            # global_Area = w*h
            cv.putText(frame,(f'Pink DETECTED, ${width}'),(10,60),cv.FONT_HERSHEY_SIMPLEX,0.6,(0,0,255),2)
            return (1 , width)
    # return (0 , global_Area)
    return (0 , width)

BASE_URL = "http://172.21.232.26"
cap = cv.VideoCapture('http://172.21.232.26:81/stream')

# distance = 200
flag_B = 0
flag_N = 1
flagTimeFirstRun = 0


while True:
    # t_current = time.time()
    t_current = time.localtime(time.time())
    if(flagTimeFirstRun == 0):
        t_last = t_current.tm_sec
        flagTimeFirstRun = 1
    ret , frame = cap.read()
    status = "N666"

    (condition_BLue , Area_Blue) = Blue(frame)
    distance_Blue = round( Area_Blue)
    if distance_Blue < 100:
        distance_Blue = "0" + str(distance_Blue)
    else:
        distance_Blue = str(distance_Blue)
    if(condition_BLue):
        status="B" + distance_Blue
 
    (condition_Pink , Area_Pink) = Pink(frame)
    distance_Pink = round( Area_Pink)
    if distance_Pink < 100 :
        distance_Pink = "0" + str(distance_Pink)
    else:
        distance_Pink = str(distance_Pink)
    if(condition_Pink):
        status = "P"+ distance_Pink

    if(t_current.tm_sec >= (t_last + 2)):
        t_last = t_current.tm_sec
        if(t_last >= 58):
            t_last = 0
        url = f"{BASE_URL}/currentColor?color={status}"
        print(url)
        x = requests.get(url)
        print(f'Status:{x.status_code} , Time: {t_current.tm_sec} , Area: {Area} ')
        

    cv.imshow("FRAME",frame)
    if cv.waitKey(1)&0xFF==27:
        break

        # Do not forget to release the capture 
cap.release()
cv.destroyAllWindows()

