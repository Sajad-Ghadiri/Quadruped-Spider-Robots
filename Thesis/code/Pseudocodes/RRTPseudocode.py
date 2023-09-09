############### Pseudocode ###############
Start
1. import necassary libraries
2. import classes from modules which we wrote before
3. Define Start and goal points and obstacles dimention
4. Define Main function and write below details in it 
4.1 Create Map and Graph object with init method
4.2 Create obstacles and draw on Map
4.3 while(not graph."path_to_goal()" is True):
        use bias or expand approach for optimization
        update graph by drawing nodes and lines
        draw path to goal untill last node

5. call Main function and define a Flag 
6. if(last node reached to goal point area):
        assign True to our Flag
   else:
        assign False to our Flag
        Main function will call again
End
