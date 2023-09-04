#include "TA.h"

TA::TA(string name,int s1,int s2,int s3,int e1,int e2,int e3)
{
    this->name = name;
    this->startTimes[0]=s1;
    this->startTimes[1]=s2;
    this->startTimes[2]=s3; 
    
    this->endTimes[0]=e1;
    this->endTimes[1]=e2;
    this->endTimes[2]=e3;

    this->minute = 0;
    this->studentWithTA=NULL;
    
}
TA::TA(){
  
}
TA::~TA()
{
    //dtor
}
