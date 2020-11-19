#include <cmath>
#include <iostream>
using namespace std;
struct rectangle
{ double x1, y1, x2, y2; };
double area(rectangle &r)
{
    return fabs((r.x2-r.x1)*(r.y2-r.y1));
}
void print(rectangle &r)
{ cout << "upper left corner: ("<<r.x1<< ","<< r.y1<<")"<<endl;
cout << "lower right corner: ("<<r.x2<<","<<r.y2<<")"<<endl;
cout << "area rectangle: "<< area(r)<<endl;
}

void printCircumference(rectangle &r){
    double cir;
    cir = 2*(fabs(r.x2-r.x1)+fabs(r.y2-r.y1));
    cout<<"Circumference of the Rectangle is "<<cir<<endl;
}

void printDiagonalLength(rectangle &r){
    double dLen;
    double a, b;
    a = r.x2-r.x1;
    b = r.y2-r.y1;
    dLen = sqrt(pow(a,2)+pow(b,2));
    cout<<"diagonal length "<<dLen<<endl;
}

bool isSquare(rectangle &r){
    return fabs(r.x2-r.x1) == fabs(r.y2-r.y1);
}

bool isCorrect(rectangle &r){
    //return fabs(r.x2-r.x1) != fabs(r.y2-r.y1); //this is for check whether it is rectangle or not

    return (r.x1 < r.x2 && r.y1 > r.y2);
}

void makeBigSquare(rectangle &r){
    r.y2 -= (r.x2- (r.y1-r.y2));
}

void makeSmallSquare(rectangle &r){
    r.x2 = fabs(r.y1-r.y2);
}

int main(void)
{ rectangle z;
cout << "input upper left corner: ";
cin >> z.x1 >> z.y1 ;
cout << "input lower right corner: ";
cin >> z.x2 >> z.y2 ;

print(z);
printCircumference(z);
printDiagonalLength(z);

if (isCorrect(z) == true){
    cout<<"Rectangle is correctly stored"<<endl;
}

makeBigSquare(z);
print(z);

if (!isSquare(z)){
    makeSmallSquare(z);
    print(z);
}
return 0;
}
