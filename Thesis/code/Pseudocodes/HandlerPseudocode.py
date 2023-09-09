############### Pseudocode ###############
Start
1. Add some handlers definition to predefined ones 
2. Declaration of "current_color_uri" with "/currentcolor" path
3. Define same configs for camera
4. if(there is any request):
        Check it with all handlers 
        if(any handler were called (except "current_color_uri")):
             respond properly
End
