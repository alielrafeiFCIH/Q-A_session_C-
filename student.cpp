#include "student.h"

student::student(string firstName,string lastName,int entertime,int numQuestions)
{
  this->firstName = firstName;
  this->lastName  = lastName;
  this->enterTime = enterTime;
  this->numQuestions = numQuestions;
  this->unanswered = numQuestions;
  this->laptopSerialNum = 0;
}
student::student(){
  
}
student::~student()
{
    //dtor
}
