############### Pseudocode ###############
Start
1. import necessary libraries
2. Determine boundries of colors 
3. Define function to detect colors
   3.1.Create mask with boundries  
   3.2.Convert frame to hsv representations
   3.3.Use threshold for mask

4. Find all contours   
5. Choose biggest object among contours detected
6. Return width and Heigth of object
7. Draw shape around obstacle for visualization
End
