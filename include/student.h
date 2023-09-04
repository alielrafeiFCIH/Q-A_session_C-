#ifndef STUDENT_H
#define STUDENT_H

#include <bits/stdc++.h>
using namespace std;
class student
{
    public:
        string firstName; 
        string lastName;
        int enterTime;
        int numQuestions;
        int unanswered;
        int laptopSerialNum;
        student(string firstName,string lastName,int entertime,int numQuestions);
        student();
        virtual ~student();

    protected:

    private:
};

#endif // STUDENT_H
