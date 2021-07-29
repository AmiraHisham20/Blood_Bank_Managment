#include <map>
#include <iomanip>
#include <iostream>
#include "Donor.h"


Donor::Donor() {
	
	latestDonationDate = 0;
	disease = "";
}

bool Donor::Verification(int age, int donationDate, int currentMonth) {

	if (age < 17 || age > 60) {

		cout << "\nYour Donation Request Can Not Be Approved Due To Your Age." << endl;
		return false;
	}
	else if (abs(currentMonth - donationDate) <= 3) {

		cout << "\nYour Donation Request Can Not Be Approved Due To Your Last Donation Date." << endl;
		return false;
	}
	else {
		return true;
	}
}

void Donor::registeration(vector<Donor>& donors, int currentMonth) {

	char gen;
	int age = -1;

	cout << "Please Enter Your Personal Information" << endl;
	cout << "\nName: ";
	this->setName();

	cout << "\nAge: ";
	age = getChoices();
	this->setAge(age);

	while (true) {

		cout << "\nLast Donation Month: ";
		cin >> latestDonationDate;

		if (latestDonationDate < 1 || latestDonationDate > 12) {
			cout << "\nPlease Enter The Correct Month." << endl;
		}

		else {
			break;
		}
	}

	while (true) {

		cout << "\nDo You Have any Type Chronic Diseases:\n-Blood Pressure\n-Thyroid\n-Diabetes\n-Cancer\nEnter 1 if Exists, 0 if Non\n";

		int choice;

		cin >> choice;
		if (choice == 1) {

			this->isChronicDisease = true;
			break;
		}

		else if (choice == 0) {

			this->isChronicDisease = false;
			break;
		}
		cout << "\nPlease Enter a Valid Option from Below" << endl;
	}

	cout << "\nAny Other Disease:        (Press 0 If You Don't Have)\n";
	cin >> this->disease;

	string arr[8] = { "A+","A-","B+","B-" ,"AB+","AB-" ,"O+","O-" };
	bool isValid = false;

	while (!isValid) {

		cout << "\nEnter Your Blood Type From Choices Below" << endl;

		for (int i = 0; i < 8; i++) {

			cout << arr[i] << "  ";
		}
		cout << "\nYour Blood Type: ";

		string btype;
		cin >> btype;

		for (int i = 0; i < 8; i++) {

			if (btype == arr[i]) {

				setBloodType(btype);
				isValid = true;
				break;
			}
		}
		if (!isValid) {

			cout << "Please Enter a Valid Choice." << endl;
		}
	}

	cout << "\nEmail: ";
	this->setEmail();

	if (!approveDonorEmail(donors)) {

		this->email = "";
		return;
	}

	cout << "\nPassword: ";
	this->setPassword();


	while (true) {

		cin.clear();

		cout << "\nGender(M/F): ";
		cin >> gen;

		if (islower(gen)) {
			gen -= 32;
		}

		if (gen == 'F' || gen == 'M') {
			break;
		}
		cout << "Please Enter a Valid Choice." << endl;
	}

	this->setGender(gen);
}

Donor Donor::logIn(vector<Donor> donors) {

	string email;
	string password;
	bool isValid = false;

	cout << "Enter Email: ";
	cin >> email;

	cout << "Password: ";
	cin >> password;

	Donor d;

	for (int i = 0; i < donors.size(); i++) {

		if (email == donors.at(i).email) {

			if (password == donors.at(i).password) {

				d = donors.at(i);
				isValid = true;
				break;
			}
		}
	}

	if (!isValid) {
		cout << "\nEmail or Password is Incorrect" << endl;
	}

	return d;
}

int Donor::getChoices() {

	int choice = -1;

	cin >> choice;

	while (!cin.good()) {

		//Report a Problem
		cout << "!ERROR INVALID DATA TYPE!" << endl;

		//Clear Stream
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		//Get Input again
		cout << "Enter a Valid Choice" << endl;
		cin >> choice;
	}

	cin.clear();
	cin.ignore(INT_MAX, '\n');

	return choice;
}

void Donor::displayOptions(vector<Donor>&donors, map <string,int> &req , vector<Blood>& donations, int currentMonth, vector<Blood>& searchDonations) {
	
	int choice = -1;

	while (true) {

		cout << "\n1. Update Account\n2. Delete Account\n3. Make a Donation\n		Press 0 To Go Back" << endl;

		choice = getChoices();

		if (choice == 1) {

			this->updateAccount(currentMonth);

			for (int i = 0; i < donors.size(); i++) {

				if (this->email == donors.at(i).email) {

					donors.at(i).password = this->password;
					donors.at(i).age = this->age;
					donors.at(i).name = this->name;
					donors.at(i).isChronicDisease = this->isChronicDisease;

					break;
				}
			}
		}

		else if (choice == 2) {
			
			if (this->deleteAccount(donors)) {
				
				return;
			}
		}
		else if (choice == 3) {

			this->donation(donors, req, donations, currentMonth, searchDonations);
		}
		else if (choice == 0) {

			return;
		}

		else
			cout << "Please Enter a Valid Choice." << endl;
	}
}

bool Donor::approveDonorEmail(vector<Donor>& donors) {

	bool isValid = true;

	for (int i = 0; i < donors.size(); i++) {

		if (this->email == donors.at(i).email) {

			cout << "\nThis Email has Already been Used with Another Account." << endl;

			isValid = false;

			break;
		}
	}

	return isValid;
}

void Donor::updateAccount(int currentMonth) {

	int age;
	int chronicDisease;
	string email;
	string password;
	string name;

	while (true) {

		cout << "\n1. Change Password\n2. Update Information\nPress 0 To Go Back" << endl;
		int choice = getChoices();

		if (choice == 1) {

			cout << "Email: ";
			cin >> email;

			if (email == this->email) {

				cout << "Old Password: ";
				cin >> password;

				if (password == this->password) {

					cout << "New Password: ";
					cin >> password;
					this->password = password;
				}
				else {

					cout << "\nIncorrect Email or Password" << endl;
				}
			}
			else {
				cout << "\nIncorrect Email or Password" << endl;
			}
		}

		else if (choice == 2) {

			int infoSelection;

			cout << "\n1. Change Display Name\n2. Update Age\n3. Chronic Diseases\n Press 0 To Go Back" << endl;

			infoSelection = getChoices();

			if (infoSelection == 1) {

				cout << "\nNew Display Name(Press 0 To Cancel): ";
				cin >> name;

				if (name == "0") {
					continue;
				}

				else {

					this->name = name;
					cout << "\nDisplay Name Updated" << endl;
				}
			}

			else if (infoSelection == 2) {

				cout << "\nEnter Age(Press 0 To Cancel): ";
				cin >> age;
				this->age = age;
			}

			else if (infoSelection == 3) {
				cout << "Do You Have any Type Chronic Diseases:\n-Blood Pressure\n-Thyroid\n-Diabetes\n-Cancer\nEnter 1 if Exists, 0 if Non\n";
				chronicDisease = getChoices();

				if (chronicDisease == 1) {
					this->isChronicDisease = true;
				}
				else if (chronicDisease == 0) {
					this->isChronicDisease = false;
				}
			}
			else if (infoSelection == 0) {
				return;
			}
			else {
				cout << "Please Enter A Valid Option.";
			}
		}

		else if (choice == 0) {

			return;
		}
		else {

			cout << "Please Enter A Valid Option.";
		}
	}
}

bool Donor::deleteAccount(vector<Donor>& d) {


	cout << "Enter Your Email: " << endl;
	cin >> email;

	cout << "Enter Your Password" << endl;
	cin >> password;
	
	if (!d.empty()) {

		for (int i = 0; i < d.size(); i++) {

			if (email == d.at(i).email) {

				if (password == d.at(i).password) {

					d.erase(d.begin() + (i));

					cout << "\nThis account is deleted successfully." << endl;

					return true;
				}
				else {

					cout << "Email or Password is Incorrect" << endl;
					return false;
				}
			}
		}
	}
}

void Donor::donation(vector<Donor>& donors, map<string, int>& req, vector<Blood>& donations, int currentMonth, vector<Blood>& searchDonations) {

	if (!Verification(this->age, this->latestDonationDate, currentMonth)) {

		return;
	}

	if (this->isChronicDisease) {

		cout << "\nSorry " << this->name << ", Your Donation Request can not be Approved Due To your Health Conditions." << endl;
		return;
	}

	else {

		Blood b;

		b.donorName = this->name;
		b.bloodType = this->bloodType;
		b.quantity = 1;
		b.recievedMonth = currentMonth;
		b.expiryMonth = b.recievedMonth + 1;

		donations.push_back(b);
		searchDonations.push_back(b);

		map<string, int> ::iterator it;

		for (it = req.begin(); it != req.end(); it++) {

			if (this->bloodType == it->first) {

				req[it->first]++;
			}
		}

		this->latestDonationDate = currentMonth;

		for (int i = 0; i < donors.size(); i++) {

			if (this->email == donors.at(i).email) {

				donors.at(i).latestDonationDate = currentMonth;
			}
		}

		cout << "\nYour Donation Request Is Done." << endl;
	}
}