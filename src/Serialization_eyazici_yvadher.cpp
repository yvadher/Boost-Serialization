//============================================================================
// Name        : Serialization_eyazici_yvadher_project.cpp
// Author      : Yagnik and Enes
// Version     :
// Copyright   : Your copyright notice
// Description : Serialization_
//============================================================================

using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>  // Libraries for using archive serialization funcatnality
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

class skill   // Base class which has player skills in intger variable.
{
public:
	skill()  //Constructer
	{
		attacking=0;
		defending=0;
		stamina=0;
	}
	skill(int attacking_power, int defending_power, int stamina_power) // Constructer
	{
		this->attacking= attacking_power;
		this->defending= defending_power;
		this->stamina= stamina_power;
	}
	friend class boost::serialization::access;    // accessing the boost serialization
	template<class Archive> // serialization of variables (attacking,defending,stamina).
	void serialize(Archive & ar, const unsigned int version)
	{
		cout<<"Serializing Skills Object"<<endl;
		ar & attacking & defending & stamina;
	}
protected:
	int attacking;
	int defending;
	int stamina;
};

class player: public skill   // Derived class
{
public:
	virtual ~player()
	{
		//
	}
	player() // Default constructor
	{
		playerName="";
	}
	player(string name,int attacking_power, int defending_power, int stamina_power) // constructor
	{
		this->playerName=name;
		this->attacking= attacking_power;
		this->defending= defending_power;
		this->stamina= stamina_power;
	}
	string getPlayerName(){return playerName;}
	virtual int getAttacking(){return attacking;}
	virtual int getDefending(){return defending;}
	virtual int getStamina(){return stamina;}
	string playerName;
	void print_player()  // Print the particular player information
	{
		cout<<playerName<<endl;
		cout<<"Attacking : "<<getAttacking()<<endl;
		cout<<"Defending : "<<getDefending()<<endl;
		cout<<"Stamina : "<<getStamina()<<endl;
	}
private:
	friend class boost::serialization::access;  // accessing the boost serialization
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{  // serialization of variables (attacking,defending,stamina,playerName).
		cout<<"Serializing player Object :"<<endl;
		boost::serialization::base_object<skill>(*this);  // Serialize the base class
		ar & playerName;
		ar & attacking & defending & stamina;
	}

};

class team: public player
{
public:
	team()  // Default constructor
	{
		teamName="";
		attackingTeam=0;
		defendingTeam=0;
		staminaTeam=0;
	}
	team(string name)   // constructor
	{
		teamName=name;
	}
	virtual int getAttacking()
	{
		return attackingTeam;
	}
	virtual int getDefending()
	{
		return defendingTeam;
	}
	virtual int getStamina()
	{
		return staminaTeam;
	}
	void add_players(vector<player>add_players)
	{
		for (unsigned int i=0;i<add_players.size();i++)  // add player to players vector.
		{
			players.push_back(add_players[i]);
		}
		int attack_power=0,defend_power=0,stamina_power=0;
		int size = players.size();
		for (unsigned int i=0;i<size;i++)  //Averages the players skills and store it in team.
		{
			attack_power+=players[i].getAttacking();
			defend_power+=players[i].getDefending();
			stamina_power+=players[i].getStamina();
		}
		attackingTeam= attack_power/size;
		defendingTeam= defend_power/size;
		staminaTeam= stamina_power/size;
	}
	void remove_players(vector<player>remove_players)
	{
		//need a search algorithm
	}
	virtual ~team(){}  // distructer. not needed now but could be usefull after improvements.
	void print_object(){
 // Print the Team object informations
		cout<<"\nTeam name : "<<teamName<<endl;
		cout<<"Team Power"<<endl;
		cout<<"Team Attacking Power : "<<attackingTeam<<endl;
		cout<<"Team Defending Power : "<<defendingTeam<<endl;
		cout<<"Team Stamina Power : "<<staminaTeam<<endl;
		cout<<"Player Names: "<<endl;
		for (unsigned int i=1; i<=players.size();i++)
		{
			cout<<i<<"."<<endl;
			players[i-1].print_player();
			cout<<endl;
		}
	}

private:
	string teamName;
	vector<player> players;
	friend class boost::serialization::access; // accessing the boost serialization
	int attackingTeam,defendingTeam,staminaTeam;
	template<class Archive>
	    void serialize(Archive & ar, const unsigned int version)
	    { // serialization of variables (attackingTeam,defendingTeam,staminaTeam,players,TeamName).
			cout<<"Serializing Team Object"<<endl;
			ar & boost::serialization::base_object<player>(*this);
			ar & teamName;
			ar & attackingTeam & defendingTeam & staminaTeam;
			ar & players;

	    }
};

void write(team team1)   // Serialize file from object.
{
	//writing(saving the serial object) into storedData.txt
	std::ofstream ofs("storedData.txt");
	boost::archive::text_oarchive oa(ofs);	//text archive to render data as text
	oa << team1;
	//ofs.close();
}

void read(team &team1)   // To restore object from serialized file.
{
	//reading(loading the serial object) to a new object called team1
	// create and open an archive for input
	std::ifstream ifs("storedData.txt");
	cout<<ifs<<endl;
	boost::archive::text_iarchive ia(ifs);
	// read class state from archive
	ia >> team1;
	ifs.close();
}

int main()
{
	// Storing the data in team objects.
	player enes("enes",0,80,80);
	player yagnik("yagnik",100,50,50);
	vector<player>Team1_Saved_players;
	Team1_Saved_players.push_back(enes);
	Team1_Saved_players.push_back(yagnik);
	team Team1_Saved("Team1_Saved");
	Team1_Saved.add_players(Team1_Saved_players);
	// serialize the data.
	write(Team1_Saved);
	// Output could be seen in the pproject directory under name of stored data.
	team Team2_restored;
	// Restores the data which is serialized and which is in the text file.
	read(Team2_restored);
	// Print the result which is restored from the string base serialization.
	Team2_restored.print_object();
	return 0;
}


