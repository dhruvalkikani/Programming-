// Finalprojectc++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <sstream>      // std::istringstream
#include <cstdlib>
#include <string>
#include <iomanip>  // std::setiosflags
#include <algorithm>
#include <vector>
#include "Trip.h"
#include <Time.h>
#include<cstdio> 
#define width 20
#define FILE_NAME "test.txt"
using namespace std;
void mainpage();		//Displays main page of the program
int saveDataIntoFile(vector<Trip> fileStore, string file_name);// saves data into file
void addtripinfo(vector<Trip>& t1, Trip& temp);// adds trip info in file
void print(vector<Trip>& t1);//prints all trip
int readdata(vector<Trip>& t1, string file_name, Trip& temp);// reads data from file
int deletefile(string file_name); //delete the trip file
double avarage_fuel_comsuption(Trip& temp); // calculates average fuel consumption
void removetrip(vector<Trip>& t1);//removes user selected trip 
int main()
{
	vector<Trip> t1;		// stores all trip
	Trip temp;
	double fuel = 0;
	int expression = 0;
	int returnv, returnv1;

	do {
		mainpage();
		cin >> expression;
		switch (expression) {
		case 0:
			cout << "THE PROGRAM HAS ENDED" << endl;				// ends the program
		case 1:
			t1.clear();											//clears the vector

			break;
		case 2:
			returnv = saveDataIntoFile(t1, FILE_NAME);
			if (returnv == 0) {
				cout << "FILE SAVED SUCCESFULLY" << endl;
			}
			else
			{
				cout << "ERROR" << endl;
			}

			break;
		case 3:
			returnv1 = readdata(t1, FILE_NAME, temp);
			if (returnv1 == 0) {
				cout << "READING FROM FILE WAS SUCCESSFULL" << endl;
			}
			else
			{
				cout << "THE FILE IS EMPTY" << endl;
			}

			break;
		case 4:
			addtripinfo(t1, temp);
			fuel = fuel + avarage_fuel_comsuption(temp);			//adds fuel consumption everytime (used for getting average )  
			temp.display();
			break;
		case 5:
			removetrip(t1);
			break;
		case 6:
			deletefile(FILE_NAME);
			break;
		case 7:
			cout << "THE AVERAGE FUEL CONSUMPTION IS :" << fuel << endl;
			break;
		case  8:
			print(t1);
			break;
		default:
			cout << "ERROR,SELECT FROM OPTIONS ABOVE";
		}
		cout << "\n";
	} while (expression != 0);

}
void mainpage() {
	cout << "0. EXIT THE PROGRAM" << endl;
	cout << "1. INITIALLIZE (CLEAR ALL RECORD)" << endl;
	cout << "2. SAVE TRIP DATA TO FILE" << endl;
	cout << "3. READ TRIP DATA FROM FILE" << endl;
	cout << "4. ADD NEW TRIP" << endl;
	cout << "5. REMOVE TRIP" << endl;
	cout << "6. DELETE TRIP FILE" << endl;
	cout << "7. CALCULATE AVERAGE FUEL CONSUMPTION " << endl;
	cout << "8. PRINT ALL DATA" << endl;
	cout << "\n";
	cout << "KINDLY SELECT FROM OF OPTIONS ABOVE :";

}

void addtripinfo(vector<Trip>& t1, Trip& temp) {
	temp.startlocation();
	temp.endlocation();
	temp.starttime();
	temp.endtime();
	temp.startodometer();
	temp.endodometer();
	temp.amountoffuel();
	t1.push_back(temp);

}

void print(vector<Trip>& t1) {
	const int wid1 = 180;

	cout << setfill(' ') << "|START LOCATION" << setfill(' ');
	cout << setw(width) << "|END LOCATION" << setfill(' ');
	cout << setw(width) << "|START TIME" << setfill(' ');
	cout << setw(width) << "|END TIME" << setfill(' ');
	cout << setw(width) << "|START ODOMETER" << setfill(' ');
	cout << setw(width) << "|END ODOMETER" << setfill(' ');
	cout << setw(width) << "|AMOUNT OF FUEL" << "|" << setfill(' ') << endl;

	cout << "|" << setw(wid1) << setfill('-') << right << "|" << setfill(' ') << endl;
	for (auto i = t1.begin(); i != t1.end(); i++) {
		cout << "|" << setfill(' ') << *i;

	}


}



int saveDataIntoFile(vector<Trip> fileStore, string file_name) { // insert  data into File

	ofstream outfile(file_name.c_str());
	string seprator = "  ";
	if (!outfile) {
		cout << "Error" << endl;
		return -1;
	}
	else {
		for (auto ob : fileStore) {
			outfile << ob.getslocation();
			outfile << seprator + ";" + seprator;
			outfile << ob.getelocation();
			outfile << seprator + ";" + seprator;
			outfile << ob.getStartTime();
			outfile << seprator;
			outfile << ob.getEndTime();
			outfile << seprator;
			outfile << ob.getStartOdometer();
			outfile << seprator;
			outfile << ob.getEndOdometer();
			outfile << seprator;
			outfile << ob.getAmountOfFuel() << endl;
		}
	}

	outfile.close();
	return 0;

}
int readdata(vector<Trip>& t1, string file_name, Trip& temp) {
	ifstream infile;
	infile.open(file_name);
	string line;
	string check;
	string s_location, e_location;
	Time start_time, end_time;
	int start_od, end_od;
	double fuel;
	int count = 0;
	istringstream sin(line);
	vector<Trip> fileStore;
	if (infile.peek() == std::ifstream::traits_type::eof())
	{

		return 1;				// Empty File

	}
	else
	{
		if (!infile) {
			cout << "Error" << endl;
			return -1;
		}
		else {
			while (getline(infile, line)) {
				while (sin >> check && check != ";") {
					s_location.append(check + " ");
					temp.setStartLocation(s_location);
				}
				while (sin >> check && check != ";") {
					e_location.append(check + " ");
					temp.setEndLocation(e_location);
				}
				if (sin >> start_time) {
					temp.setStartTime(start_time);

				}
				if (sin >> end_time) {
					temp.setEndTime(end_time);

				}
				if (sin >> start_od) {
					temp.setStartOdometer(start_od);
				}
				if (sin >> end_od) {
					temp.setEndOdometer(end_od);
				}

				if (sin >> fuel) {
					temp.setAmountOfFuel(fuel);
				}

				fileStore.push_back(temp);
				line.erase();
				count++;
				cout << "TRIP :" << count << endl;


			}

		}
		fileStore = t1;
		print(t1);
		return 0;
	}

}


int deletefile(string file_name) {
	if (remove(file_name.c_str()) != 0)
		perror("FILE DELETION FAILED");
	else
		cout << "FILE DELETED SUCCESSFULLY";

	return 0;
}
double avarage_fuel_comsuption(Trip& temp) {

	double average_fuel = 0;
	int d = temp.getDistance();
	double fuel = temp.getAmountOfFuel();
	average_fuel = (d / fuel) + average_fuel;
	return average_fuel;
}

void removetrip(vector<Trip>& t1) {
	int element;
	if (t1.empty()) {
		cout << "THERE ARE NO TRIPS ADDED,KINDLY ADD NEW TRIPS " << endl;
	}
	else
	{
		cout << "ENTER THE TRIP NUMBER YOU WANT TO REMOVE :";
		cin >> element;
		t1.erase(t1.begin() + element - 1);//removes the mentioned trip 
		saveDataIntoFile(t1, FILE_NAME);// writes in the file again
	}

}

