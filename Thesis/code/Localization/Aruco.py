import numpy as np
import cv2
import PIL
import os
from cv2 import aruco
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import matplotlib as mpl
import pandas as pd

camera = cv2.VideoCapture(0)
mtx = np.array([[1.78952655e+03, 0.00000000e+00, 9.69572430e+02],
                [0.00000000e+00, 1.78952655e+03, 5.64872516e+02],
                [0.00000000e+00, 0.00000000e+00, 1.00000000e+00]])

dist = np.array([[5.33659854e+00],[-1.67904382e+02],[3.32943561e-03],
                 [-4.67385863e-03],[9.75622127e+02],[5.14691206e+00],
                 [-1.66105367e+02],[9.69643912e+02],[0.00000000e+00],
                 [0.00000000e+00],[0.00000000e+00],[0.00000000e+00],
                 [0.00000000e+00],[0.00000000e+00]])
dist.reshape(1,14)
while 1 : 
    try:
        _ , frame = camera.read()
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        aruco_dict = aruco.Dictionary_get(aruco.DICT_6X6_250)
        parameters = aruco.DetectorParameters_create()
        corners, ids, rejectedImgPoints = aruco.detectMarkers(gray,
                                    aruco_dict,parameters=parameters)
        # SUB PIXEL DETECTION
        criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER,
        100,0.0001)
        for corner in corners:
            cv2.cornerSubPix(gray, corner, winSize=(3, 3),
                              zeroZone=(-1, -1), criteria=criteria)

        frame_markers=aruco.drawDetectedMarkers(frame.copy(),corners,ids)
        
        size_of_marker = 0.0285  # side lenght of the marker in meter
        
        rvecs, tvecs, _ = aruco.estimatePoseSingleMarkers(corners,
                                            size_of_marker,mtx, dist)
        length_of_axis = 0.1
        
        #print("hi")
        imaxis = aruco.drawDetectedMarkers(frame.copy(), corners, ids)
        #print(imaxis)
        
        for i in range(len(tvecs)):
            imaxis = aruco.drawAxis(
                imaxis, mtx, dist, rvecs[i], tvecs[i], length_of_axis)
            
        cv2.imshow("hi",frame)
        if (cv2.waitKey(1) & 0xFF) == ord('q'):
            break
        cv2.imshow("hii", frame_markers)
        cv2.imshow("hiii", imaxis)
        data = pd.DataFrame(data=rvecs.reshape(len(rvecs), 3), 
                            columns=["tx", "ty", "tz"],
                            index=ids.flatten())
        data.index.name = "marker"
        data.sort_index(inplace=True)
        print(data)
    except:
        print("an error occured in while loop")

camera.release()
cv2.destroyAllWindows()