# The TimeFlo Project: Validation and Verification
*Jordan Hyde 2021*

(*Thanks to Chris Gilmore for the document template for this
document.*)

## Introduction

The purpose of this document is to display the validation and verification processes used to confirm the complete function of this program. The remainder of the document will describe the techniques that will be used and the process that will be taken. 

### Purpose and Scope

This program is meant as a turn in for the fall 2021 term of PSU's CS300 Software Engineering course. It will be turned in for credit, and not used for any other purpose. The scope of verification and validation will focus on the necessary functions outlined by the assignment, and ensuring no other malfunction exists. Some features determined by the design and requirement documents have been cut for time, and the reasons for that will be outlined. 

### Target Audience

The main target audience for this document is Bart Massey, the person who created the base assignment and is responcible for its grading. Past that, this document will serve as a record of the testing done if myself or anyone else decided to look into this program.

### Terms and Definitions

The program refers to the entire program, as it runs as of 11/8/2021

The edit boxes are windows API controls that the user can input values in. The program uses a style of edit box that can only take number values.

The trackbars are windows API controls that the user can slide to change the remaining time left on the timer. 

The main .cpp file refers to Timeflo Project.cpp

## V&amp;V Plan Description

The plan for validation and verification will include investigation and testing. I am unsure of any formal methods that could be used to test this kind of program, and because of limited time I will be unable to use any. The investigation stage will be primarily focused on finding the edge cases where the program may not function as intended. Simple corrections may be notated but not made during this phase, as repairs should not be made during investigaion. Investigation will also clearly state any features that were outlined in the design process that were not included in the final build. The testing phase will go over each of the edge cases found by the investigation phase, in order to ensure there arent any extensive errors created by these cases. Simple bugs may not be fixed, but any major crashes will need to be corrected to ensure a baseline function of the program. 

## Test Plan Description

Test Cases:

- 0 cases in each value

- Negative cases in each value

- Negative values combined with positive values

- Large values

- Very large values

### Scope Of Testing

The main scope of testing will be considering what edge cases may cause the timer to malfunction. This would be values not normally considered for time, such as negative values and extremely large values. 0 cases in each value will also be tested in order to confirm the program doesn't read it in an unintended way. The edit boxes used to input values, as well as the sliders will be tested for full range of function during these cases. 

### Testing Schedule

All testing will be taking place at once, giving at most an hour to each case to test as many combinations as possible. If absolutely necessary fixes are discovered, they will be repaired after testing.

### Release Criteria

The maximum fault tolerance for this testing phase will be that the timer does not continue its cycle or start when told. Any type of program crash is outside this fault tolerance and must be repaired. If a value causes a bug but does not cause the program to crash, or cause an infinite unending timer then it will not be repaired. These bugs will still be as clearly notated as possible, with any potential fix outlined.  

## Unit Testing

Edit Boxes:

The edit box is the main source of input from the user for this program. Because of that, it will need to be tested for any unintended values that can be passed through it. The edit boxes use a style that does not allow the user to input letter characters, only numbers. If the user can input unintended integer values then issues may arise.

Trackbars

The trackbars can be moved while the timer is running to change the remaining time on the timer. These will also be tested in order to confirm changing the value during unintended edge cases does not cause crashes. 

Stop/Pause/Start buttons

These buttons will be tested in order to confirm usage during unintended edge cases does not cause crashes.

### Strategy

The main strategy for testing the edge cases outlined above will be described here. In order to confirm the edge case does not become more problematic when used in any of the 6 edit boxes, each box will be tested individually. During the test, the timer will run with the edge case value input in one of the 6 edit boxes. Each other box will be input as 0 if the edit box is one of the work period timer inputs. If the edit box is one of the break timer inputs, the work timer second value will be set to 1. While the timer runs, the trackbars and buttons will be stress tested with rapid inputs in hopefully unintended ways. 

## System Testing

The main system being tested with this program is the message loop created using the windows api. This is best represented in code by the WndProc function in the main .cpp file. This function processes each message sent to the main program window. The testing process was created considering this function runs many times in succession while the program runs. In order to confirm this function does not create bugs the unintended edge cases must be considered.

## Inspection

Inspection was completed on the main .cpp file. Other files were created by the IDE used to create the project, and will not be inspected. The inspection process yielded the test plan outlined above, and the units that were best able to be manipulated for testing. There is only one outright missing feature from the design document outlines. The save function had to be cut for time, because it was an extra-functional requirement and would not be able to be completed in the time before turn in. This feature could easily be implemented in the future, and doing so would likely not cause any extra issues. The notification function had to be changed from its original design. Originally, the plan was to notify the user through the Window's notification center. Doing this would have required implementing another module to use the windows shell api. In place of this pattern, I decided to use a message box, which is included in the winuser api. The message box still notifies the user in visual and audio. I believe this is a worse representation of the original strategy, because the message box pops up in a rather intrusive fashion.  
