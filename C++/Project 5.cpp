#include<iostream>
#include<iomanip>
#include<sstream>
using namespace std;
//enum structure
enum Board:char{noMeals='w', breakfast='b', halfBoard='h', allInclusive='a'};

ostream& operator<<(ostream& out, Board& Bo){   //for outputting enum type
    if(Bo==noMeals)
        return out<<"no meals";
    if(Bo==breakfast)
        return out<<"with breakfast";
    if(Bo==halfBoard)
        return out<<"half board";
    if(Bo==allInclusive)
        return out<<"all inclusive";
}
//class Date
class Date{
private:
    unsigned int daysInMonth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    short unsigned int day, month, year;
public:
    Date(short unsigned int d=1,short unsigned int m=1,short unsigned int y=1)
    :day(d), month(m), year(y)
    {}
    Date operator+(unsigned int dayOfn){
        day = (day+dayOfn)%daysInMonth[month-1];
        if(day+dayOfn>daysInMonth[month-1])
            month+1;
        if(month>12){
            month-=12;
        }
        if(month == 12){
            month=1;
            day=1;
            year++;
        }
        Date objCons(day, month ,year);
        return objCons;
    }
    friend istream& operator>>(istream& in, Date& objd){
        char sign;
        in>>objd.day>>sign>>objd.month>>sign>>objd.year;
        return in;
    }
    friend ostream& operator<<(ostream& out, Date& objd){
        out<<objd.day<<":"<<objd.month<<":"<<objd.year;
        return out;
    }
};
//class hotel
class Hotel{
private:
    string name;
    Date arrivalHotel;
    int nights, singles, doubles;
    Board bookBoard;
    double priceNightSingle, priceNightDouble;
    bool parking;
public:
    Hotel(string na, int ni=0, int si=0, int dub=0, double pns=0, double pnd=0, bool p=false, Board bB=noMeals)
    :name(na), nights(ni), singles(si), doubles(dub), priceNightSingle(pns), priceNightDouble(pnd), parking(p), bookBoard(bB)
    {}
    ~Hotel(){
        stringstream obj1;
        obj1<<"destructor hotel ";
        obj1<<name;
        obj1<<" at ";
        obj1<<arrivalHotel;
        obj1<<" for ";
        obj1<<get_guests();
        obj1<<" guests done";
        cout<<obj1.str()<<endl;
    }
    double get_price(){
        double price;
        price = (nights*(singles*priceNightSingle+doubles*priceNightDouble));
        if(parking=false)
            return price;
        else
            return (price+(10*nights));
    }
    Date get_arrival(){
        return arrivalHotel;
    }
    Date get_checkout(){
        Date check;
        check = arrivalHotel+nights;
        return check;

    }
    int get_guests(){
        int calc;
        calc = singles+(2*doubles);
        return calc;
    }
    void print(){
        stringstream obj2;
        obj2<<"hotel ";
        obj2<<arrivalHotel;
        obj2<<" ";
        obj2<<name;
        obj2<<" for ";
        obj2<<nights;
        obj2<<" night(s) ";
        obj2<<doubles;
        obj2<<" bed room(s) ";
        obj2<<singles;
        obj2<<" bed room(s)";
        if(parking==false)
        cout<<obj2.str()<<" "<<bookBoard<<endl;
        else{
            obj2<<" parking included";
            cout<<obj2.str()<<" "<<bookBoard<<endl;
        }

    }
};
//class transport
class Transport{
public:
    virtual ~Transport(){
        cout<<"destructor Transport done"<<endl;
    }
    virtual bool withTransfer()=0;
    virtual double get_price()=0;
    virtual void print()=0;
};
//class selforganised
class SelfOrganised: public Transport{
public:
    SelfOrganised(){}
    virtual ~SelfOrganised(){
        cout<<"destructor SelfOrganised done"<<endl;
    }
    virtual bool withTransfer(){
        return false;
    }
    virtual double get_price(){
        return 0.0;
    }
    virtual void print(){
        cout<<"self organized transport"<<endl;
    }
};
//class publictransport inheriting class transport as public
class PublicTransport: public Transport{
protected:
    Date forDeparture;
    string code, from, to;
    double priceOneSeat;
    bool firstClass;
public:
    PublicTransport(Date d, string c, string f, string t, double p, bool fc=false)
    :forDeparture(d), code(c), from(f), to(t), priceOneSeat(p), firstClass(fc)
    {}
    virtual ~PublicTransport(){
        stringstream obj1;
        obj1<<"destructor PublicTransport ";
        obj1<<code;
        obj1<<" at ";
        obj1<<forDeparture;
        obj1<<" done";
        cout<<obj1.str()<<endl;
    }
    virtual void print(){
        stringstream obj2;
        obj2<<forDeparture;
        obj2<<" ";
        obj2<<code;
        obj2<<" from ";
        obj2<<from;
        obj2<<" to ";
        obj2<<to;
        if(firstClass==false)
            cout<<obj2.str()<<endl;
        else{
            obj2<<" first class";
            cout<<obj2.str()<<endl;
        }
    }
};
//class flight inheriting publictransport as public
class Flight: public PublicTransport{
protected:
    bool transfer;
public:
    Flight(Date d, string codeOfFlight, string departure, string arrival, double priceSeat, bool fClass=false, bool trans = true)
    :PublicTransport(d, codeOfFlight, departure, arrival, priceSeat, fClass), transfer(trans)
    {}
    virtual ~Flight(){
        cout<<"destructor Flight done"<<endl;
    }
    virtual bool withTransfer(){
        return transfer;
    }
    virtual double get_price(){
        if(firstClass==true)
            return (2*priceOneSeat);
        else
            return priceOneSeat;
    }
    virtual void print(){
        string info;
        stringstream obj1;
        obj1<<"flight ";
        info= obj1.str();
        cout<<info<<" ";
        PublicTransport::print();
    }
};
//class train inheriting publictransport as public
class Train:public PublicTransport{
public:
    Train(Date d, string codeOfTrain, string departure, string arrival, double priceSeat, bool fClass=false)
    :PublicTransport(d, codeOfTrain, departure, arrival, priceSeat, fClass)
    {}
    virtual ~Train(){
        cout<<"destructor Train done"<<endl;
    }
    virtual bool withTransfer(){
        return false;
    }
    virtual double get_price(){
        if(firstClass==true)
            return (1.5*priceOneSeat);
        else
            return priceOneSeat;
    }
    virtual void print(){
        string info;
        stringstream obj1;
        obj1<<"train ";
        info= obj1.str();
        cout<<info<<" ";
        PublicTransport::print();
    }
};
//class trip
class Trip{
private:
    const unsigned int no;
    static unsigned int lastNo;
    unsigned int travellers;
    Hotel *hotel;
    Transport *transportOutward, *transportBack;
    Trip *next;
public:
    Trip(unsigned int num, Hotel *pointer, Transport *transout, Transport *transback, Trip* next1=nullptr)
    :travellers(num), hotel(pointer), transportOutward(transout), transportBack(transback), next(next1), no(++lastNo)
    {}
    virtual ~Trip(){
        delete []hotel;
        delete []transportOutward;
        delete []transportBack;
        cout<<"destructor Trip done"<<endl;
    }
    unsigned int get_no(){
        return no;
    }
    Trip* get_next(){
        return next;
    }
    Trip* set_next(Trip* sNext){
        next=sNext;
    }
    double get_price(){
        double result;
        result = travellers*(hotel->get_price()+transportOutward->get_price()+transportBack->get_price());
        return result;
    }
    void print(){
        cout<<"trip inquiry "<<no<<" for "<<travellers<<" person(s)"<<endl;
        cout<<"check-in: ";
        hotel->print();

        cout<<"outward journey: ";
        transportOutward->print();

        cout<<"journey back: ";
        transportBack->print();

        cout<<"price: "<<get_price()<<endl;
    }
};
unsigned int Trip::lastNo=0; //static variable initialize outside as 0
//class travelagency
class TravelAgency{
private:
    Trip *tripsHead;
public:
    TravelAgency(Trip* head = nullptr)
    :tripsHead(head)
    {}
    void add(Trip* head){
        head->set_next(tripsHead);
        tripsHead=head;
    }
    void removes(Trip* head){
        Trip* newHead = tripsHead;

        for(;newHead->get_next()!=nullptr;){
            Trip*newHead1=newHead->get_next();
            delete []newHead;
        }
    }
    Trip* searchs(int searching){
        Trip* newHead = tripsHead;
        for(;newHead!=nullptr;){
            if(newHead->get_no()!=searching){
                newHead= newHead->get_next();
            }else{
                return newHead;
            }
        }
    }
    void printAllTrips(){
        Trip* newHead = tripsHead;
        for(;newHead!=nullptr;){
            newHead->print();
            newHead=newHead->get_next();
        }
    }
};
//inline function for choosing enum types
inline void func_forChoose(){
    stringstream obj3;
    obj3<<"a all inclusive\n";
    obj3<<"b breakfast\n";
    obj3<<"h half board\n";
    obj3<<"w without meals";
    cout<<obj3.str()<<endl;
}
inline void func_forTransport(){    //inline function for transport printing
    stringstream obj4;
    obj4<<"0 self organised\n";
    obj4<<"1 by flight\n";
    obj4<<"2 by train";
    cout<<obj4.str()<<endl;
}
//main function
int main()
{
    TravelAgency tAgency;
    Board board;
    Date newDate;
    Transport* inWard;
    Transport* outWard;

    string nameHotel, depart, arriv, code;
    int day, month, year, num, noOfSingle, noOfdouble, numT;
    double priceSingle, priceDouble, price;
    char ch, ch2, ch3, ch4;
    bool class1, class2, class3;

    do{
       stringstream obj;
       obj<<"HOTEL TRAVEL AGENCY\n";
       obj<<"0 end\n";
       obj<<"1 new trip\n";
       obj<<"2 search trip\n";
       obj<<"3 show all trip offers\n";
       cout<<obj.str();

       cout<<"your choice: ";
       cin>>ch;
        if(ch == '0')
        break;
        if(ch=='1'){
            Date date;
            cout<<"name of hotel : ";
            cin.sync();
            getline(cin, nameHotel);
            cout<<"arrival on:";
            cin>>date;
            cout<<"how many nights: ";
            cin>>num;
            cout<<"how many single bed rooms: ";
            cin>>noOfSingle;
            cout<<"how many double bed rooms: ";
            cin>>noOfdouble;
            func_forChoose();
            cin>>ch4;
            board = static_cast<Board>(ch4);
            cout<<"price one night in single bed room: ";
            cin>>priceSingle;
            cout<<"price one night in double bed room: ";
            cin>>priceDouble;
            cout<<"with parking (1(yes) or 0(no): ";
            cin>>class3;

            Hotel *hotel= new Hotel(nameHotel, num, noOfSingle, noOfdouble,priceSingle, priceDouble, class3, board);

            cout<<"please choose transport for outward journey"<<endl;
            func_forTransport();
            cout<<"your choice: ";
            cin>>ch3;

            if(ch3=='0')
                outWard = new SelfOrganised;
            if(ch3=='1'){
                cout<<"code of flight: ";
                cin.sync();
                getline(cin, code);
                cout<<"airport of departure: ";
                cin.sync();
                getline(cin, depart);
                cout<<"airport of arrival: ";
                cin.sync();
                getline(cin, arriv);
                cout<<"price for one passenger: ";
                cin>>price;
                cout<<"1st class with(1) or without(0): ";
                cin>>class1;
                cout<<"transfer with(1) or without(0): ";
                cin>>class2;
                outWard = new Flight(date, code, depart, arriv, price, class1, class2);
            }
            if(ch3=='2'){
                cout<<"code of train: ";
                cin.sync();
                getline(cin, code);
                cout<<"main train station of departure: ";
                cin.sync();
                getline(cin, depart);
                cout<<"main train station of arrival: ";
                cin.sync();
                getline(cin, arriv);
                cout<<"price for one passenger: ";
                cin>>price;
                cout<<"1st class with(1) or without(0): ";
                cin>>class1;
                outWard = new Train(date, code, depart, arriv, price, class1);
            }

            cout<<"please choose transport for outward journey"<<endl;
            func_forTransport();
            cout<<"your choice: ";
            cin>>ch3;

            if(ch3=='0')
                inWard = new SelfOrganised;
            if(ch3=='1'){
                cout<<"code of flight: ";
                cin.sync();
                getline(cin, code);
                cout<<"airport of departure: ";
                cin.sync();
                getline(cin, depart);
                cout<<"airport of arrival: ";
                cin.sync();
                getline(cin, arriv);
                cout<<"price for one passenger: ";
                cin>>price;
                cout<<"1st class with(1) or without(0): ";
                cin>>class1;
                cout<<"transfer with(1) or without(0): ";
                cin>>class2;
                inWard = new Flight(date, code, depart, arriv, price, class1, class2);
            }
            if(ch3=='2'){
                cout<<"code of train: ";
                cin.sync();
                getline(cin, code);
                cout<<"main train station of departure: ";
                cin.sync();
                getline(cin, depart);
                cout<<"main train station of arrival: ";
                cin.sync();
                getline(cin, arriv);
                cout<<"price for one passenger: ";
                cin>>price;
                cout<<"1st class with(1) or without(0): ";
                cin>>class1;
                inWard = new Train(date, code, depart, arriv, price, class1);
            }
            Trip *trip = new Trip(hotel->get_guests(), hotel, outWard, inWard);
            tAgency.add(trip);

        }
        if(ch=='2'){
            cout<<"number of trip: ";
            cin>>numT;
            Trip *pointer;
            pointer=tAgency.searchs(numT);
            pointer->print();
            cout<<"(d)elete or (n)ot: ";
            cin>>ch2;
            if(ch2=='d')
                tAgency.removes(tAgency.searchs(numT));
        }
        if(ch=='3'){
            tAgency.printAllTrips();
        }
    }while(ch != '0');
    return 0;
}
