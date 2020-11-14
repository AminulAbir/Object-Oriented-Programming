#include<iostream>
#include<iomanip>

using namespace std;
//structure for the list (Task 1)
struct Sofconfunc
{
    int cf;
    Sofconfunc *next;
};

Sofconfunc* funcForinsert(Sofconfunc *ptrIns, int value); //function for inserting n+1 element (Task 2)

void funcFordelete(Sofconfunc *ptrDel); //function for delete all nodes (Task 3)

double funcForcalc(Sofconfunc *ptrCalc); //function for calculating the continued fraction (Task 4)

Sofconfunc* funcForimplement(void); //function for implementing the elements (Task 5)
//main function to call all the function and others (Task 6)
int main()
{   //declaring the pointers
    Sofconfunc *headRoot1 = nullptr;
    Sofconfunc *headRoot2 = nullptr;
    Sofconfunc *headRoot3 = nullptr;
    int a=1, b=4, c=2, d=7; //implementing the local variables
    double result;
    //calling functions for cf1
    headRoot1 = funcForinsert(headRoot1, a);
    funcForinsert(headRoot1, b);
    funcForinsert(headRoot1, c);
    funcForinsert(headRoot1, a);
    funcForinsert(headRoot1, d);

    cout<<"cf1 = 123/100 = ";
    result = funcForcalc(headRoot1);
    cout<<fixed<<setprecision(2);
    cout<<result<<endl;
    funcFordelete(headRoot1);

    a=1, b=2, c=3;
    result = 0;
    //calling functions for cf2
    headRoot2 = funcForinsert(headRoot2, a);
    funcForinsert(headRoot2, a);
    funcForinsert(headRoot2, b);
    funcForinsert(headRoot2, c);

    cout<<"\ncf2 = 17/10 = ";
    result = funcForcalc(headRoot2);
    cout<<fixed<<setprecision(1);
    cout<<result<<endl;
    funcFordelete(headRoot2);

    result = 0;
    //calling functions for cf3
    headRoot3 = funcForimplement();
    result = funcForcalc(headRoot3);
    cout<<fixed<<setprecision(15);
    cout<<result<<endl;
    funcFordelete(headRoot3);

    return 0;
}
//functions definitions
Sofconfunc* funcForinsert(Sofconfunc *ptrIns, int value)
{
    Sofconfunc *ptrNew = new Sofconfunc;
    ptrNew->cf=value;
    ptrNew->next=nullptr;
    if(ptrIns != nullptr){
        for(;;)
        {   if(ptrIns->next == nullptr){
            ptrIns->next = ptrNew;
            break;
        }
        ptrIns = ptrIns->next;
        }
    }else
        return ptrNew;
}

void funcFordelete(Sofconfunc *ptrDel)
{
    Sofconfunc *deletion;
    cout<<"Delete: ";
    while(ptrDel != nullptr)
    {
        deletion = ptrDel;
        ptrDel = ptrDel->next;
        cout<<deletion->cf<<ends;
        delete deletion;
}
}

double funcForcalc(Sofconfunc *ptrCalc)
{   //using recursive function
    if(ptrCalc->next != nullptr)
    {
        return (ptrCalc->cf+(1/funcForcalc(ptrCalc->next))); //recursive case
    }else{
        return ptrCalc->cf; //base case
    }
}

Sofconfunc* funcForimplement(void)
{
    Sofconfunc *ptrImpl = new Sofconfunc;
    int FValue,FValue1, counts = 1;

    cout<<"\nContinued fraction, enter first value f_0: ";
    cin>>FValue;

    ptrImpl->cf = FValue;
    ptrImpl->next = nullptr;

    do{
        cout<<"Enter next part denominator f_"<<counts<<" (<=0 for end): ";
        cin>>FValue1;

        if(FValue1==0)
        break;
        else{
        funcForinsert(ptrImpl, FValue1);
        counts++;
        }

    }while(FValue1 != 0);
    return ptrImpl;
}
