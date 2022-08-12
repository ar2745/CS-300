//============================================================================
// Name        : Main.cpp
// Author      : Andrew Robinson
// Version     : 1.0
// Copyright   : Copyright © 2022 SNHU CS-300
// Description : Project Two Main File
//============================================================================
#include <iostream>
#include <fstream>
#include <vector>
#include "CSVparser.hpp"
#include "source.cpp"

//Main
int main() {

    //Variable declarations
    string csvPath, courseID;
    bool itWorks = true;

    //Define BST and display intro
    CourseBST* courseBST = nullptr;
    cout << "Welcome to the ABC University Course Planner Tool" << endl;

    //Make user input integer
    int userInput = 0;

    //Menu
    while (userInput != 9) {
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Individual Course Info" << endl;
        cout << "9. Exit Program " << endl;
        cout << endl;
        cout << " What would you like to do:" << endl;
        cin >> userInput;

        //Handle user input from menu
        switch (userInput) {

        //Instantiate BST
        case 1:
            if (courseBST == nullptr) {
                courseBST = new CourseBST();
            }
            if (csvPath.length() == 0) {
                cout << "Enter the file name which contains course data: ";
                cin >> csvPath;
            }

            //If file is opened successfully
            itWorks = loadCourses(csvPath, courseBST);
            if (itWorks) {
                cout << "Courses have been successfully loaded" << endl;
            }
            else {
                cout << "File not found" << endl;
            }
            csvPath = "";
            break;

        //Validate BST exists and prints course list
        case 2:
            if (courseBST != nullptr && itWorks) {
                cout << "Printed course list:" << endl;
                courseBST->PrintCourses();
                cout << endl;
            }
            else {
                cout << "Load courses first please" << endl;
            }
            break;


        //Validate BST exists and display course info
        case 3:
            if (courseBST != nullptr && itWorks) {
                if (courseID.length() == 0) {
                    cout << "What course would you like to search for" << endl;
                    cin >> courseID;
                }
                courseBST->PrintCourseInfo(courseID);
                cout << endl;
            }
            else {
                cout << "Load courses first please" << endl;
            }
            courseID = "";
            break;


        //User input chooses exit program
        case 9:
            cout << "Thank you for using the ABC University Course Planner Tool" << endl;
            break;
            return 0;
        }
    }
}
