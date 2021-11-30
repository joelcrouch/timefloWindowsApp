# The TimeFlo Project: Requirements Document
*Jordan Hyde 2021*

(*Thanks to Chris Gilmore for the document template for this
document.*)

## Introduction

This document outlines the requirements and design considerations of my version of the TimeFlo project. It will address the purpose and scope of the program, the target audience, the terms and definitions, the users and use cases, stakeholders, and the functional requirements of the program. This project's goal is to create a timer application in C++ for the windows platform. 


### Purpose and Scope

The purpose of this program is to create a convienient to use PC application that times break periods and work periods as outlined by the Pomodoro Technique for workflow. This program will save user preferences and have visual and audio notifications. The main scope consideration for this project is the time limit. Because there are only 4 weeks to build this program, and a majority of time will be spent performing thorough design there will be limits to the final product. One of those limits are that it will only operate on Windows systems, because of familiarity and simplicity.  

### Target Audience

There are two main individuals for the tangible target audience of this program. The professor for this CS300 class, Bart Massey, and myself the author of this program, Jordan Hyde. Outside from that, the considered audience for this program is working individuals or students. People who would use this program while doing their work would benefit from having a convienient to use timer.

### Terms and Definitions

"The timer" will always refer to the program as a whole, and not just one specific aspect or feature of the program. 

## Product Overview

This section will cover a general overview of the product. The product is going to be a Windows executable program that acts as a timer. The Pomodoro Technique outlines a schedule of short work blocks and break periods in order to achieve more efficient workflow. This timer will attempt to mimic this technique in code for the user. In order to perform the assigned functions, the program will time the user and notify them when the periods end. This program needs to be more convienient than a digital phone timer and more useful than a kitchen timer in order to perform above average.  

### Users and Stakeholders

The primary stakeholder of this program is myself. I recieve a grade based on the quality of the project, but also benefit from the practice of creating a complete product. Additionally as I am recieving the grade from my professor, he is also a primary stakeholder. The users of the program are also stakeholders, since this is time management software their time is in its stake. People who are distributed this program will use it, including myself and Bart Massey. Potential other users could be individuals who work with computers, or students. 

#### *Stakeholder 1*

The firstmost stakeholder of this product is myself, Jordan Hyde. My role is the main development programmer and author of all design documents. I will be the one responcible for maintenence, upkeep, distribution, and design of the project. I will be the one benefiting from not only the grade of the assignments and program, but also the experience offered by creating my own version of this project. 

#### *Stakeholder 2*

The second main stakeholder of this project is the person who will grade it, Bart Massey. He has contributed the main idea for the project and the baseline requirements. 

### Use cases
This section describes the use cases for this program. Use cases are the main consideration for how the program should be used. The terms and assumptions of both use case are as follows: 

-the user is using the program on a functioning Windows system

The first use case will cover a user properly using the program to perform the Pomodoro Technique, and the intended outcome. The second use case will cover a user improperly using the program as a regular timer and what complications may occure.

#### *Use Case 1*

The user is a student working on a homework assigment, and plan on taking breaks every 40 minutes. they plan on taking 5 minute breaks between working blocks. In order to do this, they set the timer accordingly, 40 minute work blocks and 5 minute breaks then start the timer. After 40 minutes, the student is notfied they can break. After 5 minutes, they are notified and asked if they wish to restart the work timer.

#### *Use Case 2*

The user is trying to use the program as a normal timer. In order to do this, they set the break timer to 0. The program needs to act as the user wishes, and so the break timing cycle will need to be skipped. The user should not be notified that their break has completed because they did not wish to take a break. The user should only be notified that the first timer has ended. The user should not have to dismiss multiple notifications when they did not ask for them.

## Functional Requirements

This section outlines the functional requirements of the program. Functional requirements are aspects a program must have to be considered "functional" or working in full capacity. This program will have few true functional requirements as specified by the assignment. Timing the user and notifying them are the main functional requirements.

### *Functional Requirements 1*

*Timing the User*

The program must time the user properly. If the user wishes to set the timer for 30 minutes, then it should run for exactly 30 minutes every time with no error. If the program cannot time the user properly then it is not functional. 

### *Functional Requirement 2*

*Notifying the User*

The program must notify the user when the timer finishes. There is no point to properly timing the user if they are not properly notified by the program. If an egg timer made no sound when it finished it would be relatively useless compared to one that does. if the program cannot notify the user than it is not functional.

## Extra-functional Requirements

The purpose of this section is to document the extra-functional requirements of this program. These are the requirements that were not specified by the assignment but would still make the program more functional. These requirements include: saving the user's data and asking the user if they wish to repeat their cycle of work and break periods. The main things considered for this section were design aspects that make the program more efficient and convienient.

### *Extra-functional Requirement 1*

*Saving the user's data*

This program uses a small amount of data to run, 7 values at absolute most by the current design. That being said, in order to be as convienient as a phone timer, it should not require 7 inputs from the user to run every time. This means that saving the user's data between sessions will greatly increase the functionality of the program, as well as achieving design aspirations of efficiency and convienience. 

### *Extra-functional Requirement 2*

*Repeating the timer cycle*

The user should have the choice to run the timer multiple times in a row if they wish. Needing to reset the timer every time would make the timer less convienient. Because of this, allowing the user to select an option to automatically restart the work/break period cycle will increase the functionality of the program. 
