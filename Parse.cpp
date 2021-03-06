/*
This program uses a .csv file.
First column must be names,
second must be battletags,
third must be email addresses,
fourth must be continent,
fifth must be SR,
sixth must be role.
7th must be second choice role.
THE MUST BE NO DATA FURTHER DOWN THAN THE PLAYERS
*/
#include <vector>
#include <string>
#include "Player.h"
#include "Role.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Division.h"
//#include "stdafx.h"
using namespace std;

bool isnotprintable(char c) // will need to be modified if unicode is desired
{
	return !(c>=0 && c <128 && isprint(static_cast<unsigned char>(c)));
}

void cleaninput(string &str)
{
	str.erase(remove_if(str.begin(), str.end(), isnotprintable), str.end());
}

void parse(Division &europe, Division &NA, int count, string fileName) //Count is the number of players to process. Filename is that of the .csv file
{
	ifstream file(fileName);
	if (!file)
	{
		cout << "There was a problem opening the file. \n";
	}
	europe.m_division.resize(count);
	NA.m_division.resize(count);
	int europeCounter = 0;
	int NACounter = 0;
	string name;
	string battletag;
	string email;
	string srString;
	int sr;
	string roleString;
	Role role;
	string role2string;
	Role role2;
	string region;

	for (int i = 1; i <= count; ++i)
	{
		getline(file, name, ',');
		getline(file, battletag, ',');
		getline(file, email, ',');
		getline(file, region, ',');
		getline(file, srString, ',');
		getline(file, roleString, ',');
		getline(file, role2string);

		cleaninput(name);
		cleaninput(battletag);
		cleaninput(email);
		cleaninput(region);
		cleaninput(srString);
		cleaninput(roleString);
		cleaninput(role2string);

		sr = atoi(srString.c_str());
		if (roleString == "DPS")
			role = ROLE_DPS;
		else if (roleString == "Tank")
			role = ROLE_TANK;
		else if (roleString == "Support")
			role = ROLE_SUPPORT;
		else if (roleString == "any")
			role = ROLE_ANY;
		else
			cout << "Something was wrong with the role choice of player number " << i << ". \n";
		if (role2string == "DPS")
			role2 = ROLE_DPS;
		else if (role2string == "Tank")
			role2 = ROLE_TANK;
		else if (role2string == "Support")
			role2 = ROLE_SUPPORT;
		else if (role2string == "any")
			role2 = ROLE_ANY;
		else
			cout << "Something was wrong with the second role choice of player number " << i << ". \n";
		if (region == "Europe")
		{							//Assigns the data to a Player with the index i in the correct vector.
			europe.m_division[europeCounter].m_name = name;
			europe.m_division[europeCounter].m_battletag = battletag;
			europe.m_division[europeCounter].m_email = email;
			europe.m_division[europeCounter].m_sr = sr;
			europe.m_division[europeCounter].m_role = role;
			europe.m_division[europeCounter].m_role2 = role2;
			europeCounter++;
		}
		else if (region == "Americas")
		{

			NA.m_division[NACounter].m_name = name;
			NA.m_division[NACounter].m_battletag = battletag;
			NA.m_division[NACounter].m_email = email;
			NA.m_division[NACounter].m_sr = sr;
			NA.m_division[NACounter].m_role = role;
			NA.m_division[NACounter].m_role2 = role2;
			NACounter++;
		}
	}
	NA.m_division.resize(NACounter);

	europe.m_division.resize(europeCounter);

}
