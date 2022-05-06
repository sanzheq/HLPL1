#include "std_lib_facilities.h"

constexpr char number = '8';
constexpr char quit = 'q'; 
constexpr char print = ';';
constexpr char name = 'a';
constexpr char let = '#';
const string square = "sqrt"; //chapter 7 drill 7
const string power = "pow"; //chapter 7 drill 9
const string declkey = "#"; //chaoter 7 drill 10
const string quitkey = "quit"; //chapter 7 drill 11

double expression();

class Variable {
public:
	string name;
	double value;
};

vector<Variable> var_table;

bool is_declared(string var){
	for (const auto& v : var_table)
		if (v.name == var) return true;
	return false;
}

double define_name (string var, double val){
	if (is_declared(var)) error(var, " declared twice");
	var_table.push_back(Variable{var,val});
	return val;
}

double get_value(string s){
	for(const auto& v : var_table)
		if (v.name == s) return v.value;
	error("get: undefined variable", s);
}

void set_value(string s, double d){
	for (auto& v : var_table)
		if(v.name == s){
			v.value = d;
			return;
		}
		error("set: undefined variable", s);
}

class Token{
public:
	char kind;
	double value;
	string name;
	Token(): kind(0) {}
	Token(char ch): kind(ch), value(0) {}
	Token(char ch, double val): kind(ch), value(val) {}
	Token(char ch, string n): kind(ch), name(n) {}
};

class Token_stream {
public:
	Token_stream();
	Token get();
	void putback(Token t);
	void ignore(char c);
private:
	bool full;
	Token buffer;
};

Token_stream::Token_stream() :full(false), buffer(0) {}

void Token_stream::putback(Token t){
	if (full) error("putback() into full buffer");
	buffer = t;
	full = true;
}

Token Token_stream::get(){

	if (full){
		full = false;
		return buffer;
	}

	char ch;
	cin >> ch;

	switch (ch){
		case print:
		case '(':
		case ')':
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		case '=':
			return Token(ch);
		case '.':
		case '0': case '1': case '2': case '3': case '4':
    	case '5': case '6': case '7': case '8': case '9':
    	{
    		cin.putback (ch);
    		double val;
    		cin >> val;
    		return Token(number, val);
    	}
    	default: 
    	{
    		if (isalpha(ch)){
    			string s;
    			s += ch;
    			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s+=ch;
    			cin.putback(ch);
    			if (s == declkey) return Token{let};
    			else if(s == quitkey) return Token(quit); //using same technique as with let to make string possible.
    			else if(s == square) return Token('s'); //reading square returns token s that will be used for defining square method
    			else if(s == power) return Token ('p'); //power for power function.
    			else if (is_declared(s))
    				return Token(number, get_value(s));
    			return Token{name,s};
    		}
    		error("Bad token");
    	}
	}
}

void Token_stream::ignore(char c){

	if (full && c == buffer.kind){
		full = false;
		return;
	}
	full = false;

	char ch = 0;
	while (cin>>ch)
		if (ch==c) return;
}

Token_stream ts;

double primary(){

	Token t = ts.get();
	switch (t.kind){
		case '(':
		{
			double d = expression();
			t = ts.get();
			if (t.kind != ')') error ("')' expected");
			return d;
		}
		case number:
			return t.value;
		case '-':
			return - primary();
		case '+':
			return primary();
		case 's': //defining square function ALso chapter 7 drill 7
		{
			char ch1;
			double toBeSquared;
			if(cin>>ch1 && ch1 == '('){
				toBeSquared =expression();
			}
			else error("The function starts with (!"); //eror checking
			if(ts.get().kind == ')'){
			
				if(toBeSquared >=0)
					return sqrt(toBeSquared);
				else error(" argument cannot be smaller than 0!"); //error check if the value is negative since the square root cannot be found. Chapter 7 drill 8
				}
			else error(" ) is needed for the end of the function!"); //eror check
		}
		case 'p':
		{
			char ch1;
			double toBePowered;
			int power;
			if(cin>>ch1 && ch1 =='('){
			toBePowered = primary();
			if(cin>>ch1 && ch1 ==','){
			power = narrow_cast<int>(primary()); //using narrow cast to make sure that no info is lost/damaged seriously and making it integer since the task is to use integer for power funciton. Chapter 7 drill 9
			}
			else error(" , is needed between arguments"); //error checking
			}
			else error("Enter ( first"); //error checking
			if(cin>>ch1 && ch1 ==')'){
			return pow(toBePowered,power);
			}
			else error(") needed at the end of pow");//error checking
		}
		default:
			error("primary expected");
	}
}

double term(){

	double left = primary();
	Token t = ts.get();
	while(true){
		switch (t.kind){
			case '*':
				left *= primary();
				t = ts.get();
				break;
			case '/':
			{
				double d = primary();
				if (d == 0) error ("divide by zero");
				left /= d;
				t = ts.get();
				break;
			}
			case '%':
			{
				double d = primary();
				if (d == 0) error ("%: Zero oszto");
				left = fmod (left, d);
				t = ts.get();
				break;
				/*
				int i1 = narrow_cast<int>(left);
				int i2 = narrow_cast<int>(primary());
				if (i2 == 0) error ("%: Zero oszto");
				left = i1 % i2;
				t = ts.get();
				break;
				*/
			}
			default:
				ts.putback(t);
				return left;
		}
	}
}

double expression(){

	double left = term();
	Token t = ts.get();
	while (true){
		switch(t.kind){
			case '+':
				left += term();
				t = ts.get();
				break;
			case '-':
				left -= term();
				t = ts.get();
				break;
			default:
				ts.putback(t);
				return left;
		}
	}
}

void clean_up_mess(){
	ts.ignore(print);
}

double declaration(){
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", var_name);

	double d = expression();
	define_name(var_name, d);
	return d;
}

double statement(){
	Token t = ts.get();
	switch(t.kind){
		case let:
			return declaration();
		default:
			ts.putback(t);
			return expression();
	}
}

void calculate(){
	
/*	double val = 0;

	while (cin)
		try {

		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.putback(t);
		cout << "=" << statement() << endl;
		*/
	while (cin)
	try {
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.putback(t);
		cout << "=" << statement() << endl;
	}
	catch (exception& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main() 

try {
	cout<<"Welcome to our simple calculator. Please enter expressions using floating-point numbers."<<endl;
	cout<<"The operators available are: +,-,*,/,%,sqrt(argument),pow(argument)"<<endl;

	define_name("pi", 3.1415926535);
	define_name("e", 2.7182818284);
	define_name("k",1000); //chapter 7 ,drill 6
	calculate();

	return 0;
} catch (exception& e){
	cerr << e.what() << endl;
	return 1;
} catch (...) {
	cerr << "exception\n";
	return 2;
}

