#include <iostream>
#include <cstdlib>
#include "Header.h"
#include <string>
#include <fstream>
#include <ostream>
#include <map>
#include <array>
#include <sstream>
#include <array>
#include <vector>
using namespace std;

string name;
string partyName;

int main()
{

	string line;
	string text;
	string splitNum;
	int numCands = 0;
	int numBallots = 0;
	//Number of lines in general
	int numlines = 0;
	//First letter of candidate LinesCandidates is C
	char newCand = '#';
	//First letter of ballot LinesCandidates is B
	char newBallot = 'B';
	string CandidateCounter;
	string BallotCounter;
	stringstream ss;
	string tempname;
	//	int tempvalue;


	ifstream myfileoutput("Candidates.txt");

	if (myfileoutput.is_open())//COUNT Candidates and Ballots
	{
		while (!myfileoutput.eof())
		{
			getline(myfileoutput, CandidateCounter);
			numlines++;
			if (CandidateCounter.at(0) == newCand)
			{
				numCands++;
			}
			if (CandidateCounter.at(0) == newBallot)
			{
				numBallots++;
			}
		}
	}
	myfileoutput.close();


	string *Names;
	Names = new string[numCands];

	string *partyNames;
	partyNames = new string[numCands];

	string *LinesCandidates;
	LinesCandidates = new string[numCands];

	string *LinesBallots;
	LinesBallots = new string[numBallots];

	string *AllVotes;
	AllVotes = new string[numBallots];

	//string *SplitVotes;
	//SplitVotes = new string[numCands];

	vector<Candidate> Candidates(numCands);
	vector< vector<BallotPaper>> Ballots(numBallots, vector<BallotPaper>(numCands));


	/*ifstream myfile("Candidates.txt");

	if (myfile.is_open())//SPLIT
	{
		for (int i = 0; i < numCands; i++)
		{
			while (getline(myfileoutput, line));
			{
				ss.str(line);
				while (getline(ss, name))
				{
					cout << name;
				}
			}
		}
	}*/

	ifstream myfileo("Candidates.txt"); //Splitting candidate lines into name and partynames

	if (myfileo.is_open())
	{
		for (int i = 0; i < numlines; i++)
		{
			getline(myfileo, line);

			if (line.at(0) == newCand)
			{
				int pos = line.find_first_of(',');

				LinesCandidates[i] = line;

				Names[i] = LinesCandidates[i].substr(1, pos);
				partyNames[i] = LinesCandidates[i].substr(pos + 1);
			}

			if (line.at(0) == newBallot)
			{
				LinesBallots[i - numCands] = line;
				AllVotes[i - numCands] = LinesBallots[i - numCands].substr(1);
			}

		}
	}
	myfileo.close();

	for (int i = 0; i < numCands; i++)
	{
		Candidates[i].setName(Names[i].substr(0, Names[i].length() - 1));
		Candidates[i].setPartyName(partyNames[i]);
	}

	cout << "\n*******************CANDIDATE NAMES AND PARTYS*******************\n";

	for (int i = 0; i < numCands; i++)
	{
		cout << "Candidate " << i + 1 << "\n";
		cout << "Name is : " << Candidates[i].getName();
		cout << "\n";
		cout << "Party name is : " << Candidates[i].getPartyName();
		cout << "\n";
	}

	for (int i = 0; i < numBallots; i++)
	{
		string tobesplit = AllVotes[i];

		//stringstream ss(tobesplit);

		for (int j = 0; j < numCands; j++)
		{
			int temp = (int)tobesplit.at(j) - 48;

			Ballots[i][j].setPreference(temp, Candidates[j].getName());
		}

		//for (int j = 0; j < numBallots; j++)
		//{

		//Runs through splitting each of the lines of votes into individual numbers
		//getline(ss, splitNum, ' ');


		//Runs through loop for each Candidate
		//for (int j = 0; j < numCands; j++)
		//{
			//Runs through splitting each of the lines of votes into individual numbers
			//getline(ss, splitNum, ' ');
			//SplitVotes[i] = splitNum;



		//cout << " Num is : " << splitNum;
		//tempname = Candidates[i].getName();//Setting a Candidate name
		//tempvalue = atoi(SplitVotes[i].c_str());//Setting the votes the candidate got
		//int tempvalue = atoi(splitNum.c_str());
		//Ballots[i].setPreference(tempvalue, tempname);

		//}
	}

	cout << "\n*******************VOTER'S PREFERENCES*******************\n";

	for (int i = 0; i < numBallots; i++)
	{
		cout << "\nVoter number " << i + 1 << " : \n";
		for (int j = 0; j < numCands; j++)
		{
			//int temp = Ballots[i][j].getVote();
			//SplitVotes[j] = temp;
			cout << "Gave the preference : " << Ballots[i][j].getVote() <<
				" to the cadidate " << Ballots[i][j].getCName() << "\n";
		}

	}



	/*cout << "Which voters preferences would you like to see? \n";
	for (int i = 0; i < numBallots; i++)
	{
		cout << "Voter : " << i + 1 << "?\n";
	}
	int input;
	cin >> input;

	cout << "For which preference would you like to see the candidate for? \n";
	int input2;
	cin >> input2;

	for (int j = 0; j < numBallots; j++)
	{
		cout << Ballots[input][j].getPreference(input2);
	}*/


	vector<VoteCounter> VoteCount(numCands);


	for (int i = 0; i < numCands; i++)
	{
		int votecount = 0;
		for (int j = 0; j < numBallots; j++)
		{

			int temp = Ballots[j][i].getVote();

			if (temp == 1)
			{
				votecount++;
			}
			VoteCount[i].setVoteCount(votecount, Ballots[j][i].getCName());
		}
	}

	cout << "\n*******************WHAT EACH CANDIDATE GOT*******************\n";

	for (int i = 0; i < numCands; i++)
	{
		cout << "Candidate " << i + 1 << " got \n";
		for (int j = 0; j < numBallots; j++)
		{
			cout << Ballots[j][i].getVote() << "\n";
		}
	}

	cout << "\n*******************EACH CANDIDATES COUNT OF 1 VOTES*******************\n";

	for (int i = 0; i < numCands; i++)
	{
		cout << "\nThe count of 1's for candidate " << Candidates[i].getName() << " is " << VoteCount[i].getCount(Candidates[i].getName()) << "\n";
	}


	cout << "\n*******************ELIMINATION*******************\n";


	int Highestindex;

	int highest = 0;

	for (int i = 0; i < numCands; i++)
	{
		int num = numCands;
		int temp = VoteCount[i].getCount(Candidates[i].getName());

		if (temp > highest)
		{
			highest = temp;
			Highestindex = i;
		}
	}


	cout << "\nCandidate " << Candidates[Highestindex].getName() << " is the winner! \n";

	system("pause");	

}
