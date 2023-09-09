import cv2 as cv
import numpy as np
from time import sleep
import serial
import requests
import datetime
import time

Area = 0 
w = 0

green = (0,255,0)
blue = (255,0,0)

lower_blue = np.array([90 , 65 , 110])
upper_blue = np.array([134 , 159 , 222])

lower_green = np.array([44 , 21 , 82])
upper_green = np.array([69 , 64 , 234])

lower_pink = np.array([129 , 20 , 118])
upper_pink = np.array([198 , 120 , 250])

lower_yellow = np.array([0 , 47 , 78])
upper_yellow = np.array([48 , 116 , 200])



