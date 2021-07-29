#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>
#include "blood.h"
#include "Donor.h"
#include "Recipient.h"
#include "Request.h"

using namespace std;


vector<Donor> donors;
vector<Blood>donations;
vector<Request> requests;
vector<Blood>searchDonations;
vector<Recipient> recipients;


time_t now = time(0);
tm* ltm = localtime(&now);


void loadDonors() {

	ifstream file("donorsData.txt");

	Donor d;

	while (file.peek() != EOF) {

		file >> d.id >> d.name >> d.age >> d.isChronicDisease >> d.latestDonationDate >> d.disease >> d.bloodType
            >> d.email >> d.password >> d.gender;

		donors.push_back(d);
	}

	file.close();
}

void writeDonorData() {

	ofstream file("donorsData.txt", ios::out);

	int flag = 0;

	for (int i = 0; i < donors.size(); i++) {

		Donor d = donors.at(i);

		file << d.id << endl << d.name << endl << d.age << endl << d.isChronicDisease << endl << d.latestDonationDate << endl
			<< d.disease << endl << d.bloodType << endl << d.email << endl << d.password << endl << d.gender;

		if (flag < donors.size() - 1) {

			file << endl;
		}

		flag++;
	}

	file.close();
}

void loadRecipients() {

	ifstream file("recipientsData.txt");

	Recipient r;

	while (file.peek() != EOF) {

		file >> r.id >> r.name >> r.age >> r.bloodType >> r.email >> r.password
			>> r.HospitalName >> r.DoctorOfCase >> r.gender;

		recipients.push_back(r);
	}

	file.close();
}


void writeRecipientData() {

	ofstream file("recipientsData.txt", ios::out);

	int flag = 0;

	for (int i = 0; i < recipients.size(); i++) {

		Recipient r = recipients.at(i);

		file << r.id << endl << r.name << endl << r.age << endl << r.bloodType << endl << r.email << endl << r.password << endl
			<< r.HospitalName << endl << r.DoctorOfCase << endl << r.gender;

		if (flag < recipients.size() - 1) {

			file << endl;
		}

		flag++;
	}

	file.close();
}

void loadDonations() {

	ifstream file("donationsData.txt");

	Blood b;

	while (file.peek() != EOF) {

		file >> b.donorName >> b.bloodType >> b.quantity >> b.recievedMonth >> b.expiryMonth;

		donations.push_back(b);
	}

	file.close();
}

void loadSearchDonations() {

	ifstream file("searchDonation.txt");

	Blood b;

	while (file.peek() != EOF) {

		file >> b.donorName >> b.bloodType >> b.quantity >> b.recievedMonth >> b.expiryMonth;

		searchDonations.push_back(b);
	}

	file.close();
}

void writeSearchDonationsData() {

	ofstream file("searchDonation.txt", ios::out);

	int flag = 0;

	for (int i = 0; i < searchDonations.size(); i++) {

		Blood b = searchDonations.at(i);

		file << b.donorName << endl << b.bloodType << endl << b.quantity << endl << b.recievedMonth << endl << b.expiryMonth;

		if (flag < searchDonations.size() - 1) {

			file << endl;
		}

		flag++;
	}

	file.close();
}

void writeDonationsData() {

	ofstream file("donationsData.txt", ios::out);

	int flag = 0;

	for (int i = 0; i < donations.size(); i++) {

		Blood b = donations.at(i);

		file << b.donorName << endl << b.bloodType << endl << b.quantity << endl << b.recievedMonth << endl << b.expiryMonth;

		if (flag < donations.size() - 1) {

			file << endl;
		}

		flag++;
	}

	file.close();
}

void loadRequests() {

	ifstream file("requestsData.txt");

	Request r;

	while (file.peek() != EOF) {

		file >> r.recipientName >> r.requestType >> r.requestQuantity >> r.recipientHospitalName >> r.recipientemail;

		requests.push_back(r);
	}

	file.close();
}

void writeRequestsData() {

	ofstream file("requestsData.txt", ios::out);

	int flag = 0;

	for (int i = 0; i < requests.size(); i++) {

		Request r = requests.at(i);

		file << r.recipientName << endl << r.requestType << endl << r.requestQuantity << endl << r.recipientHospitalName << endl << r.recipientemail;

		if (flag < requests.size() - 1) {

			file << endl;
		}

		flag++;
	}

	file.close();
}

int getChoice() {

	int choice = -1;

	cin >> choice;

	while (!cin.good()) {

		//Report a Problem
		cout << "Enter a Valid main Choice from the Above" << endl;

		//Clear Stream
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		//Get Input again
		cin >> choice;
	}

	return choice;
}

void initializeMap(map<string, int>& req) {

	req.insert(pair<string, int>("A+", 0));					
	req.insert(pair<string, int>("A-", 0));				    
	req.insert(pair<string, int>("B+", 0));
	req.insert(pair<string, int>("B-", 0));
	req.insert(pair<string, int>("O+", 0));
	req.insert(pair<string, int>("O-", 0));
	req.insert(pair<string, int>("AB+", 0));
	req.insert(pair<string, int>("AB-", 0));
}

int main() {

	map <string, int> req;
	initializeMap(req);

	loadDonors();
	loadRequests();
	loadDonations();
	loadRecipients();
	loadSearchDonations();

	Donor d;
	Recipient r;

	map<string, int> ::iterator it;

	for (int i = 0; i < searchDonations.size(); i++) {

		for (it = req.begin(); it != req.end(); it++) {

			if (it->first == searchDonations.at(i).bloodType) {

				req[it->first]++;
				break;
			}
		}
	}

	int currentMonth = 1 + ltm->tm_mon;

	int userType;

	while (true) {

		cout << "\n------------------ " << "Welcome To Blood Bank System" << " ------------------" << endl;
		cout << "\n1. Donor\n2. Recipient\n Press 0 to Exit" << endl;

		userType = getChoice();

		if (userType == 1) {

			int choice;

			while (true) {

				cout << "\n1. Sign Up\n2. Already Have an Account\n	Press 0 To Back" << endl;

				choice = getChoice();

				if (choice == 1) {

					d.registeration(donors, currentMonth);

					if (d.email != "") {

						if (donors.empty()) {

							d.id = 1;
						}
						else {

							d.id = donors.at(donors.size() - 1).id + 1;
						}

						cout << endl<< "Your Id is: " << d.id << endl;

						donors.push_back(d);

						d.displayOptions(donors, req, donations, currentMonth, searchDonations);
					}
				}

				else if (choice == 2) {

					d = d.logIn(donors);

					if (d.email != "") {

						d.displayOptions(donors, req, donations, currentMonth, searchDonations);
					}
				}

				else if (choice == 0) {
					break;
				}
				else
					cout << "\nInvalid Option, Please Enter One Of the Choices:" << endl;
			}
		}

		else if (userType == 2) {

			int choice;

			while (true) {

				cout << "\n1. Sign Up\n2. Already Have an Account\n	Press 0 To Back" << endl;

				choice = getChoice();

				if (choice == 1) {

					r.Register(recipients);

					if (r.email != "") {

						if (recipients.empty()) {

							r.id = 1;
						}
						else {

							r.id = recipients.at(recipients.size() - 1).id + 1;
						}

						cout << endl << "Your Id is: " << r.id << endl;

						recipients.push_back(r);

						r.DisplayFunctionalities(recipients, donors, req, requests, donations, currentMonth, searchDonations);
					}
				}

				else if (choice == 2) {

					r = r.Login(recipients, donors);

					if (r.email != "") {

						r.DisplayFunctionalities(recipients, donors, req, requests, donations, currentMonth, searchDonations);
					}
				}

				else if (choice == 0) {

					break;
				}
				else
					cout << "\nInvalid Option, Please Enter One Of the Choices:" << endl;
			}
		}
		else if (userType == 0) {

			break;
		}
		else
			cout << "\nInvalid Option, Please Enter One Of the Choices:\n";

	}

	writeDonorData();
	writeRequestsData();
	writeRecipientData();
	writeDonationsData();
	writeSearchDonationsData();

	return 0;
}