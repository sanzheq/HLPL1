#include "std_lib_facilities.h"

// Question 4
void print_array10(ostream& os, int* a)
{
	for(int i=0; i<10; i++)
		os << a[i] << endl;
delete[] a;  // Question 9
	
}
// Question 6
void print_array11(ostream& os, int* a)
{
	for(int i=0; i<11; i++)
		os << a[i] << endl;

delete[] a; // Question 9
}

// Question 7
void print_array(ostream& os, int* a, int n)
{
	for(int i=0; i<n; i++)
		os << a[i] << endl;
delete[] a;  // Question 9
}


void printVector(vector<int*> v)
{

for (int i = 0; i < v.size(); ++i)
		cout << *v[i] << endl;
//delete v[i];


}

vector<int*> allocateVector(int n)
{
	vector<int*> temp;
	int counter = 100;
	for (int i = 0; i < n; ++i)
		temp.push_back(new int{counter++});
	
	return temp;
}


int main()
{
// Question 1
int* ten_i = new int[10];

        // Question 2
	for(int i=0; i<10; i++)
	cout << ten_i[i] << endl;
	
	// Question 3
	delete[] ten_i;
	
	// Question 4
	//print_array10(cout, ten_i);
	
	
	// Question 5
	int* ten_i2 = new int[10] {100, 101, 102, 103, 104, 105, 106, 107, 108, 109};
	print_array10(cout, ten_i2);
	//delete[] ten_i2
	
	
	// Question 6
	int* eleven_i = new int[11] {100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110};
	print_array11(cout, eleven_i);
	//delete[] eleven_i;
	
	// Question 8
	int* twenty_i = new int[20] {100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119};
	print_array(cout, twenty_i, 20);
	//delete[] twenty_i ;
	
	// Question 10
	cout << "with Vector 10" << endl;
	vector<int*> v_ten_i = allocateVector(10);
	printVector(v_ten_i);
	
	cout << "with Vector 11" << endl;
	vector<int*> v_eleven_i = allocateVector(11);
	printVector(v_eleven_i);
	
	cout << "with Vector 20" << endl;
	vector<int*> v_twenty_i = allocateVector(20);
	printVector(v_twenty_i);
	
	

return 0;
}