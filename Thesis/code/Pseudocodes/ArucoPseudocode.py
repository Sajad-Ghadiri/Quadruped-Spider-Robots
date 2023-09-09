############### Pseudocode ###############
Start
1. import necessary libraries
2. Get camera access with IP
3. Define mtx matric and dist array
4. while(camera is available and send validate frame):
        Convert frame to grayscalar 
        Use gray frame as Aruco methods
        Output of methods include corners
        { Find Transition and Rotation matrices 
          by predefined variables and corners }
        
        plot frame in a monitoring window

5. Print Transition and Rotation matrices
6. Release camera
7. Destroy all monitoring windows
End
