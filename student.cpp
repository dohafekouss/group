#include "student.h"
#include <iostream>
using namespace std;

Student::Student(int id,string firstname,string surname, string dob,string attendance):
studentId(id),fname(firstname), sname(surname),date_of_birth(dob),studentAttendance(attendance){}

Student::Student(int id,string firstname,string surname, int votes):studentId(id),
fname(firstname), sname(surname), noOfVotes(votes){}

int Student::getId() const {
    return studentId;
}
int Student::getVotes() const{
    return noOfVotes;
}
void Student::setVotes(int vote){
    this->noOfVotes=vote;
}
void Student::setFirstName(string fname) {
    this->fname=fname;
}
void Student::setSurname(string sname) {
    this->sname=sname;
}
void Student::setDOB(string dob) {
    this->date_of_birth=dob;
}
void Student::setAttendance(string attendance) {
    this->studentAttendance=attendance;
}
string Student::getFirstName() const {
    return fname;
}
string Student::getSurname() const {
    return sname;
}

string Student::getDOB() const {
    return date_of_birth;
}

string Student::getAttendance() const {
    return studentAttendance;
}


