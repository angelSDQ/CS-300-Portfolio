//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Angel Matos
// Description : ABCU advising assistance program
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>
#include <cctype>

using namespace std;

// Holds the data for one course
struct Course {
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

// One node in the binary search tree
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course aCourse) {
        course = aCourse;
        left = nullptr;
        right = nullptr;
    }
};

// Splits one comma separated line into a Course object
Course parseLine(string line) {
    Course course;
    vector<string> fields;
    stringstream ss(line);
    string field;

    while (getline(ss, field, ',')) {
        fields.push_back(field);
    }

    course.courseNumber = fields.at(0);
    course.name = fields.at(1);

    for (unsigned int i = 2; i < fields.size(); i++) {
        // skips empty fields so trailing commas dont create blank prerequisites
        if (!fields.at(i).empty()) {
            course.prerequisites.push_back(fields.at(i));
        }
    }

    return course;
}

// Finds the correct spot for a course and adds it
void addNode(Node* node, Course course) {
    // smaller course numbers go left and larger go right
    if (course.courseNumber < node->course.courseNumber) {
        if (node->left == nullptr) {
            node->left = new Node(course);   // empty spot found place it here
        } else {
            addNode(node->left, course);     // will continue searching the left
        }
    } else {
        if (node->right == nullptr) {
            node->right = new Node(course);  // empty spot found, place it here
        } else {
            addNode(node->right, course);    // keep searching the right
        }
    }
}

// Adds a course to the tree
void insert(Node*& root, Course course) {
    if (root == nullptr) {
        root = new Node(course);   // first course becomes the root
    } else {
        addNode(root, course);     // otherwise find its spot on the tree
    }
}

// Visits nodes in sorted order (left, current, right)
void inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->course.courseNumber << ", " << node->course.name << endl;
        inOrder(node->right);
    }
}

// prints the full course list in correct alphanumeric order
void printCourseList(Node* root) {
    cout << "Here is a sample schedule:" << endl;
    cout << endl;
    inOrder(root);
}

// searches the tree for one course and prints it with the prerequisites.
void searchCourse(Node* root, string courseNumber) {
    Node* current = root;

    // walks down the tree going left or right by comparison
    while (current != nullptr) {
        if (current->course.courseNumber == courseNumber) {
            // when found -> print the number and name
            cout << current->course.courseNumber << ", "
                << current->course.name << endl;

            // prints the prerequisites as numbers only
            cout << "Prerequisites: ";
            if (current->course.prerequisites.empty()) {
                cout << "None";
            } else {
                for (unsigned int i = 0; i < current->course.prerequisites.size(); i++) {
                    cout << current->course.prerequisites.at(i);
                    // adds a comma between the items but NOT after the last one
                    if (i < current->course.prerequisites.size() - 1) {
                        cout << ", ";
                    }
                }
            }
            cout << endl;
            return;
        } else if (courseNumber < current->course.courseNumber) {
            current = current->left;    // if target is larger then it goes left
        } else {
            current = current->right;   // if target is larger then it goes right
        }
    }

    // Course not found
    cout << "Course " << courseNumber << " was not found." << endl;
}

// Reads the data file and loads each course into the tree
void loadCourses(Node*& root) {
    string fileName;
    cout << "Enter the name of the data file: ";
    getline(cin, fileName);

    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error: could not open file " << fileName << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        // RStrip trailing carriage return
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) {
            continue;
        }
        Course course = parseLine(line);
        insert(root, course);
    }

    file.close();
    cout << "Courses loaded successfully." << endl;
}

int main() {
    Node* root = nullptr;
    int choice = 0;
    bool loaded = false;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        cout << endl;
        cout << "  1. Load Data Structure." << endl;
        cout << "  2. Print Course List." << endl;
        cout << "  3. Print Course." << endl;
        cout << "  9. Exit" << endl;
        cout << endl;
        cout << "What would you like to do? ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                loadCourses(root);
                loaded = true;
                break;
            case 2:
                if (!loaded) {
                    cout << "Please load the data first (option 1)." << endl;
                } else {
                    printCourseList(root);
                }
                break;
            case 3: {
                if (!loaded) {
                    cout << "Please load the data first (option 1)." << endl;
                    break;
                }
                string courseNumber;
                cout << "What course do you want to know about? ";
                getline(cin, courseNumber);

                for (unsigned int i = 0; i < courseNumber.length(); i++) {
                    courseNumber.at(i) = toupper(courseNumber.at(i));
                }

                searchCourse(root, courseNumber);
                break;
            }
            case 9:
                cout << "Thank you for using the course planner!" << endl;
                break;
            default:
                cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}