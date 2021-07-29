#include<string>
#include <vector>

#ifndef USER_H
#define USER_H

using namespace std;
class User
{
public:

	int id;
	int age;
	char gender;

	string name;
	string email;
	string password;
	string bloodType;

	User();

	void setName();
	void setEmail();
	void setPassword();
	void setGender(char gender);
	void setAge(int);
	void setBloodType(string bloodType);
};
#endif