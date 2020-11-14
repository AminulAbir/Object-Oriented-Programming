/******************************
Task No. : H4
Last Name: ISLAM
First Name: MD AMINUL
Matriculation Number: 3070939
Uni-Email: md.islam.aminul@stud.uni-due.de
Course of Study: ISE CE
*******************************/
#include<iostream>
#include<iomanip>
using namespace std;
const int max1 = 1440;  //two global variables
const int max2 = 15;
//class time to calculate time and also add the from time to time
class Time{
private:
    unsigned int minuteOfDay;
public:
    Time(unsigned int var1=0)
    :minuteOfDay(var1)
    {
        if(var1>(max1))
            var1 -= (max1);
            minuteOfDay = var1;
    }
    Time(int hour, int minute){
        set_time(hour, minute);
    }
    void set_time(int hour, int minute){
        if(hour>24||minute>60){
            cout<<"Incorrect timing u have entered, please try again!"<<endl;
            return;
        }
            minuteOfDay=(hour*60)+minute;

    }
    int get_hour(){
        return (minuteOfDay/60);

    }
    int get_minute(){
        return (minuteOfDay%60);
    }
    int get_minuteOfDay(){
        return minuteOfDay;
    }
    Time operator+(unsigned int time_value){    //it is used to detect from-to time
        return Time(minuteOfDay+time_value);
    }
};
istream& operator>>(istream& in, Time &inOP){   //istream operator used for input the time
    int h, m; char s;
    in>>h>>s>>m;
    inOP.set_time(h,m);
    return in;
}
ostream& operator<<(ostream& out, Time &outOP){    //ostream operator used for output the time
    if(outOP.get_hour()<=9)
    out<<"0";
    out<<outOP.get_hour()<<":";
    if(outOP.get_minute()<=9)
    out<<"0";
    out<<outOP.get_minute();
    return out;
}
//class train used for train information
class Train{
private:
    string no, to, over;
public:
    Train(string n, string t, string o);
    ~Train();
    string get_no();
    string get_to();
    string get_over();
};
Train::Train(string n, string t, string o){
    no = n;
    to = t;
    over = o;
}
Train::~Train(){
    cout<<left<<setw(5)<<no<<setw(47)<<over<<setw(15)<<to;
}
string Train::get_no(){
    return no;
}
string Train::get_to(){
    return to;
}
string Train::get_over(){
    return over;
}
//class station for platforms and add and show departures
class Station{
private:
    const string station;
    const unsigned int platforms=15;
    Train *schedule[1440][15];
public:
    Station(const string var2)
    : station(var2)
    {
        for(int i=0; i<max1; i++){
            for(int j=0; j<max2; j++){
                schedule[i][j]=nullptr;
            }
        }
    }
    ~Station(){     //destruction for deleting the objects/array informations
        for(int i=0; i<max1; i++){
            for(int j=0; j<max2; j++){
                if(schedule[i][j]!=nullptr){
                    forCalculation(i);
                cout<<"platform: "<<j<<" "<<"Train "<<schedule[i][j]->get_no()<<" "<<"to "<<schedule[i][j]->get_to()<<" deleted"<<endl;
                }
            }
        }
        delete []schedule;
        cout<<"schedule for DUISBURG MAIN TRAIN STATION completely deleted"<<endl;
    }
    void addDeparture(Time time, unsigned int platform, Train *pointer){
        unsigned int arrayVAr;
        arrayVAr=time.get_minuteOfDay();
        schedule[arrayVAr][platform] = pointer;
    }
    void showDepartures(Time time, unsigned int minutes){
        Time addTIme = time+minutes;
        cout<<"DUISBURG MAIN TRAIN STATION"<<endl;
        cout<<"DEPARTURES "<<time<<"-"<<addTIme<<endl;
        cout<<"======================"<<endl;
       cout<<left<<setw(6)<<"Time"<<setw(7)<<"Train"<<setw(50)<<"over"<<setw(18)<<"to"<<"platform"<<endl;
        unsigned int store = time.get_minuteOfDay();
        unsigned int store1 = store+minutes;
        for(int i = store; i<store1; i++){
           for(int j=0; j<max2; j++){
                   if(schedule[i][j]!=nullptr){
                    forCalculation(i);
                cout<<left<<setw(7)<<schedule[i][j]->get_no()<<setw(50)<<schedule[i][j]->get_over()<<setw(17)<<schedule[i][j]->get_to()<<" "<<j<<endl;
                cout<<"\n";
            }
        }
    }
  }
    void forCalculation(int var){       //for calculating the time alternative can be used from Time class
        if(var/60 <= 9){
            cout<<"0";
        }
        cout<<var/60<<":";
        if(var%60<=9){
            cout<<"0";
        }
        cout<<var%60<<" ";
    }
};
//main function
int main()
{
    unsigned int nextMinute, platform;
    string no, to, over;
    char ch;
    Station duisburg("DUISBURG MAIN TRAIN STATION");
    int comp = 0;
    while(comp<24){     //examples of informations
        Train *s_bahn1=new Train("S1","Dortmund Hbf","Muelheim(Ruhr) Styrum - Muelheim(Ruhr) - Essen");
        Train *s_bahn2=new Train("S1","Solingen Hbf","Duisburg-Schlenk -Duesseldorf Flughafen");
        Train *s_bahn3=new Train("S2","Dortmund Hbf","Oberhausen - Gelsenkirchen - Wanne-Eickel");
        Train *re_bahn1=new Train("RE1","Aachen Hbf","Duesseldorf Flughafen - Duesseldorf - Koeln");
        Train *re_bahn2=new Train("RE2","Muenster Hbf","Muelheim(Ruhr) - Essen - Gelsenkirchen");

        Time forTime(comp,07);
        //for S1 and time star with :07 after each 20 minute
        duisburg.addDeparture(forTime,9,s_bahn1);
        Time forTime1=forTime+20;
        duisburg.addDeparture(forTime1,9,s_bahn1);
        forTime1=forTime1+20;
        duisburg.addDeparture(forTime1,9,s_bahn1);
        //for S2 and time star after each 20 minute
        Time forTime2=forTime+8;
        duisburg.addDeparture(forTime2,5,s_bahn2);
        forTime2=forTime2+20;
        duisburg.addDeparture(forTime2,5,s_bahn2);
        forTime2=forTime2+20;
        duisburg.addDeparture(forTime2,5,s_bahn2);
        //for S3 and time star after each 1 hour
        Time forTime3 = forTime+28;
        duisburg.addDeparture(forTime3,2,s_bahn3);
        forTime3 = forTime3+60;
        duisburg.addDeparture(forTime3,2,s_bahn3);
        //for RE1 and time star after each 1 hour
        Time forTime4 = forTime+15;
        duisburg.addDeparture(forTime4,4,re_bahn1);
        //for RE2 and time star after each 1 hour
        Time forTime5 = forTime+17;
        duisburg.addDeparture(forTime5,10,re_bahn2);

        comp++;
    }
    do{     //small menu function using do-while loop
        cout<<"0 end"<<endl<<"1 schedule train"<<endl<<"2 show schedule"<<endl;
        cin>>ch;
        Time objTime;
            if(ch=='0') break;

            if(ch=='1'){
                cout<<"time of departure? ";
                cin>>objTime;
                cout<<"platform? ";
                cin>>platform;
                cout<<"train? ";
                cin>>no;
                cout<<"to? ";
                cin.sync();
                getline(cin, to);
                cout<<"over? ";
                cin.sync();
                getline(cin,over);
                Train *pointer=new Train(no,to,over);
                duisburg.addDeparture(objTime, platform, pointer);
            }

            if(ch == '2'){
                cout<<"show departures starting at? ";
                cin>>objTime;
                cout<<"for how many next minutes? ";
                cin>>nextMinute;
                duisburg.showDepartures(objTime,nextMinute);
            }
    }while(ch!='0');
    return 0;
}
