#include "std_lib_facilities.h"

template <typename T>//chapter 19, drill 1
struct S
{
private://chapter 19, drill 17
	T val;
public :
	
	S()//chapter 19, drill 2
	{
		val = 0;
	}
	S(T vv)
	{
		val=vv;
	}
	
	T get();//chapter 19, drill 5
	/*{
	return val;
	}
	*/ 
	const T get() const;
	void operator=(const T&);
	/*
	void set(T vvv) // chapter 19, drill 9
	{
		val = vvv;
	}
	*/

};

template<typename T>
T S<T>::get()//chapter 19, drill 6
	{
		return val;
	}

template<typename T>
const T S<T>::get() const // chapter 19, drill 11
{
	return val;
}

template <typename T> // chapter 19, drill 10
void S<T>:: operator=(const T& vvv)
{
	val = vvv;
}

template<typename T> 
void read_val(T& v) // chapter 19, drill 12
 {
	cin >> v;
}
int main()
{
	S<int> intS(11);
	S<char> charS('K');
	S<double> dblS(11.23);
	S<string> strS("Helloooooo");
	S<vector<int>> vecS ({ 1,2,3,4,5 });//chapter 19, drill 3
	/*
	 
	cout << intS.val<<endl;
	cout << charS.val << endl;
	cout << dblS.val << endl;
	cout << strS.val << endl;
	for(int i : vecS.val)
	cout << i <<" ";// chapter 19, drill 4
	*/ 
	
	cout << intS.get()<<endl;//chapter 19, drill 8
	cout << charS.get() << endl;
	cout << dblS.get() << endl;
	cout << strS.get() << endl;
	for(int i : vecS.get())
	cout << i <<" ";
	cout << endl;
	 
	int int1; //chapter 19, drill 13
	read_val(int1);
	S<int> int1S(int1);
	
	double dbl1; 
	read_val(dbl1); 
	S<double> dbl1S(dbl1);
	
	char char1; 
	read_val(char1); 
	S<char> char1S(char1);
	
	string stringg;
	read_val(stringg);
	S<string> string1S(stringg);
	
	cout << int1S.get() << endl;
	cout << dbl1S.get() << endl;
	cout << char1S.get() << endl;
	cout << strS.get() << endl;
	 
	return 0;
}
