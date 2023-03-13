#include <iostream>
#include<string>
#include<curses.h>
#include<stdlib.h>
#include<vector>
#include "student.h"
#include <iomanip>
using namespace std;
#define limit 2
int cnt;

vector <Student> studentList;
vector <Student> academicExcellence;
vector <Student> bestEffort;
vector <Student> mostImproved;
vector <Student> perfectAttendance;
vector <Student> friendship;
void add(int id,string firstname,string surname,string dob,string attendance){
    cnt++;
    studentList.push_back(Student(id,firstname,surname,dob,attendance));
}

void add_student() {
    string firstname, surname, dob, attendance;
    int id;
    id = cnt;
    cout<<"Enter student's first name: ";
    cin>>firstname;
    cout<<"Enter student's surname: ";
    cin>>surname;
    cout<<"Enter student's date of birth: ";
    cin>>dob;
    cout<<"Enter student's attendance percentage: ";
    cin>>attendance;
    studentList.push_back(Student(id,firstname,surname,dob,attendance));
}

void displayAll(){
    cout << "\nStudents:" << endl;
    for (const Student& student : studentList) {
        cout <<"Student Id: "<<student.getId() << "\t\tFirst Name: "<<student.getFirstName()<<
        "\t\tSurname: "<<student.getSurname()<<"\t\tDate Of Birth: "<<student.getDOB()
        <<"\t\tAttendance: "<<student.getAttendance()<<endl;
    }
}
void getStudentById(){
    int id;
    cout<<"\nEnter Student Id: ";
    cin>>id;
    for (Student& student : studentList) {
        if (student.getId() == id) {
            cout << "Student Id: " << student.getId() << "\t\tFirst Name: " << student.getFirstName() <<
                 "\t\tSurname: " << student.getSurname() << "\t\tDate Of Birth: " << student.getDOB()
                 << "\t\tAttendance: " << student.getAttendance() << endl;
        }
    }
}
void deleteById(){
    int id;
    cout<<"\nEnter Student Id: ";
    cin>>id;
    for (int i=0;i<studentList.size();i++){
        if (studentList[i].getId()==id){
            studentList.erase(studentList.begin()+i);
        }
    }
}
void editDetails() {
    int id;
    cout<<"Enter Student Id: ";
    cin>>id;
    for (Student& student : studentList){
        if (student.getId()==id){
            int ch;
            string ch2;
            cout<<"\n1. First Name\n2. Surname\n3. Date of birth\n4. Attendance\n";
            cout<<"Select a choice: \n";
            cin>>ch;
            cout<<"What do you want to change it to?\n";
            cin>>ch2;
            switch(ch) {
                case 1:
                    student.setFirstName(ch2);
                    cout << "Change Made!" << endl;
                    break;
                case 2:
                    student.setSurname(ch2);
                    cout << "Change Made!<<" << endl;
                    break;
                case 3:
                    student.setDOB(ch2);
                    cout << "Change Made!" << endl;
                    break;
                case 4:
                    student.setAttendance(ch2);
                    cout<<"Change Made!"<<endl;
                    break;
            }
        }
    }
    return;
}

bool login() {
    string username, password;
    string choice;

    cout << "Are you an admin(yes/no) : ";
    cin >> choice;

    if (choice == "yes") {
        cout << "\n\t\tEnter login credentials for ADMIN PORTAL" << endl;
        cout << "\nEnter username : ";
        cin >> username;
        cout << "Enter password : ";
        cin >> password;

        if (username == "admin" && password == "admin") {
            cout << "\nWELCOME TO ADMIN PORTAL" << endl;
            return true;
        } else {
            cout<<"\nUsername or Password Incorrect!";
            return false;
        }
    } else{
        cout<<"\n Sorry, you do not have access to this system.";
        return 0;
    }
}

void print(vector <Student> list) {
    int v,ch3,vote,votes,id,highestVotes;
    string firstName, surname;
    bool x=false,flag=false;
    do {
        cout << "\n---------------------------------------";
        cout << "\n       STUDENT VOTING SYSTEM           ";
        cout << "\n---------------------------------------";
        cout << "\n       1. Vote With Student ID         ";
        cout << "\n       2. View Current Nominees        ";
        cout << "\n       3. Nominate Student             ";
        cout << "\n       4. View Winner                  ";
        cout << "\n       5. Back To Awards List          ";
        cout << "\n---------------------------------------\n";
        cout<<"Enter Your Choice: ";
        cin >> ch3;
        switch (ch3) {
            case 1:
                cout << "\nEnter your votes student id: ";
                cin >> vote;
                for (Student &student: list) {
                    if (student.getId() == vote) {
                        x=true;
                        int a = student.getVotes();
                        student.setVotes(a + 1);
                        cout<<"Your vote has been tallied!\n";
                    }
                }
                if (x==false){
                    cout<<"\nInvalid Student Id! Student hasn't been nominated!";
                }
                break;
            case 2:
                for (const Student &student: list) {
                    cout << "Student Id: " << student.getId() << "\t\tFirst Name: "
                         << student.getFirstName() <<
                         "\t\tSurname: " << student.getSurname() << "\t\tNumber of Votes: " <<
                         student.getVotes() << endl;
                }
                break;
            case 3:
                cout << "Enter Student ID: ";
                cin >> id;

                for (const Student &student: studentList) {
                    if (student.getId()==id){
                        x=true;
                        id=student.getId();
                        firstName=student.getFirstName();
                        surname=student.getSurname();
                        v=1;
                    }
                }
                if (x==true){
                    for (const Student &student2: list) {
                        if (student2.getId()==id){
                            cout<<"Student Already Nominated!\n";
                            flag=true;
                        }
                    }
                }else if (x==false){
                    cout<<"\nInvalid Id! Student doesn't exist!";

                }
                if(x==true&&flag==false){
                    list.push_back(Student(id,firstName,surname,v));
                    cout << "Student Nominated and your vote has been tallied!\n";
                }
                break;
            case 4:
                highestVotes=list[0].getVotes();
                for (int i=0;i<list.size();i++) {
                    if (list[i+1].getVotes()>list[i].getVotes()){
                        highestVotes=list[i+1].getVotes();
                        firstName = list[i+1].getFirstName();
                        surname = list[i+1].getSurname();
                    }
                }
                cout<<"The Winner is "<<firstName<<" "<<surname<<" with "
                    <<highestVotes<<" vote(s)!"<<endl;
                break;
            case 5:
                break;
            default:
                cout<<"Invalid Choice!";
                break;
        }
    }while(ch3!=5);
}

int main() {
    add(cnt, "Daniel","Brown","29/03/2005","99%");
    add(cnt, "Hannah","Smith","15/08/2005","97%");
    add(cnt, "Sarah","Taber","14/02/2005","98%");
    add(cnt, "Ryan","Skalli","20/02/2005","100%");
    add(cnt, "Melissa","Rodriguez","13/06/2005","99%");
    add(cnt, "Adam", "Worth", "12/04/2005","95%");
    add(cnt, "Benita", "Chapman", "11/01/2005","92%");
    add(cnt, "Christina", "Jones", "21/11/2004","98%");
    add(cnt, "David","Williams","11/12/2004","100%");

    academicExcellence.push_back(Student(0,"Daniel","Brown",23));
    academicExcellence.push_back(Student(1, "Hannah","Smith",32));
    academicExcellence.push_back(Student(2, "Sarah","Taber",23));
    bestEffort.push_back(Student(5, "Adam", "Worth",8));
    bestEffort.push_back(Student(0, "Daniel","Brown",11));
    mostImproved.push_back(Student(2, "Sarah","Taber",18));
    mostImproved.push_back(Student(7, "Christina", "Jones",20));
    mostImproved.push_back(Student(4, "Melissa","Rodriguez",31));
    friendship.push_back(Student(7, "Christina", "Jones",3));
    friendship.push_back(Student(5, "Adam", "Worth",16));
    perfectAttendance.push_back(Student(3, "Ryan","Skalli",28));
    perfectAttendance.push_back(Student(8, "David","Williams",23));

    int ch, ch2;

    if (login() == true) {
        do {
            cout << "\n---------------------------------------";
            cout << "\n       STUDENT MANAGEMENT SYSTEM       ";
            cout << "\n---------------------------------------";
            cout << "\n       1. Add New Student              ";
            cout << "\n       2. Edit Student Details         ";
            cout << "\n       3. Delete Student               ";
            cout << "\n       4. Vote For Student Awards      ";
            cout << "\n       5. Search For Student           ";
            cout << "\n       6. Return All Students          ";
            cout << "\n       7. Exit                         ";
            cout << "\n---------------------------------------\n";

            cout << "Choose An Option: \n";
            cin>>ch;

            switch (ch) {
                case 1:
                    add_student();
                    break;
                case 2:
                    editDetails();
                    break;
                case 3:
                    deleteById();
                    break;
                case 4:
                    do {
                        cout << "\n----------------------------------------";
                        cout << "\n       STUDENT VOTING SYSTEM            ";
                        cout << "\n----------------------------------------";
                        cout << "\n        1. Academic Excellence          ";
                        cout << "\n        2. Best Effort                  ";
                        cout << "\n        3. Most Improved                ";
                        cout << "\n        4. Perfect Attendance           ";
                        cout << "\n        5. Friendship                   ";
                        cout << "\n        6. Back to Main Menu            ";
                        cout << "\n----------------------------------------\n";

                        cout << "Choose An Option: \n";
                        cin >> ch2;
                        switch (ch2) {
                            case 1:
                                print(academicExcellence);
                                break;
                            case 2:
                                print(bestEffort);
                                break;
                            case 3:
                                print(mostImproved);
                                break;
                            case 4:
                                print(perfectAttendance);
                                break;
                            case 5:
                                print(friendship);
                                break;
                            case 6:
                                break;
                            default:
                                cout<<"\nInvalid Choice!";
                        }
                    }while(ch2!=6);
                case 5:
                    getStudentById();
                    break;
                case 6:
                    displayAll();
                    break;
                case 7:
                    break;
                default:
                    cout<<"\nInvalid Choice!";
            }
        } while (ch != 7);
    } else{
        return 0;
    }
}
