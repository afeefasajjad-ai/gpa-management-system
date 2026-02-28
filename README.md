# GPA Management System

A console-based C++ application built to manage student records, track course grades, and calculate Grade Point Averages (GPA). 

## Features
* **Student Registration:** Add new students with a unique ID and name. 
* **Grade Tracking:** Enter and store letter grades (A, B, C, D, F) for multiple courses per student.
* **Automated GPA Calculation:** Calculates GPA on a standard 4.0 scale based on inputted letter grades.
* **Data Persistence:** Automatically loads and saves all student records to a local text file (`students.txt`).
* **Console Interface:** Features an easy-to-use numbered menu system for navigating the application.

## Technical Details
This project demonstrates foundational C++ programming concepts without relying heavily on standard libraries:
* Utilizes primitive 1D and 2D character arrays for data storage instead of standard strings or vectors.
* Implements custom functions (`Strcpy`, `Getline`) for string manipulation and input handling.
* Handles a maximum capacity of 100 students.
* Supports up to 10 courses per individual student.

## Technologies Used
* C++

