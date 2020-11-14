#include<iostream>
#include<string>
#include<fstream>
using namespace std;
//enum type for code or diagnosis entries
enum type{code,diagnosis};
//class to make the list and make the functions as public
class ICDisease{
private:
    string Code, Diagnosis;
    ICDisease *next;
public:
    friend ICDisease* reading_ICD(void);
    friend char uppercase(string s);
    friend string lowercase(string s);
    friend bool stringForcomp(string toCompare, string withCompare);
    friend void funcForsearch(ICDisease* ptr, string searchString, type CD);
};

//make the head pointer as global
ICDisease *head = nullptr;
//function for reading the file and make it as list
ICDisease* reading_ICD(void)
{
    ICDisease *newPtr;
    string save;
    ifstream file;
    file.open("Section111ValidICD10-2018.csv");
    if(!file.is_open()){
        cerr<<"There is no file such a name available"<<endl;
        exit(EXIT_FAILURE);
    }else{
        if(file.good()){
            getline(file, save);
            for(;!file.eof();){
                ICDisease *ptr = new ICDisease;
                getline(file, ptr->Code, ';');
                getline(file, ptr->Diagnosis, '\n');
                ptr->next = nullptr;
                newPtr = head;
                if(head != nullptr){
                    for(;newPtr->next != nullptr;){
                        newPtr = newPtr->next;
                    }
                newPtr->next = ptr;
                }else{
                    head = ptr;
                }
            }
        }
    }
}
//function for having a upper case latter
char uppercase(string select)
{
    int i = 0;
        if(select[i]>='a' && select[i]<='z')
		{
            select[i]=select[i]-32;
        }
    return select[i];
}
//function for lower case latter
string lowercase(string select)
{
    int i = 0;
    for(;select[i]!='\0';)
    {
        if(select[i]>='A' && select[i]<='Z')
		{
            select[i]=select[i]+32;
        }
        ++i;
    }
    return select;
}
//bool type function in order to compare the strings and substrings
bool stringForcomp(string toCompare, string withCompare){
    int icount=0;
    int scount=1;
    int tcount =0;
    bool return_type =true;

    for(;withCompare[icount]!='\0';)
    {
        if(withCompare[icount]==toCompare[0])
        {
            tcount=icount+1;
            for(;toCompare[scount]!='\0';)
            {
                if(toCompare[scount]!=withCompare[tcount])
                return_type = false;

                tcount=tcount+1;
                scount=scount+1;
            }
            if(return_type)
                return true;
        }
        icount=icount+1;
    }
    return false;
}
//function for search the diseases
void funcForsearch(ICDisease* ptr, string searchString, type CD){
    int k = 0;
    int counts = 0;
    string newSave;
    newSave = lowercase(searchString);
    newSave[k] = uppercase(searchString);

    for(;ptr != nullptr;){
        if(CD){
            if(stringForcomp(newSave, ptr->Diagnosis)||stringForcomp(searchString, ptr->Diagnosis)){
                cout<<ptr->Code<<"\t\t"<<ptr->Diagnosis<<endl;
                counts++;
            }
            }else{
                if(stringForcomp(newSave, ptr->Code)||stringForcomp(searchString, ptr->Code)){
                cout<<ptr->Code<<"\t\t"<<ptr->Diagnosis<<endl;
                counts++;
                }
            }
            ptr = ptr->next;
    }
    switch(counts){
    case 0:
        cout<<"No entries found"<<endl;
        break;
    case 1:
        cout<<"One entry found"<<endl;
        break;
    default:
        cout<<counts<<" entries found"<<endl;
    }
}
//main function
int main()
{
    char ch;
    reading_ICD();
    string IcdCode, Diagnos_code;
    cout<<"World Health Organization (WHO)"<<endl<<"International Classification for Diseases (ICD)";

    do{
        cout<<endl<<"0 end"<<endl<<"1 search for ICD code(s) (e.g. G4453)"<<endl<<"2 search for diagnosis(s) (e.g. angina, Ebola, horse, Malaria, wheelchair)"<<endl;
        cin>>ch;
        switch(ch){
            case '0':
                cout<<"Thanks for using!!!"<<endl;
                 break;
            case '1':
                cout<<"to search for ICD code: ";
                cin>>IcdCode;
                funcForsearch(head, IcdCode, code);
                break;
            case '2':
                cout<<"to search for diagnosis: ";
                cin>>Diagnos_code;
                funcForsearch(head, Diagnos_code, diagnosis);
                break;
        }

    }while(ch != '0');
}
