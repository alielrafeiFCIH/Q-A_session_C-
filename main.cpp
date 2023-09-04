#include <bits/stdc++.h>
#include "include/student.h"
#include "include/TA.h"
#include "include/Stack.h"
#include "include/Queue.h"
using namespace std;
const int N = 30;
const int M = 300;
Stack<int>laptops(300);
Queue<student>lap_queue(300);
Queue<student>ta_queue(300);
TA working_tas[N];
student students[M];
typedef struct vis
{
    string name;
    int startday[3];
    int vis=0;
};

vis visited[N];

string weak[3] ={"Monday:","Tuesday:","Wednesday:"}; 
bool comp(TA ta1,TA ta2){
    return ta1.name<ta2.name;
}
int num_of_students,num_of_laptops,num_of_ta,happy_student,global_time,active_duty,num_of_students_visted;
bool day_ended=false;
void update_stack_laptop(int time,int day,bool is_end_day);
void update_line_status(int time,int day);
void go_to_lap_line(student s,int num);
void update_ta_queue(int time,int day);
void end_day(TA last_one,int time,int day);

string fix_date(int time);

int main() {
	#   ifdef LOCAL_PROJECT
        freopen("in.txt", "r", stdin);
        freopen("myout.txt", "w", stdout);
    #   endif
    int serial,idx=0,test_case=1;
    cin>>num_of_laptops;
    for(int i=0;i<num_of_laptops;i++){
        cin>>serial;
        laptops.push(serial);
    }
    string ta_name,st_name,ls_name;
    int s1, e1, s2, e2, s3, e3,start,no_of_questions,process;
    cin>>num_of_ta;
    for(int i=0;i<num_of_ta;i++){
        cin>>ta_name>>s1>>e1>>s2>>e2>>s3>>e3;
        working_tas[idx].name=ta_name;
        working_tas[idx].startTimes[0]=s1;
        working_tas[idx].endTimes[0]=e1;
        
        working_tas[idx].startTimes[1]=s2;
        working_tas[idx].endTimes[1]=e2;
        
        working_tas[idx].startTimes[2]=s3;
        working_tas[idx].endTimes[2]=e3;
        visited[idx].name = ta_name;
        visited[idx].vis = 0;
        visited[idx].vis = 0;
        visited[idx].startday[0] = s1;
        visited[idx].startday[1] = s2;
        visited[idx].startday[2] = s3;
        
        
        idx++;
    }
    sort(working_tas,working_tas+idx,comp);
    cin>>process;
    while(process--){
        
        cout<<"**********\nProgram "<<test_case<<":\n**********\n\n";

        int mn=INT_MAX,open_ta,minute=0;
        for(int day=0;day<3;day++){// 3 days loop
            
            cin>>num_of_students;    
            for(int i=0;i<num_of_students;i++){// entering students for the current day
                cin>>start>>st_name>>ls_name>>no_of_questions;
                students[i].firstName=st_name;
                students[i].lastName=ls_name;
                students[i].enterTime=start;
                students[i].numQuestions=no_of_questions;
                students[i].unanswered = no_of_questions;
            }
            
            for(int i=0;i<num_of_ta;i++){
                for(int j=0;j<num_of_ta;j++){
                        if(visited[i].name==working_tas[j].name){
                            working_tas[j].startTimes[0]=visited[i].startday[0];
                            working_tas[j].startTimes[1]=visited[i].startday[1];
                            working_tas[j].startTimes[2]=visited[i].startday[2];
                        }
                }
            } 
            // find the ta who will open the lab
            for(int i=0;i<num_of_ta;i++){
                if(working_tas[i].startTimes[day]<mn){
                    open_ta=i;
                    mn = working_tas[i].startTimes[day];
                }
                visited[i].vis=0;
            }
            cout<<weak[day]<<"\n\n";
            // set all all variables for the next simulation 
            global_time=mn;
            day_ended = false;
            num_of_students_visted=0;
            happy_student=0;
            active_duty = num_of_ta;
            
            while(!day_ended&&global_time<480){// running summiulation 
                 if(!day_ended)
                  update_stack_laptop(global_time,day,false);
                 else break;

                update_ta_queue(global_time,day);
              
               if(!day_ended)
                   update_line_status(global_time,day);
                else break;
               global_time++;
               
            }
           
        }
        
      
        
        test_case++;
    }
    
    return 0;
}
string fix_date(int time){
    // this function fix the number of minutes to return this format HH:MM
    string s_time;
    int h = time/60;
    int m = time%60;
    h = (h+12)%12;
    if(h==0)h=12;
    if(h<12){
        stringstream ss;
        string hours;
        ss<<h;
        ss>>hours;
        hours = hours+":";
         s_time=hours;
    }else{
         stringstream ss;
        string hours;
        ss<<h;
        ss>>hours;
        s_time=hours+":";
       
    }
    if(m<10){
         stringstream ss;
        string mint;
        ss<<m;
        ss>>mint;
        mint = s_time+"0"+mint;
        s_time=mint;
    }else{
        stringstream ss;
        string hours;
        ss<<m;
        ss>>hours;
         s_time+=hours;
    }
    return s_time;
}
void go_out_of_lab(TA tec){
    // this function mark the tA that has finished his lab hours and decrease no of active TAs
    for(int j=0;j<num_of_ta;j++){
            if(visited[j].name==tec.name){
                        if(visited[j].vis!=1){
                            visited[j].vis=1;
                            active_duty--;
                            break;
                        }
            }
        }
}

void end_day(TA last_one,int time,int day){
    // this function end the day as all students return back the laptops they have borrowed 
    day_ended=true;
    update_stack_laptop(time,day,true);
    cout<<fix_date(time)<<" PM: "<<last_one.name<<" has finished lab hours.\n";
    cout<<fix_date(time)<<" PM: "<<"There are no TAs on duty.  TA#007 is now closed.\n";
    while(time-last_one.studentWithTA->enterTime<5){
        time++;
        if(!ta_queue.empty()){
            auto student = ta_queue.front();
            student.enterTime = time;
            lap_queue.push(student);
            ta_queue.pop();
            update_stack_laptop(time,day,true);
        }
        
    }
    student s;
    if(last_one.studentWithTA!=NULL)
     s= *last_one.studentWithTA;
    while(!ta_queue.empty()){
        auto ss = ta_queue.front();
        lap_queue.push(ss);
        ta_queue.pop();
       
    }
    if(last_one.studentWithTA != NULL){
        cout<<fix_date(time)<<" PM: "<<s.firstName<<" "<<s.lastName<<" has had one question answered, but must now return the laptop and exit the lab.\n";
        s.unanswered--;
        lap_queue.push(s);
    }
    for(int i=0;i<num_of_ta;i++){
        working_tas[i].studentWithTA=NULL;
        visited[i].vis=0;
    }
    
    while(!lap_queue.empty()){
        time++;
        update_stack_laptop(time,day,true);
    }
    cout<<"\n\n"<<weak[day]<<"'s  Lab Summary:\n";  
    cout<<"The TA Lab was open for "<<time/60<<" hours and "<<time%60<<" minutes.\n";
    cout<<num_of_students_visted<<" students visited the lab.  Out of those students, only "<<happy_student<<" left happy.\n";
    cout<<"The remaining left frustrated.\n\n";
    cout<<"Lesson Learned:  Do not procrastinate!  Start programs early!\n\n";
}

void update_ta_queue(int time,int day){
    for(int i=0;i<num_of_ta;i++){
       if(visited[i].name==working_tas[i].name&&visited[i].vis==1 || working_tas[i].startTimes[day]>time){// rg3l mga4 
           //do nothing
       }else if(working_tas[i].startTimes[day]==time && working_tas[i].endTimes[day]>time){//ta enter the lab
            working_tas[i].startTimes[day]=-1;
            cout<<fix_date(time)<<" PM: "<<working_tas[i].name<<" has begun lab hours.\n";
            if(!ta_queue.empty()){// there is a student in the ta queue
                working_tas[i].studentWithTA=&ta_queue.front();
                working_tas[i].studentWithTA->enterTime=time;
                ta_queue.pop();
                cout<<fix_date(time)<<" PM: "<<working_tas[i].studentWithTA->firstName<<" "<<working_tas[i].studentWithTA->lastName<<" is getting help from "<<working_tas[i].name<<".\n";
               
            }
       }else if(working_tas[i].startTimes[day]==0&&working_tas[i].endTimes[day]==0){//ta will not attend to day mark them  
            go_out_of_lab(working_tas[i]);
       }else if(working_tas[i].studentWithTA==NULL&&working_tas[i].endTimes[day]>=time){//ta will mark a student and finish time < time
              if(!ta_queue.empty()){// there is a student in the ta queue
                working_tas[i].studentWithTA=&ta_queue.front();
                working_tas[i].studentWithTA->enterTime=time;
                ta_queue.pop();
                cout<<fix_date(time)<<" PM: "<<working_tas[i].studentWithTA->firstName<<" "<<working_tas[i].studentWithTA->lastName<<" is getting help from "<<working_tas[i].name<<".\n";
               
            }  
       }else if(working_tas[i].studentWithTA!=NULL){
          
                if(time-working_tas[i].studentWithTA->enterTime==5){
                    if(working_tas[i].endTimes[day]>time){
                        working_tas[i].studentWithTA->unanswered--;
                        if(working_tas[i].studentWithTA->unanswered>0){
                            cout<<fix_date(time)<<" PM: "<<working_tas[i].studentWithTA->firstName<<" "<<working_tas[i].studentWithTA->lastName<<" has had one question answered and gotten back in line.\n";
                            ta_queue.push(*working_tas[i].studentWithTA);                            
                            working_tas[i].studentWithTA=&ta_queue.front();                            
                            working_tas[i].studentWithTA->enterTime = time;
                            cout<<fix_date(time)<<" PM: "<<working_tas[i].studentWithTA->firstName<<" "<<working_tas[i].studentWithTA->lastName<<" is getting help from "<<working_tas[i].name<<".\n";
                            ta_queue.pop();

                        }else{
                            cout<<fix_date(time)<<" PM: "<<working_tas[i].studentWithTA->firstName<<" "<<working_tas[i].studentWithTA->lastName<<" has no more questions and will now return the laptop.\n";
                            working_tas[i].studentWithTA->enterTime=time;
                            lap_queue.push(*working_tas[i].studentWithTA);
                            if(!ta_queue.empty()){
                                 working_tas[i].studentWithTA=&ta_queue.front();
                                 working_tas[i].studentWithTA->enterTime = time;
                                 cout<<fix_date(time)<<" PM: "<<working_tas[i].studentWithTA->firstName<<" "<<working_tas[i].studentWithTA->lastName<<" is getting help from "<<working_tas[i].name<<".\n";
                                 ta_queue.pop();
                            }else{
                                working_tas[i].studentWithTA=NULL;
                            }
                            
                            
                        }
                    
                    }else if(active_duty==1 &&working_tas[i].endTimes[day]==time){
                        end_day(working_tas[i],time,day);
                        return ;
                    }else if(active_duty>1 &&working_tas[i].endTimes[day]==time){
                       cout<<fix_date(time)<<" PM: "<<working_tas[i].name<<" has finished lab hours.\n";
                            working_tas[i].studentWithTA->unanswered--;
                            if(working_tas[i].studentWithTA->unanswered>0){
                                cout<<fix_date(time)<<" PM: "<<working_tas[i].studentWithTA->firstName<<" "<<working_tas[i].studentWithTA->lastName<<" has had one question answered and gotten back in line.\n";                                
                                ta_queue.push(*working_tas[i].studentWithTA);
                                working_tas[i].studentWithTA=NULL;
                                for(int j = 0;j<num_of_ta;j++){
                                    if(visited[i].name==working_tas[i].name&&visited[i].vis==1)continue;
                                        if(working_tas[i].studentWithTA==NULL&&working_tas[i].endTimes[day]>=time){
                                            working_tas[i].studentWithTA=&ta_queue.front();
                                            working_tas[i].studentWithTA->enterTime = time;
                                            break;                                            
                                        }
                                }
                                
                            }else{
                                cout<<fix_date(time)<<" PM: "<<working_tas[i].studentWithTA->firstName<<" "<<working_tas[i].studentWithTA->lastName<<" has no more questions and will now return the laptop.\n";
                                working_tas[i].studentWithTA->enterTime=time;
                                lap_queue.push(*working_tas[i].studentWithTA);
                                working_tas[i].studentWithTA==NULL;   
                            }
                             go_out_of_lab(working_tas[i]); 
                        
                        
                    }else if(active_duty>1 &&working_tas[i].endTimes[day]<time){
                        working_tas[i].studentWithTA->unanswered--;
                         if(working_tas[i].studentWithTA->unanswered>0){
                                cout<<fix_date(time)<<" PM: "<<working_tas[i].studentWithTA->firstName<<" "<<working_tas[i].studentWithTA->lastName<<" has had one question answered and gotten back in line.\n";                                
                                ta_queue.push(*working_tas[i].studentWithTA);
                                working_tas[i].studentWithTA==NULL;
                                for(int j = 0;j<num_of_ta;j++){
                                    if(visited[i].name==working_tas[i].name&&visited[i].vis==1)continue;
                                        if(working_tas[i].studentWithTA==NULL&&working_tas[i].endTimes[day]>=time){
                                            working_tas[i].studentWithTA=&ta_queue.front();
                                            working_tas[i].studentWithTA->enterTime = time;
                                            break;                                            
                                        }
                                }
                            }else{
                                cout<<fix_date(time)<<" PM: "<<working_tas[i].studentWithTA->firstName<<" "<<working_tas[i].studentWithTA->lastName<<" has no more questions and will now return the laptop.\n";
                                working_tas[i].studentWithTA->enterTime=time;
                                lap_queue.push(*working_tas[i].studentWithTA);
                                working_tas[i].studentWithTA==NULL;   
                            }
                            go_out_of_lab(working_tas[i]); 
                    }
                }else {
                    if(active_duty==1&&working_tas[i].endTimes[day]<=time){
                         end_day(working_tas[i],time,day);
                         return ;
                    }else if(active_duty>1&&working_tas[i].endTimes[day]==time){
                        cout<<fix_date(time)<<" PM: "<<working_tas[i].name<<" has finished lab hours.\n";
                    }
                }
       }else if(working_tas[i].studentWithTA==NULL && working_tas[i].endTimes[day]<time){//ta end== time and he is free

            if(active_duty==1){// he was the last one so he will close the lab 
                end_day(working_tas[i],time,day);
                return ;
            }else{
                go_out_of_lab(working_tas[i]);
            }
       }
    }
}
void go_to_lap_line(student s,int num){
    //this function push student to the laptop queue
    auto x = s;
    x.enterTime = num;
    lap_queue.push(x);
    
}
void update_line_status(int time,int day){
    // this function check to see if any student has arrived at this current time 
    for(int i=0;i<num_of_students;i++){
        if(time==students[i].enterTime){
            cout<<fix_date(time)<<" PM: "<<students[i].firstName<<" "<<students[i].lastName<<" has arrived in TA#007.\n";
            num_of_students_visted++;
            go_to_lap_line(students[i],time);
            
        }
    }
}
void update_stack_laptop(int time,int day,bool is_end_day){
    // here there is a flag that indicate if the day is ending or not 
    if(!is_end_day){
        if(!lap_queue.empty()){
            auto student = lap_queue.front();
            if(time-student.enterTime<2){// as the document said student will wait 2 min either to return or get a laptop
                return ;
            }
            if(student.unanswered>0){//  if the student is a fresh student he will pick a laptop and go the ta queue 
                lap_queue.pop();
                cout<<fix_date(time)<<" PM: "<<student.firstName<<" "<<student.lastName <<" has borrowed laptop "<<laptops.top() <<" and moved to the TA line.\n";
                student.laptopSerialNum=laptops.top();
                laptops.pop();
                ta_queue.push(student);
            }else{// else he will return the laptop that he had borrowed and go home happy
                lap_queue.pop();
                cout<<fix_date(time)<<" PM: "<<student.firstName<<" "<<student.lastName<<" has returned laptop "<<student.laptopSerialNum<<" and went home HAPPY.\n";
                laptops.push(student.laptopSerialNum);
                happy_student++;
            }
        }    
    }else{
        // this part is all about the end of the day 
        if(!lap_queue.empty()){
            auto student = lap_queue.front();
            lap_queue.pop();
            if(student.laptopSerialNum==0){ // if a student came late he will never get a laptop
                        cout<<fix_date(time)<<" PM: "<<student.firstName<<" "<<student.lastName<<" never even got a laptop and went home FRUSTRATED.\n";
            }else{
                int  degree = (int)ceil(1.0*student.numQuestions *3.0/4.0);// calculating his degree of unanswered questions
                int  diff = student.numQuestions - student.unanswered;
                if(degree>diff){// if less than 75% he will go home sad 
                    cout<<fix_date(time)<<" PM: "<<student.firstName<<" "<<student.lastName<<" has returned laptop "<<student.laptopSerialNum<<" and went home FRUSTRATED.\n";
                            laptops.push(student.laptopSerialNum);
                }else{      // more than he will go home happy 
                            cout<<fix_date(time)<<" PM: "<<student.firstName<<" "<<student.lastName<<" has returned laptop "<<student.laptopSerialNum<<" and went home HAPPY.\n";
                            laptops.push(student.laptopSerialNum);
                            happy_student++;
                }
            }
        
    }
    
   
}
}
