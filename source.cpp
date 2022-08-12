//============================================================================
// Name        : Source.cpp
// Author      : Andrew Robinson
// Version     : 1.0
// Copyright   : Copyright © 2022 SNHU CS-300
// Description : Project Two Source File
//============================================================================
#include <iostream>
#include <fstream>
#include <vector>
#include "CSVparser.hpp"

using namespace std;

//Each course will have an ID, Name, and a Vector to hold prerequisites
struct Course {
    string courseNum;
    string courseName;
    vector <string> prereq;

    Course() {}
};

//Each node in the BST will contain course information as well as the left and right node
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    }

Node(Course tempCourse) : Node() {
    this->course = tempCourse;
    }
};

//Course Binary Search Tree Class
class CourseBST {

private:
    Node* root;
    void addNode(Node* node, Course course);
    void printCourses(Node* node);
    void printCourseInfo(Node* node, string courseNum);

public:
    CourseBST();
    nullCourseBST();
    void DeletePrevNode(Node* node);
    void InsertCourse(Course course);
    int NumPrereq(Course course);
    void PrintCourses();
    void PrintCourseInfo(string courseNum);
};

//Constructor for the BST while initializing root
CourseBST::CourseBST() {
    root = nullptr;
}

//Destructor for BST passing root to the function
CourseBST::nullCourseBST() {
    DeletePrevNode(root);
}

//Delete BST nodes recursively
void CourseBST::DeletePrevNode(Node* node) {
    if (node) {
        DeletePrevNode(node->left);
        DeletePrevNode(node->right);
        delete node;
    }
}

//Insert node into BST
void CourseBST::InsertCourse(Course course) {

    //If root is not initialized
    if (root == nullptr) {

            //Root will become new node
            root = new Node(course);
    }
    //Use add node method
    else {
            this->addNode(root, course);
    }
}

//Return number of prerequisites the course has
int CourseBST::NumPrereq(Course course) {
    int ticker = 0;

    //For loop to search course.prereq and if it has more than 0 entries it will increment ticker
    for (unsigned int i = 0; i < course.prereq.size(); i++) {
        if (course.prereq.at(i).length() > 0){
                ticker++;
    }
    return ticker;
}
}

//Pass the BST root to print course list
void CourseBST::PrintCourses() {
    this->printCourses(root);
}

//Pass BST root also with the course ID to search for course and display if found
void CourseBST::PrintCourseInfo(string courseNum) {
    this->printCourseInfo(root, courseNum);
}

//Use Insert method and if the current node is null, a node will be added to BST else it will iterate through BST until null node is found
void CourseBST::addNode(Node* node, Course course) {

    //If current course number is less than current node courseNum
    if (node->course.courseNum.compare(course.courseNum) > 0) {
        if (node->left == nullptr) {
                node->left = new Node(course);
        }
        else {
            this->addNode(node->left, course);
        }
    }
    //Current courseNum is >= to current node courseNum
    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
            }
    else {
        this->addNode(node->right, course);
        }
    }
}

//Print courses in order
void CourseBST::printCourses(Node* node) {
    if (node != nullptr) {
        printCourses(node->left);
        cout << node->course.courseNum << ", " << node->course.courseName << endl;
        printCourses(node->right);
        cout << node->course.courseNum << ", " << node->course.courseName << endl;
    }
    return;
}

//Display single course along with its prerequisites
void CourseBST::printCourseInfo(Node* curr, string courseNum) {

    //Iterate through BST until end is reached or if course number is found
    while(curr != nullptr) {

        //Course number passed matches current course number
        if (curr->course.courseNum.compare(courseNum) == 0) {

            //Display course and number of prerequisites
            cout << endl << curr->course.courseNum << ", " << curr->course.courseName << endl;
            unsigned int size = NumPrereq(curr->course);
            cout << "Prerequisite Courses: ";

            //Display each prerequisites if prerequisites exist
            unsigned int i = 0;
            for(i = 0; i < size; i++) {
                cout << curr->course.prereq.at(i);
                if (i != size - 1) {
                    cout << ", ";
                }
            }
            //If no prerequisites exist
            if (i == 0) {
                cout << "No prerequisites found" << endl;
            }
        }
        //If course number is smaller than current course number point left
        else if (courseNum.compare(curr->course.courseNum) < 0) {
            curr = curr->left;
        }
        //If course number is larger than current course number point right
        else {
            curr = curr->right;
        }
    }
    //If null pointer has been reached but the course has not been found
    cout << "Course " << courseNum << " not found" << endl;
}

//Read courses from user input for csv file
bool loadCourses(string csvPath, CourseBST* coursesBST) {

    //Open file and read each line while inserting it into the BST
    try {
        ifstream courseFile(csvPath);

        if (courseFile.is_open()) {
            while (!courseFile.eof()) {

                //Vector to hold csv file information
                vector<string> courseInfo;
                string courseData;

                getline(courseFile, courseData);
                while(courseData.length() > 0) {

                    //Get course data and add to vector
                    unsigned int comma = courseData.find(",");

                    //Each data range will be allowed up to 99 characters
                    if (comma < 100) {
                        courseInfo.push_back(courseData.substr(0, comma));
                        courseData.erase(0, comma + 1);
                    }
                    //Adds last course after the last comma
                    else {
                        courseInfo.push_back(courseData.substr(0, courseData.length()));
                        courseData = "";
                    }
                }

                //Load values into a course and then insert that course into BST and then close file
                Course course;
                course.courseNum = courseInfo[0];
                course.courseName = courseInfo[1];

                //For loop to read the rest of the line and push it back for courseInfo and assign it to prereq
                for (unsigned int i = 2; i < courseInfo.size(); i++) {
                    course.prereq.push_back(courseInfo[i]);
                }
                coursesBST->InsertCourse(course);
            }
            courseFile.close();
            return true;
        }
    }
    //Error if something is wrong with reading csv
    catch (csv::Error& e) {
        cout << "Error: " << e.what() << endl;
    }
    return false;
}
