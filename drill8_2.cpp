#include "std_lib_facilities.h"
void swap_v(int a ,int b){
int temp;
temp = a;
a = b;
b = temp;
}

void swap_cr(const int& a, const int& b){
int temp;
temp = a;
a = b;
b = temp;

}

void swap_r(int &a, int &b){
int temp;
temp = a;
a = b;
b = temp;
}
int main(){

int x = 7;

int y = 9;

swap_r(x,y);

swap_v(x,y);

int cx = 7;

int cy = 9;

swap_v(cx,cy);

swap_cr(cx,cy);

double dx = 7.7;

double dy = 9.9;

swap_v(dx,dy);

swap_cr(dx,dy);

return 0;
}

//ANSWER: THe ones that are not compiled are the ones that have const reference to the number. SInce they are constant they cannot change the value of the referenced number. They would create error at compie time. Others will compile but the one with int a,int b arguments will not swap values because it works with the copies of the original values and not original values. swap_r will swap the values and compile successfully.
