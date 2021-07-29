#pragma once
#include<string>
#include <vector>
#include <map>
#include"User.h"
#include "blood.h"

using namespace std;


class Donor : public User
{
public:

	string disease;
	bool isChronicDisease;
	int latestDonationDate;


	Donor();
	void registeration(vector<Donor>&, int);
	Donor logIn(vector<Donor>);
	bool approveDonorEmail(vector<Donor>&);
	void displayOptions(vector<Donor>& donors, map<string, int>& req, vector<Blood>& donations, int, vector<Blood>&);
	void donation(vector<Donor>&, map<string, int>& req, vector<Blood>& donations, int, vector<Blood>&);
	void updateAccount(int);
	bool deleteAccount(vector<Donor>&);
	int getChoices();

private:

	bool Verification(int age, int donationDate, int);
};
