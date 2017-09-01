#include<iostream>
#include<map>
#include<string>
#include<iomanip>
#include<sstream>
#include<set>
#include<exception>

using namespace std;

class Date {
public:
	int GetYear() const {
		return y;
	}

	int GetMonth() const {
		return m;
	}

	int GetDay() const {
		return d;
	}

	Date(int a = 0, int b = 1, int c = 1) {
		y = a;
		m = b;
		d = c;
	}

	Date parseDate(string& input_string) {
		string error_msg = "Wrong date format: ";
		if (input_string.empty())
			throw invalid_argument(error_msg);
		stringstream isstream(input_string);
		int year = 0, month = 0, day = 0;
		char s, s1 = 0, s2 = 0;
		if (!isdigit(isstream.peek()) && isstream.peek() != ' ') {
			throw invalid_argument(error_msg + input_string);

		} else {
			while (isdigit(isstream.peek())) {
				s = isstream.peek();
				year = year * 10 + (s - 48);
				isstream.ignore(1);
			}

			if (isstream.peek() != '-') {
				//cout << isstream.peek();
				throw invalid_argument(error_msg + input_string);

			}

			isstream >> s1;
			if (!isdigit(isstream.peek()) && isstream.peek() != '-') {
				throw invalid_argument(error_msg + input_string);
			}

			char z = isstream.peek();
			if (z == '-')
				isstream.ignore(1);
			while (isdigit(isstream.peek())) {
				s = isstream.peek();
				month = month * 10 + (s - 48);
				isstream.ignore(1);
			}
			if (z == '-')
				month *= -1;
			if (isstream.peek() != '-') {
				throw invalid_argument(error_msg + input_string);

			}
			isstream >> s2;
			if (!isdigit(isstream.peek()) && isstream.peek() != '-') {
				throw invalid_argument(error_msg + input_string);
			}
			char z1 = isstream.peek();
			if (z1 == '-')
				isstream.ignore(1);
			while (isdigit(isstream.peek())) {
				s = isstream.peek();
				day = day * 10 + (s - 48);
				isstream.ignore(1);
			}
			if (z1 == '-')
				day *= -1;

			if (isstream.peek() != ' ' && !isstream.eof()) {
				throw invalid_argument(error_msg + input_string);

			}
		}
		if (year > 9999 || year < 0 || month < 0 || day < 0)
			throw invalid_argument(
					error_msg + to_string(year) + "-" + to_string(month) + "-"
							+ to_string(day));
		if (month > 12 || month <= 0)
			throw invalid_argument("Month value is invalid: " + to_string(month));
		else if (day > 31 || day <= 0)
			throw invalid_argument("Day value is invalid: " + to_string(day));
		Date d(year, month, day);
		return d;
	}

private:
	int y;
	int m;
	int d;
};

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() < rhs.GetYear())
			return true;
		if (lhs.GetMonth() < rhs.GetMonth() &&
			lhs.GetYear() == rhs.GetYear())
			return true;
		if (lhs.GetDay() < rhs.GetDay() &&
			lhs.GetMonth() == rhs.GetMonth() &&
			lhs.GetYear() == rhs.GetYear())
			return true;
		return false;
}

bool operator>(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() > rhs.GetYear())
			return true;
		if (lhs.GetMonth() > rhs.GetMonth() &&
			lhs.GetYear() == rhs.GetYear())
			return true;
		if (lhs.GetDay() > rhs.GetDay() &&
			lhs.GetMonth() == rhs.GetMonth() &&
			lhs.GetYear() == rhs.GetYear())
			return true;
		return false;
}

bool operator==(const Date& lhs, const Date& rhs) {
	if (lhs.GetDay() == rhs.GetDay() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetYear() == rhs.GetYear())
				return true;
		return false;
}

class Database {
public:
	void AddEvent(const Date& date, const string& event) {
		if (event.empty())
			throw invalid_argument("Wrong date format: ");
		db[date].insert(event);
	}
	bool DeleteEvent(const Date& date, const string& event) {
		if (db.size() > 0 && db.count(date) > 0
				&& db.at(date).count(event) > 0) {
			db[date].erase(event);
			return true;
		} else {
			return false;
		}
	}
	int DeleteDate(const Date& date) {
		if (db.size() == 0 || db.count(date) == 0)
			return 0;
		int q = db.at(date).size();
		db.erase(date);
		return q;
	}

	void Find(const Date& date) const {
		if (db.count(date) == 0)
			return;
		for (const auto& i : db.at(date)) {
			cout << i << endl;
		}
	}

	void Print() const {
		//if (db.size() == 0)
		//	throw invalid_argument("Wrong date format: ");
		cout.fill('0');
		for (const auto& i : db) {
			for (const auto& j : i.second) {
				cout << setw(4) << i.first.GetYear() << '-' << setw(2)
						<< i.first.GetMonth() << '-' << setw(2)
						<< i.first.GetDay() << " " << j << endl;
			}
		}
	}
private:
	map<Date, set<string> > db;
};

int main() {
	Date a(1,1,1);
	Date b(1,1,1);
	Date c(1,2,1);

	Database db;
	string command;
	while (getline(cin, command)) {
		try {
			string com, name, date;
			stringstream in(command);
			Date d;
			in >> com;

			if (com == "Add") {
				try {
					try {
						in >> date >> name;
						d = d.parseDate(date);
						db.AddEvent(d, name);
					} catch (exception &e) {
						cout << e.what() << endl;
						break;
					}

				} catch (exception& e) {
					break;
				}
			}

			else if (com == "Del") {
				try {
					in >> date;
					d = d.parseDate(date);
				} catch (exception &e) {
					cout << e.what() << endl;
					break;
				}

				if (!in.eof()) {
					try {
						in >> name;
						if(name.empty()){
							cout << "Deleted 0 events" << endl;
						}else{
							if (db.DeleteEvent(d, name) == true) {
								cout << "Deleted successfully" << endl;
							} else
								cout << "Event not found" << endl;
						}
					} catch (exception& e) {
						cout << "Event not found" << endl;
						break;
					}
				} else {

					try {
						cout << "Deleted " << db.DeleteDate(d) << " events"
								<< endl;
					} catch (exception& e) {
						cout << "Deleted 0 events" << endl;
						break;
					}
				}
			} else if (com == "Find") {
				try {
					try {
						in >> date;
						d = d.parseDate(date);
						db.Find(d);
					} catch (exception &e) {
						cout << e.what() << endl;
						break;
					}

				} catch (exception& e) {
					break;
				}

			} else if (com == "Print") {
				try {
					db.Print();
				} catch (exception& e) {
					cout << e.what() << endl;
					break;
				}
			} else if (command != "") {
				try {
					throw invalid_argument("Unknown command: " + com);
				} catch (exception &e) {
					cout << e.what() << endl;
					break;
				}

			}
		} catch (exception& e) {
			break;
		}

	}

	return 0;
}
