#include <iostream>
#include <map>
#include <random>
#include <ctime>
#include <fstream>
#include <sstream>
using namespace std;

mt19937 random_mt;

class State{
private:
    int income, population, hh_income, num_hh;
    string state;

public:
    State(){}

    State(string state, string income, string population, string hh_income, string num_hh){
        this->state = state;
        this->income = stoi(income);
        this->population = stoi(population);
        this->hh_income = stoi(hh_income);
        this->num_hh = stoi(num_hh);
    }
    void Display(){
        cout << state << endl;
        cout << "Population: " << population << endl;
        cout << "Per Capita Income: " << income << endl;
        cout << "Median Household Income: " << hh_income << endl;
        cout << "Number of Households: " << num_hh << endl;
    }
};

int Random(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(random_mt);
}

void RollDice(int num_rolls, int num_sides){
    map <int, int> roll;
    for (int i = 1; i <= num_sides; ++i) {
        roll[i] = 0;
    }
    for (int i = 0; i < num_rolls; ++i) {
        int value = Random(1, num_sides);
        roll[value]++;
    }
    map <int, int>::iterator iter;
    cout << endl;
    for (iter = roll.begin(); iter != roll.end(); iter++) {
        cout << iter->first << ": " << iter->second << endl;
    }
}

map<string, State> getData(string filename){
    ifstream file;
    map<string, State> states;
    file.open(filename,ios::in);
    string line, name, income, pop, hh_income, num_hh;
    //cout << file.is_open()<<endl;
    if(file.is_open()){
        getline(file, line);

        while(getline(file, line)){
            //getline(file, line);
            istringstream stream(line);
            getline(stream, name, ',');
            getline(stream, income, ',');
            getline(stream, pop, ',');

            getline(stream, hh_income, ',');
            getline(stream, num_hh, ',');
            State State(name, income, pop, hh_income, num_hh);
            states.emplace(name, State);
        }
    }
    return states;
}

int main()
{
	cout << "1. Random Numbers\n";
	cout << "2. State Info\n";

	int option;
	cin >> option;

	if (option == 1)
	{
		int randomSeed;
		cout << "Random seed value: ";
		cin >> randomSeed;
		random_mt.seed(randomSeed);

        int num_roll;
		cout << "Number of times to roll the die: ";
        cin >> num_roll;

        int num_sides;
        cout << "Number of sides on this die: ";
        cin >> num_sides;

        RollDice(num_roll, num_sides);
	}
	else if (option == 2)
	{
        map<string, State> states;
        states = getData("states.csv");
	   // Get input for option 1 (show all states) or 2 (do a search for a particular state)
        cout << "1. Print all states" << endl;
        cout << "2. Search for a state" << endl;
        cin >> option;

        if(option ==1){
            map <string, State>::iterator iter;

            for (iter = states.begin(); iter != states.end(); iter++) {
                iter->second.Display();
            }
        }
        else if(option == 2){
            string name;
            cin >> name;
            if(states.find(name) != states.end()){
                states[name].Display();
            }
            else{
                cout << "No match found for " << name << endl;
            }
        }
    }

	return 0;
}

