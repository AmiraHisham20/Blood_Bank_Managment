#pragma once

#include<string>
#include<vector>
#include"Donor.h"
#include"User.h"
#include "Request.h"

using namespace std;

class Recipient :public User
{
public:
	
	string HospitalName;
	string DoctorOfCase;

	Recipient();

	void Register(vector<Recipient>& recipients);
	Recipient Login(vector<Recipient>& rec, vector<Donor>&);
	bool approveRecipientEmail(vector<Recipient>& recipients);

	void DisplayFunctionalities(vector<Recipient>& , vector<Donor>, map<string, int>&, vector<Request>&, vector<Blood>& , int, vector<Blood>&);
	void UpdateAccount(vector<Recipient>& rec);
	bool DeleteAccount(vector<Recipient>& rec);
	void SearchForAvailablity(map<string, int>& , vector<Request>&, int, vector<Blood>&);
	void RequestBloodType(map<string, int>&, vector<Request>&, string, int, vector<Blood>&,int );
	void ShowRequestHistory(vector<Request>);
	void DisplayBloodData(vector<Blood>);
	int getChoices();
};