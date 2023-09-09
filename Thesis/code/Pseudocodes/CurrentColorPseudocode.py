############### Pseudocode ###############
Start
1. Create a buffer 
2. if(there are any "get" request with query string):
        assign buffer values to 0 to clear last data
        if(the "key" of query is "color"):
                assign the value to buf
3. Write data with serial to STM32
4. clear buffer
End
