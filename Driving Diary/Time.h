#include <iostream>
#include <string>
#include <iomanip>  
using namespace std;
class Time
{
	friend ostream& operator<<(ostream& out, const Time& time);
	friend istream& operator>>(istream& in, Time& inputtime);
public:
	Time(int H = 0, int M = 0);// initialising
	void read(string str); // read values 
	bool operator<(const Time& t2) const;// returns true if t2 > t1 
	Time operator-(const Time& t2) const; // subtracts time
	Time operator+(const Time& t2) const;// adds time 
	Time& operator++(); // pre-increment
	Time operator++(int); // post-increment 

private:
	int hours;
	int mins;
};
Time::Time(int H, int M) {
	hours = H;
	mins = M;
}
ostream& operator<<(ostream& out, const Time& time) {
	out << setiosflags(ios::right) << time.hours << ":" << setfill('0') << setw(2) << time.mins;
	return out;
}
istream& operator>>(istream& in, Time& inputtime)
{
	in >> inputtime.hours;

	if (in.peek() == ':') {
		in.ignore(1, ':');
		in >> inputtime.mins;
	}

	else {
		in.setstate(ios_base::failbit);
	}

	if (inputtime.hours > 23 || inputtime.mins > 59 || inputtime.hours < 0 || inputtime.mins < 0) {
		in.setstate(ios_base::failbit);
	}

	return in;
}
void Time::read(string s1) {
	int check;
	do
	{
		cout << s1;
		cin >> hours >> mins;
		if (hours < 24 && hours >= 0 && mins < 60 && mins >= 0) {
			check = 0;
		}
		else
		{
			cout << "Error;Invalid entry,Enter correct values" << endl;
			check = 1;
		}
	} while (check != 0);
}
bool Time:: operator<(const Time& t2) const {
	int totalt1, totalt2;
	totalt1 = hours * 60 + mins;
	totalt2 = t2.hours * 60 + t2.mins;
	if (totalt2 > totalt1) {
		return true;

	}
	else {
		return false;

	}

}

Time Time::operator-(const Time& t2) const {
	int totalt1, totalt2, diff;
	Time sub;

	totalt1 = hours * 60 + mins;
	totalt2 = t2.hours * 60 + t2.mins;
	if (totalt1 > totalt2) {
		diff = totalt1 - totalt2;
	}
	else
	{
		diff = totalt2 - totalt1;

	}
	sub.hours = diff / 60;
	sub.mins = diff % 60;

	return sub;
}

Time Time::operator+(const Time& t2) const {
	Time ftime;
	int time1, time2, ttime;
	time1 = hours * 60 + mins;
	time2 = t2.hours * 60 + t2.mins;
	ttime = time1 + time2;
	ftime.hours = ttime / 60;
	ftime.mins = ttime % 60;
	if (ftime.hours >= 24) {

		if (ftime.hours == 24) {
			ftime.hours = 0;
		}

		else
		{
			ftime.hours = ftime.hours - 24;


		}



	}

	if (ftime.mins >= 60) {
		ftime.hours = ftime.hours + 1;
		if (ftime.mins == 60) {
			ftime.mins = 00;

		}
		else

			ftime.mins = ftime.mins - 60;

		if (ftime.hours >= 24 || ftime.mins >= 60)
		{
			ftime.hours = ftime.hours - 24;


		}

	}


	return ftime;
}
Time& Time::operator++() {
	mins++;
	return *this;
}

Time Time::operator++(int) {
	Time old = *this;
	mins++;
	return old;
}