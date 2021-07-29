#pragma once
#include<string>

using namespace std;

class Request
{

public:

	int requestQuantity;
		
	string recipientName;
	string recipientemail;
	string requestType;
	string recipientHospitalName;

	int month;

	Request();
};