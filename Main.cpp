#include "std_lib_facilities.h"
using namespace std;

struct Reading {
	int hour;
	double temperature;
};

//read integers from the ist into v until we reach eof or terminator
void fill_vector(istream& ist, vector<int>& v, char terminator)	
{
	for (int i; ist >> i;) v.push_back(i);
	if (ist.eof()) {
		return; //fine: we found the end of the file
	} 

	if (ist.bad()) error("ist is bad()"); //file corrupt 

	if (ist.fail()) { //clean up the mess and report the problem
			ist.clear(); //clear the stream state
							//so we can look for the terminator
			char c;
			ist >> c; //read the character hopefully the terminator

		if (c != terminator) { //unexpected character
			ist.unget();	//put the character back
			ist.clear(ios_base::failbit);	//set the state of fail()
		}
	}
}

int main()
{
	cout << "Please enter the input file name: ";
	string iname;
	cin >> iname;
	
	if (!cin) {
		if (cin.bad()) error("cin is bad() (Corrupted file)\n");
		if (cin.eof()) {
			//no more input 
			//this is often how we want a sequence of events to end
		}
		if (cin.fail()) { //stream encountered something unexpected
			cin.clear(); //make ready fo more input
			//somehow recover
		}
	}
	ifstream ist{iname};
	if (!ist) {
		error("\ncan't open input file", iname);
	}else
	{
		cout << "\nInput file " << iname << " opened.\n";
	}
	string oname;
	cout << "Please enter the output file name: "; //I can only at this stage assume this could be to an entirely diffferent file name
	cin >> oname;
	ofstream ost{ oname };
	if (!ost) error("cannot open the file for output", oname);

	vector<Reading> temps; //store the temperature readings here
	int hour;
	double temperature;
	while (ist >> hour >> temperature) {
		if (hour < 0 || 23 < hour) error("error hour is out of range", hour);
		temps.push_back(Reading{ hour, temperature });
	}

	for (int i = 0; i < temps.size(); ++i)
		ost << '(' << temps[i].hour << ','
		<< temps[i].temperature << ")\n";

	return 0;
}