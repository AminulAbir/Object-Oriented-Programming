/******************************
Task No. : H1
Last Name: ISLAM
First Name: MD AMINUL
Matriculation Number: 3070939
Uni-Email: md.islam.aminul@stud.uni-due.de
Course of Study: ISE CE
*******************************/

#include<iostream>
#include<cstdlib>
#include<string>
#include<iomanip>

using namespace std;

const int MAX_ARRAY = 20;  //constant variable (length of array)
int counts = 0;             //global variable

//enumeration (Task 1)
enum Phn_type: char{
    home = 'h',
    work = 'w',
    fax= 'f',
    mobile = 'm',
    other = 'o'
};

//structure for name, number & type (Task 2)
struct Contact_var{
    string name, number;
    Phn_type obj;
};
Contact_var contact[MAX_ARRAY]; //structure type global array


bool add_data(void); //bool return type function for adding contacts (Task 3)

bool delete_data(void); //bool return type function for deleting data (Task 4)

void enum_func(Phn_type input); //for contact type function

void contact_sorting(void); //function for sorting the contacts and printing them (Task 5)


//main function for inputing a new contact (Task 6)
int main()
{
    int choose;
    do{
        cout<<"*** "<<counts<<ends<<"contacts entries ***"<<endl;
        cout<<"0 end"<<endl<<"1 new contact"<<endl<<"2 delete contact"<<endl<<"3 show all contacts"<<endl<<"9 empty contact memory"<<endl;
        cin>>choose;

    if(choose != 0){
        switch(choose){
        case 1:
            if(add_data()==1){
                cout<<"Contact stored!"<<endl;
            }else{
                cout<<"Try again!"<<endl;
            }
            break;
        case 2:
            if(delete_data()==1){
                cout<<"Contact deleted!"<<endl;
            }else{
                cout<<"Contact not found. Please check your entries!"<<endl;
            }
            break;
        case 3:
            if(counts==0){
                cout<<"No contact entries"<<endl;
            }else{
            contact_sorting();
            }
            break;
        case 9:
            delete[] contact;
            counts = 0;
            cout<<"All contacts deleted!"<<endl;
            break;
        default:
            cout<<"Please check your keywords"<<endl;
        }
    }

    }while(choose != 0);

    return 0;
}
bool add_data(void){
    if(counts == MAX_ARRAY){
        return false;
    }else{
    char ch;

    cout<<"Please enter phone number: ";
    cin.sync();
    getline(cin,contact[counts].number);


    cout<<"Please enter name: ";
    cin.sync();
    getline(cin, contact[counts].name);

    cout<<"Type of number (f for fax, h for home, m for mobile, w for work, o for other): ";
    cin>>ch;
    contact[counts].obj= static_cast<Phn_type>(ch); //to convert char type into Phn_type

    counts++; //for each addition of contacts counts will be increased

    return true;
    }
}

bool delete_data(void){
    string searching;

    cout<<"Enter the name which you want to delete"<<endl;
    cin.sync();
    getline(cin,searching);

    //comparing the inputed string with other string and then delete that
    for(int i=0; i<counts; i++){
        if(searching.compare(contact[i].name)==0){
            for(int j=i; j<counts-1; j++){
                contact[j]=contact[j+1]; //By swapping the selected name will be at last array
            }
            counts--; //after deleting counts will be decreased
            return true;
        }
    }
    return false;
}

void enum_func(Phn_type input){
//here we compare with ASCII value of char data
    switch(input){
        case 102: cout<<"(Fax)"<<endl;
                    break;
        case 104: cout<<"(Home)"<<endl;
                    break;
        case 109: cout<<"(Mobile)"<<endl;
                    break;
        case 119: cout<<"(Work)"<<endl;
                    break;
        case 111: cout<<"(Other)"<<endl;
                    break;
        default: cout<<"Please check your keywords"<<endl;
    }
}

void contact_sorting(void){
    //Sorting is performed here
    for(int i=0; i<counts-1; i++){
        for(int j=0; j<counts-1-i; j++){
            if((contact[j].name).compare(contact[j+1].name)>0){
                swap(contact[j],contact[j+1]);
            }
        }
    }
    //Printing out contacts
    for(int k=0; k<counts; k++){
        cout<<left<<setw(26)<<contact[k].name<<setw(26)<<contact[k].number;
        enum_func(contact[k].obj);
    }
}
