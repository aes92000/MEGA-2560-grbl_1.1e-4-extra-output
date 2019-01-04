# MEGA-2560-grbl_1.1e-4-extra-output
modified version to add 4 additional output pins for control through relay

I am, in no way, a professional programmer. Use at your own risk. 
I used existing grbl files and modified to add additional outputs.
I have tested with bCNC and SnapCNC programs. They worked for me very well.

The outputs are assigned through cpu_map.h
Each output has it's own toggle control through 'M' codes
There is an 'M' code for "ALL OFF" of the outputs.

M85 - relay 1 - MEGA A0
M86 - relay 2 - MEGA A1
M87 - relay 3 - MEGA A2
M88 - relay 4 - MEGA A3
M89 - all off

M code can be inseted into gcode files to control whatever you may need to control. I would suggest relay control.


