# The TimeFlo Project: Design
*Jordan Hyde 2021*

## Introduction
This document serves as the design prospects for my rendition of Bart Massey's TimeFlo Project. This project is explicitly for grading and for no other purpose. The project refers to a method of time management called the Pomodoro strategy. This time management strategy makes use of shorter periods of work broken up by short breaks in order to achieve efficiency in workflow. The program will run as a WIN32 application which is fully documented by Microsoft.


This design document will outline the proposed architecture of a program for timing the work and break periods. The program will function on the Windows platform at a minimum. The program will visually and auditorily notify the user when the timer has finished counting. The user will be able to tell the program how long they wish to work and break for. The user will be able to set a pattern for shorter or longer breaks, such as taking a longer break after 4 consecutive work sessions. There will be a default configuration for the timer, and the user will be able to save their configuration in a text file.


The main design considerations for this project come from 2 different kind of timers. A physical kitchen (egg) timer, and a digital alarm or phone timer. I believe with these two examples of timers you can outline the best features of any type of timer, while also showing their downsides.


A kitchen timer has the following pros and cons:


Pros:

- It takes only one action(turning the dial) to set the timer and run it.


- You can move the timer ahead or back without stopping it.


Cons:


- You cannot accurately set the timer to a specific second.


- The timer has a relevant maximum amount of time it can count, usually an hour.


A digital timer has the following pros and cons:


Pros:



- The time can be exactly set down to the second or further.


- The maximum amount of time it can count is irrelevant, usually multiple days.


Cons:


- The timer usually takes many actions to set up, setting the time may be separated into several fields and starting the timer is seperate.


- The timer can run out of battery.


- You usually cannot interact with the timer once it has started.


## Architecture


A main design concern is that because the program will have an interface with multiple time inputs, it may have a complicated interface. The best way to work around this is to have a well labeled and intuitive interface. With that in mind, the main display of the timer is going to be a traditional slider. This means that the user can set their work time on the same display that shows its progress. This will also allow the user to add or remove time from the timer without stopping it. Setting exact maximum time will be a separate numerical input field. The timer for breaks will operate identically to the timer for working. The user will be able to select an option to tell the program to start the work timer again immediately after the break timer completes, restarting the cycle. There will be a button labeled "start" which will automatically start the timer with the user's values. There will be a button labeled "save" that saves all of the user's settings to the default text file. there will be a button labled "stop" that completely stops the timer from running. There will be a button labled pause which will hold the current state of the timer until the user runs it again. 


Windows WIN32 applications take events from the user in order to determine the outcome in the program. These events will be used in order to determine what actions the user wishes to take. This program will use the WIN32 buttons in order to cover each of the buttons outlined in the above paragraph. The slider will also be provided in a similar fashion. The timing function will need to count regardless of program variables such as runtime lag. The program will reference the system's time variable for this reason.


In order to save the user's settings the program will take the inputs from the user and save them to a text file. The first line of the file will contain the hours, minutes, and seconds for the work period time seperated by "|" characters with spaces. The second line of the file will contain the same information, formatted the same way, for break periods. The third line of the file will contain a character Y or N in order to save the user's preference on restarting the timing cycle, and no other information. 

