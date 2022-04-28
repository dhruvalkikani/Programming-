#include <iostream>
#include <string>
#include "Time.h"
#define width 20
using namespace std;
class Trip {
	friend ostream& operator<<(ostream& out, const Trip& t);		//for displaying trip 
public:
	Trip();
	~Trip();
	//gets info from users and validates it
	void startlocation();
	void endlocation();
	void starttime();
	void endtime();
	void startodometer();
	void endodometer();
	void amountoffuel();
	//sets info (used for reading) 
	void setStartLocation(string location);
	void setEndLocation(string location);
	void setStartTime(Time t);
	void setEndTime(Time t);
	void setStartOdometer(int odometer);
	void setEndOdometer(int odometer);
	void setAmountOfFuel(double amount);
	//returns set values
	string getslocation();
	string getelocation();
	Time getStartTime();
	Time getEndTime();
	int getStartOdometer();
	int getEndOdometer();
	double getAmountOfFuel();
	int getDistance();			//returns distance used for average fuel consumption
	void display();				//display last enterned trip with trip number

private:
	string start_location;
	string end_location;
	Time  start_time;
	Time  end_time;
	int start_odometer;
	int end_odometer;
	double amount_of_fuel;

};
Trip::Trip() {
	start_location = "SOMEWHERE";
	end_location = "SOMEWHERE";
	amount_of_fuel = 0;
	start_odometer = 0;
	end_odometer = 0;
}
Trip::~Trip() {
}

void Trip::startlocation()
{
	string location;
	cout << "\n";
	cout << "ENTER START LOCATION :";
	cin >> location;
	start_location = location;

}
void Trip::endlocation()
{
	string location;
	cout << "ENTER END LOCATION :";
	cin >> location;
	end_location = location;

}
void Trip::starttime()
{
	Time val;
	cout << "ENTER START TIME[HH:MM] :";
	while (!(cin >> val)) {
		cin.clear();
		cin.ignore();
		cout << "ERROR :ENTER VALID DATATYPE" << endl;
		cout << "ENTER START TIME[HH:MM] :";
	}
	start_time = val;
}
void Trip::endtime()
{
	Time val;
	cout << "ENTER END TIME[HH:MM] :";
	while (!(cin >> val)) {
		cin.clear();
		cin.ignore();
		cout << "ERROR :ENTER VALID DATATYPE" << endl;
		cout << "ENTER END TIME[HH:MM] :";
	}
	end_time = val;
}

void Trip::startodometer()
{
	int odometer = 0;
	cout << "ENTER START OF ODOMETER :";
	while (!(cin >> odometer) || odometer < 0) {
		cin.clear();
		cin.ignore();
		cout << "ERROR :ENTER VALID DATATYPE OR VALID ODOMETER VALUE" << endl;
		cout << "ENTER START OF ODOMETER (INT) :";
	}
	start_odometer = odometer;
}
void Trip::endodometer()
{
	int odometer = 0;
	cout << "ENTER END OF ODOMETER :";
	while (!(cin >> odometer) || odometer < 0 || odometer < getStartOdometer()) {
		cin.clear();
		cin.ignore();
		cout << "ERROR :ENTER VALID DATATYPE OR VALID ODOMETER VALUE" << endl;
		cout << "ENTER END OF ODOMETER (INT) :";
	}
	end_odometer = odometer;
}

void Trip::amountoffuel()

{
	double amount;
	cout << "ENTER AMOUNT OF FUEL :";
	while (!(cin >> amount) || amount < 0) {
		cout << "ERROR :ENTER VALID DATATYPE" << endl;
		cout << "ENTER AMOUNT OF FUEL :";
	}

	amount_of_fuel = amount;


}
void Trip::setStartLocation(string location) {
	start_location = location;
}
void Trip::setEndLocation(string location) {
	end_location = location;
}

void Trip::setStartTime(Time t) {
	start_time = t;
	//start_time.read("Start Time");
}

void Trip::setEndTime(Time t) {
	end_time = t;
	//end_time.read("End Time");
}

void Trip::setStartOdometer(int odometer) {
	start_odometer = odometer;
}

void Trip::setEndOdometer(int odometer) {
	end_odometer = odometer;
}

void Trip::setAmountOfFuel(double fuel) {
	amount_of_fuel = fuel;
}
string Trip::getslocation()
{
	return start_location;
}

string Trip::getelocation()
{
	return end_location;
}

Time Trip::getStartTime()
{
	return start_time;
}

Time Trip::getEndTime()
{
	return end_time;
}

int Trip::getStartOdometer()
{
	return start_odometer;
}

int Trip::getEndOdometer()
{
	return end_odometer;
}

double Trip::getAmountOfFuel()
{
	return amount_of_fuel;
}


int Trip::getDistance()
{

	return end_odometer - start_odometer;
}

void Trip::display()
{
	cout << "\n";
	static int counter = 0;
	cout << "TRIP :" << counter + 1 << endl;
	cout << "START LOCATION :" << getslocation() << endl;
	cout << "END LOCATION :" << getelocation() << endl;
	cout << "START TIME :" << getStartTime() << endl;
	cout << "END TIME :" << getEndTime() << endl;
	cout << "START ODOMETER :" << getStartOdometer() << endl;
	cout << "END ODOMETER :" << getEndOdometer() << endl;
	cout << "AMOUNT OF FUEL :" << getAmountOfFuel() << endl;
	counter++;

}

ostream& operator<<(ostream& out, const Trip& t) {

	out << t.start_location << setw(width) << " | " << t.end_location << setw(width) << " | " << t.start_time << setw(width) << setfill(' ') << " | " << t.end_time << setw(width) << setfill(' ') << " | " << t.start_odometer << setw(width) << setfill(' ') << " | " << t.end_odometer << setw(width) << setfill(' ') << " | " << t.amount_of_fuel << endl;
	return out;
}
