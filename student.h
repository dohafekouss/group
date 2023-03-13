#ifndef ONLINEVOTINGSYSTEM_STUDENT_H
#define ONLINEVOTINGSYSTEM_STUDENT_H
#include <iostream>
#include <string>
using namespace std;

class Student{
    public:
        Student();
        Student (int id,string firstname,string surname, string dob,string attendance);
        Student (int id, string firstname, string surname, int votes);
        int getId() const;
        string getFirstName() const;
        string getSurname() const;
        string getDOB() const;
        string getAttendance() const;
        int getVotes() const;
        void setVotes(int vote);
        void setFirstName(string fname);
        void setSurname(string sname);
        void setDOB(string dob);
        void setAttendance(string attendance);
    private:
        int studentId;
        string fname;
        string sname;
        string date_of_birth;
        string studentAttendance;
        int noOfVotes;
};

#endif //ONLINEVOTINGSYSTEM_STUDENT_H
