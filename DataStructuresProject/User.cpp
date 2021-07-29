#include "User.h"
#include<iostream>


User::User() {
	name =  password = bloodType = "";
	email = "";
	age = id = 0;
	gender = ' ';
}
void User::setName() {
	cin>>this->name;
}

void User::setAge(int age) {
	this->age=age;
}

void User::setEmail() {
	cin >> this->email;
}

void User::setPassword() {
	cin >> this->password;
}

void User::setGender(char gen) {

	gender = gen;
}

void User::setBloodType(string btype) {

	this->bloodType = btype;
}