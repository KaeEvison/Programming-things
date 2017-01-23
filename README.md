Programming things assignment
Kae Evison



Achieved tasks:
I have completed tasks 1 to 4 in this assignment, the program I have written allows the user to remotely control the Zumo using the 'W', 'A', 'S', and 'D' to move it forward, rotate left, move backward and rotate right respectively. The user can also use the 'F' key to set the Zumo moving perpetually forward at a slower rate and thespacebar to halt this movement.
When the Zumo encounters a wall it will halt and wait for user control in order to guide it around corners.
To inicate that a room is about to be scanned, the user can press the 'R' key with the Zumo stopped in the corridor, it will then detect which direction the room is in (left or right) as well as assign the room a number and log that information in an array which can be output using the 'V' key. Once the user has position the Zumo at the entrance to the room, pressing the 'R' key again will begin the scan.
At this stage I have not implemented the ultrasound scanning.
Once the scan is complete the user will be informed in the serial monitor via the XBee and can manuever the Zumo back into the corridor.
Pressing the 'F' key to set the Zumo moving again will exit room clearing mode and the sequence can be repeated at the next room


All of the code I used was based on the example sketches provided with the Arduino IDE and Zumo libraries.
