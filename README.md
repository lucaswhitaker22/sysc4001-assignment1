# sysc4001-assignment1
Lucas Whitaker 101195445

How to run:
1. Open up shell and navigate to /sysc4001-assignment1 directory
2. Run the script.sh script to build and run the program
3. Altneratively, you can use the following command:


**Starting a Controller Process:**
>$ gcc controller.c -o controller
>$ ./controller

**Starting a Device Process:**
>$ gcc sensor.c -o sensor
>$ ./sensor 500

This will create a sensor process with a threshhold of 500.

# How it works:

The sensor process reads a random value every 1 second. If the value is above the sensors threshold, it raises a signal and triggers an actuator.



