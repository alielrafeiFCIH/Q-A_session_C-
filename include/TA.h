#ifndef TA_H
#define TA_H
#include <bits/stdc++.h>
#include <student.h>
using namespace std;
class TA
{
    public:
        string name;    
        int startTimes[3];
        int endTimes[3]; 
        student *studentWithTA; 
        int minute;
        TA(string name,int s1,int s2,int s3,int e1,int e2,int e3);
        TA();
        virtual ~TA();

    protected:

    private:
};

#endif // TA_H
