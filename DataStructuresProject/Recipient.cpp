#include "Recipient.h"
#include "Donor.h"
#include "Request.h"
#include "Blood.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

Recipient::Recipient() {

	 DoctorOfCase = HospitalName = "";
}

void Recipient::Register(vector<Recipient>& recipients) {

	char gen = ' ';
	int age = -1;

	cout << "\nPlease Enter Your Personal Information" << endl;

	cout << "\nName: ";
	this->setName();

	cout << "\nAge: ";
	age = getChoices();
	this->setAge(age);

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

	cout << "\nEmail: ";
	this->setEmail();

	if (!approveRecipientEmail(recipients)) {

		this->email = "";
		return;
	}

	cout << "\nPassword: ";
	this->setPassword();

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

			cout << "\nPlease Enter a Valid Choice." << endl;
		}
	}

	cout << "\nHospital Name:";
	cin >> this->HospitalName;

	cout << "\nDoctor Responsible Your The Case:";
	cin >> this->DoctorOfCase;

}

Recipient Recipient::Login(vector<Recipient>& rec, vector<Donor> &donor) {

	string email;
	string password;

	Recipient r;

	bool isValid=false;

	cout << "Enter Email: ";
	cin >> email;

	cout << "Password: ";
	cin >> password;

	for (int i = 0; i < rec.size(); i++) {

		if (email == rec.at(i).email) {

			if (password == rec.at(i).password) {

				r = rec.at(i);
				isValid = true;
				break;
			}
		}
	}

	if (!isValid) {
		cout << "Email or Password is Incorrect" << endl;
	}

	return r;
}

int Recipient::getChoices() {

	int choice = -1;

	cin >> choice;

	while (!cin.good()) {
		//Report a Problem
		cout << "!ERROR INVALID DATATYPE!" << endl;

		//Clear Stream
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		//Get Input again
		cout << "Enter a Valid Choice..." << endl;
		cin >> choice;
	}

	cin.clear();
	cin.ignore(INT_MAX, '\n');

	return choice;
}


bool Recipient::approveRecipientEmail(vector<Recipient>& recipients) {

	bool isValid = true;

	for (int i = 0; i < recipients.size(); i++) {

		if (this->email == recipients.at(i).email) {

			cout << "\nThis Email has Already been Used with Another Account." << endl;

			isValid = false;

			break;
		}
	}

	return isValid;
}

void Recipient::DisplayFunctionalities(vector<Recipient>& rec, vector<Donor> donor, map<string, int>& req, vector<Request>& requests, vector<Blood>& donations, int currentMonth, vector<Blood>& searchDonations) {

	int rec_choice = -1;

	while (true) {

		cout << "\nChoose One Of The Options Below" << endl << endl;
		cout << "1. Update Your Account Information\n2. Search and Request For Available Blood Type\n3. Delete The Account\n4. Show request history	\n5. Display Blood Data\nPress 0 To Go Back\n";
		
		rec_choice=getChoices();

		if (rec_choice == 1)
			this->UpdateAccount(rec);

		else if (rec_choice == 2)
			this->SearchForAvailablity(req, requests, currentMonth, searchDonations);

		else if (rec_choice == 3) 
		{

			if(this->DeleteAccount(rec))
			return;

		}
		else if (rec_choice == 4) {

			this->ShowRequestHistory(requests);
		}
		else if (rec_choice == 5) {

			this->DisplayBloodData(donations);
		
		}
		else if (rec_choice == 0)
			break;

		else {
			cout << "Please Enter a display Valid Choice." << endl;
		}
	}
}

void Recipient::UpdateAccount(vector<Recipient>& rec) {

	int updatechoice = -1;
	string newName, newpass, newHospitalName, newemail, newDoctorOfCase;

	while (true)
	{
		cout << "Choose What To Update In Your Account: " << endl;
		cout << "1. Name\n2. Password\n3. Hospital" << endl;
		cout << "4.Doctor Responsible For The Case\n	Press 0 To Go Back\n";

		updatechoice=getChoices();

		if (updatechoice == 1) {

			for (int i = 0; i < rec.size(); i++) {

				if (rec.at(i).email == this->email) {

					cout << "Enter The New Name: ";
					cin >> newName;

					rec.at(i).name = newName;
					this->name = newName;

					cout << "The New Data Changed Successfully" << endl;
				}
			}
		}

		else if (updatechoice == 2) {

			for (int i = 0; i < rec.size(); i++) {

				if (rec.at(i).email == this->email) {

					cout << "Enter The New Password: ";
					cin >> newpass;

					rec.at(i).password = newpass;
					this->password = newpass;

					cout << "The New Data Changed Successfully" << '\n';
				}
			}

		}

		else if (updatechoice == 3) {

			for (int i = 0; i < rec.size(); i++){

				if (rec.at(i).email == this->email) {

					cout << "Enter The New Hospital: ";
					cin >> newHospitalName;

					rec.at(i).HospitalName = newHospitalName;
					this->HospitalName = newHospitalName;

					cout << "The New Data Changed Successfully" << '\n';
				}
			}
		}
		else if (updatechoice == 4) {

			for (int i = 0; i < rec.size(); i++) {

				if (rec.at(i).email == this->email) {

					cout << "Enter The Doctor Of The Case: ";
					cin >> newDoctorOfCase;

					rec.at(i).DoctorOfCase = newDoctorOfCase;
					this->DoctorOfCase = newDoctorOfCase;

					cout << "The New Data Changed Successfully" << '\n';
				}
			}
		}
		else if (updatechoice == 0)
			break;
		else {
			cout << "Please Enter a update Valid Choice." << endl;
		}
	}
}


void Recipient::DisplayBloodData(vector<Blood> donations)
{

	if (donations.size() == 0) {
		cout << "Sorry There is No Donations Available Yet...\n";
		return;
	}

	cout << "Displaying Blood Data: \n";
	for (int i = 0; i < donations.size(); i++) {

		cout << "-------------------------------\n";
		cout << "Donor Name: " << donations.at(i).donorName << '\n';
		cout << "Blood Type: " << donations.at(i).bloodType << '\n';
		cout << "Available Quantity: " << donations.at(i).quantity << '\n';
		cout << "Received Month: " << donations.at(i).recievedMonth << '\n';
		cout << "Expiry Month: " << donations.at(i).expiryMonth << '\n';
		cout << "-------------------------------\n";
	}
}

void Recipient::RequestBloodType(map<string, int>& req, vector<Request>& requests, string type, int quantity, vector<Blood>& searchDonations, int currentMonth) {
	
	int choice;

	map<string, int> ::iterator it;

	Request currentRequest;
	string hospitalName;

	currentRequest.recipientemail = this->email;
	currentRequest.recipientName = this->name;
	currentRequest.requestQuantity = quantity;
	currentRequest.requestType = type;
	currentRequest.month = currentMonth;

	cout << "Do you want the blood to deliver in your hospital or another one press 0 for same hospital and 1 for another hospital" << endl;
	
	while (true) {

		choice=getChoices();

		if (choice == 0) {

			currentRequest.recipientHospitalName = this->HospitalName;
			break;
		}
		else if (choice == 1) {

			cout << "Enter the hospital name" << endl;
			cin >> hospitalName;

			currentRequest.recipientHospitalName = hospitalName;
			break;
		}
		else
			cout << "Enter A valid choice"<<endl;
		
	}

	for (it = req.begin(); it != req.end(); it++) {

		if (it->first == type) {

			if (it->second >= quantity) {

				req[it->first] -= quantity;
			}
		}
	}

	requests.push_back(currentRequest);

	for (int i = 0; i < searchDonations.size(); i++) {

		if (searchDonations.at(i).bloodType == type && searchDonations.at(i).quantity == quantity) {

			searchDonations.erase(searchDonations.begin() + (i));
			break;
		}
	}
}

void Recipient::SearchForAvailablity(map<string, int>& req,vector<Request>&requests, int currentMonth, vector<Blood>& searchDonations) {

	map<string, int> ::iterator it;
	
	string type;

	string ABnegCompatible[4] = { "AB-","O-","B-","A-" };
	string AposCompatible[4] = { "A+","O-","O+","A-" };
	string BposCompatible[4] = { "B+","O-","O+","B-" };
	
	int choice = -1, quantity = -1;
	char requestChoice;
	bool isFound = false;
	string requestedType;

	if (!searchDonations.empty()) {

		for (int i = 0; i < searchDonations.size(); i++) {

			if (searchDonations.at(i).expiryMonth < currentMonth) {

				searchDonations.erase(searchDonations.begin() + (i));
			}
		}
	}

	cout << "press\n1. if you want to search your own type or any compitable type \n 2. to search for a different type or any compitable type." << endl;

	choice=getChoices();

	if (choice == 1) {
		
		type = this->bloodType;
	}

	else if (choice == 2) {
		cout << "Enter the type you want" << endl;
		cin >> type;
		
	}
	else {
		cout << "Sorry You Entered Wrong Invalid Choice!\n";
		cout << "Please Re-Search For Blood If You Want.\n";
		cout << "-------------------------------------\n";
		return;
	}
	
		cout << "Enter the quantity you want: ";
		quantity=getChoices();
	
	
	if (type == "AB+")
	{
		for (it = req.begin(); it != req.end(); it++) {
			if (quantity <= it->second) {
				isFound = true;
				requestedType = it->first;
				break;
			}
		}

	}

	else if (type == "A+") {

		for (int i = 0; i < 4; i++) {

			for (it = req.begin(); it != req.end(); it++) {

				if (AposCompatible[i] == it->first && quantity <= it->second) {
					isFound = true;
					requestedType = it->first;
					break;
				}
			}

			if (isFound)
				break;
		}
	}

	else if (type == "A-") {

		for (it = req.begin(); it != req.end(); it++) {

			if (it->first == "A-" || it->first == "O-") {

				if (quantity <= it->second) {

					isFound = true;
					requestedType = it->first;
					break;
				}
			}
		}
	}


	else if (type == "AB-") {

		for (int i = 0; i < 4; i++) {

			for (it = req.begin(); it != req.end(); it++) {

				if (it->first == ABnegCompatible[i] && it->second >= quantity) {

					isFound = true;
					requestedType = it->first;
					break;
				}

			}

			if (isFound)
				break;
		}
	}

	else if (type == "B+") {

		for (int i = 0; i < 4; i++) {

			for (it = req.begin(); it != req.end(); it++) {

				if (BposCompatible[i] == it->first && quantity <= it->second) {

					isFound = true;
					requestedType = it->first;
					break;
				}
			}

			if (isFound)
				break;
		}
	}

	else if (type == "B-") {

		for (it = req.begin(); it != req.end(); it++) {

			if (it->first == "B-" || it->first == "O-") {

				if (quantity <= it->second) {

					isFound = true;
					requestedType = it->first;
					break;
				}
			}
		}
	}

	else if (type == "O+") {

		for (it = req.begin(); it != req.end(); it++) {

			if (it->first == "O+" || it->first == "O-") {

				if (quantity <= it->second) {

					isFound = true;
					requestedType = it->first;
					break;
				}
			}
		}


	}
	else if (type == "O-") {

		for (it = req.begin(); it != req.end(); it++) {

			if (it->first == type) {

				if (quantity <= it->second) {

					isFound = true;
					requestedType = it->first;
					break;
				}
			}
		}

	}
	else {
		cout << "Invaid Blood Type.";
		cout << "-----------------------------\n\n";
		return;
	}

	if (!isFound) {

		cout << "Unfortunately We Can't Find Any Donors Try Again Later\n";
	}
	else {

		while (true) {
			cout <<"type:   " << requestedType << endl;
			cout << "Do you want to request Blood Type press Y if yess and N for no" << endl;

			cin >> requestChoice;

			if (requestChoice == 'Y' || requestChoice == 'y') {

				RequestBloodType(req, requests, requestedType, quantity, searchDonations, currentMonth);
				break;
			}
			else if (requestChoice == 'n' || requestChoice == 'N') {
				break;
			}
			else
			{
				cout << "Enter A valid choice" << endl;
			}
		}
	}
}

void Recipient::ShowRequestHistory(vector<Request> requests) 
{
	if (requests.size() == 0) {

		cout << "You Didn't Request Any Blood Before.\n";
		cout << "-----------------------------\n";
		return;
	}

	for (int i = 0; i < requests.size(); i++) {

		if (requests.at(i).recipientemail == this->email)
		{
			cout << "-------------------------------\n";
			cout << "Requested Type: " << requests.at(i).requestType << endl << "Requested Quantity: " << requests.at(i).requestQuantity <<endl<<"Hospital Name: "<<requests.at(i).recipientHospitalName <<endl;
			cout << "Month Of Request: " << requests.at(i).month << endl;
			cout << "-------------------------------\n";

		}
	}
}

bool Recipient::DeleteAccount(vector<Recipient>& rec) {
	
	cout << "Enter Your Email: " << endl;
	cin >> email;

	cout << "Enter Your Password" << endl;
	cin >> password;

	if (!rec.empty()) {

		for (int i = 0; i < rec.size(); i++){

			if (email == rec.at(i).email) {

				if (password == rec.at(i).password) {

					rec.erase(rec.begin() + (i));
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