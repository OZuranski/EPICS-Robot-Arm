# Project Manus
 
Project Manus is a student lead team part of Purdue University's EPICS ECE Outreach program. Our main goal with Project Manus is to showcase engineering design principles to prospective students through an interactive, easy to build robotic arm. The arm was modeled in Fusion 360 with mostly 3D printed parts and common electronics to remain accessible for schools and hobbyists. It features 5 degrees of freedom, RC controls, and Nema 17 stepper motors, all controled by an Arduino for expandibility. The endeffector can be replaced with various attatchments such as a claw or a pen. ![video1](Media/20241126_173315.mp4)

![{BF1A62CF-4D5A-4897-8AC2-FE6918821FA5}](https://github.com/user-attachments/assets/f1ff2cce-f473-4402-871e-7de717b2ebb8)

# Issues

1. Many components such as the bearings rely on a tight interference fit with 3D printed plastic. This method makes assembly relatively simple, however it makes disassembly almost impossible without cracking the plastic. If the parts are printed in PLA, the fit can slowly  loosen over time due to PLA's fluid properties under pressure, leading to excessive play in the arm. We suggest modifying the model to include screw sections between press fit components and other parts to make disassembly easier, and to print all parts in PETG.
2. The gear ratio of the base, shoulder, and elbow joint is not high enough for the weight of the arm. It is currently at 6:1, but we suggest modifying the gears within the planetary gearboxes and the pulleys to be at least 24:1. Geared Nema 17 or larger motors can be used, but this will require a major redesign of the arm which will be more costly.
3. Unfortunately due to time constraints within our semester, we were unable to fully implement the wrist joint, hand joint, and a function end effector in our prototype. We suggest finding or desining a simple claw mechanism that uses light servo motors to minimize weight at the end of the arm. 

   
