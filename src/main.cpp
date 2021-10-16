#include <iostream>
#include <vector>
#include <map>

using namespace std;

int position(int s, vector<int> pci);
map<int, vector<int>> gale_shapley(vector<int> S, vector<int> C, map<int, vector<int>> PS, map<int, vector<int>> PC);
void print_result(map<int, vector<int>> res);

int main()
{
	// input:
	// vector<int> S: vector of students
	// vector<int> C: vector of classes capacity
	// map<int, vector<int>> PS: Students preferences
	// map<int, vector<int>> PC: Classes preferences
	vector<int> S{0, 1, 2, 3, 4, 5};
	vector<int> C{2, 4};

	map<int, vector<int>> PS = {
		{0, {1, 0}},
		{1, {0, 1}},
		{2, {0, 1}},
		{3, {1, 0}},
		{4, {1, 0}},
		{5, {1, 0}}};
	map<int, vector<int>> PC = {
		{0, {0, 5, 2, 4, 3, 1}},
		{1, {1, 5, 2, 3, 0, 4}}};

	map<int, vector<int>> affectation = gale_shapley(S, C, PS, PC);

	print_result(affectation);
	return 0;
}

int position(int s, vector<int> pci)
{
	int pps = -1;
	for (unsigned int j = 0; j < pci.size(); j++)
	{
		if (pci[j] == s)
		{
			pps = j;
			break;
		}
	}
	return pps;
}

map<int, vector<int>> gale_shapley(vector<int> S, vector<int> C, map<int, vector<int>> PS, map<int, vector<int>> PC)
{
	// Initialization:
	map<int, vector<int>> affectation; // result
	for (unsigned int i = 0; i < C.size(); i++)
	{
		affectation[i] = {};
	}
	vector<int> freeS = S;
	int pps, ppi;
	int s;
	bool affected;
	while (!freeS.empty())
	{						// while there is allways non affected student then do
		s = *freeS.begin(); // select first student in the list
		cout << "Student : " << s << "------------------------------------------------------------------------------------------"<< endl;
		affected = false; // set affected as false, (the student
		for (unsigned int i = 0; i < PS[s].size(); i++)
		{ // select the classes frome the most desired to the least desired, we suppose that the preferece list is ordered like that
			cout << "Class : " << PS[s][i] << "---------------------------------------------------------------------------------" << endl;
			if (affectation[PS[s][i]].size() < C[PS[s][i]])
			{				// if capacity of class isn't reached yet then inserts
				cout << "Class : " << PS[s][i] << " effectif is : " << affectation[PS[s][i]].size() << endl;
				affectation[PS[s][i]].push_back(s); // insert the student s in the class i
				affected = true;			 // set affected true
				cout << "Student : " << s << " is affected to Class : " << PS[s][i] << endl;
				freeS.erase(freeS.begin());
				break; // continue to the next student s
			}
			else
			{							  // the case in which the capacity of class i has been reached
				pps = position(s, PC[PS[s][i]]); // get the position of student s ins preferences list of classes i
				cout << "Preferences Student " << s << " Position is : " << pps <<endl;
				if (pps < 0)
					continue; // if the position obtained is negative then the student s doesn't figure in that list then continue
				for (auto it = affectation[PS[s][i]].begin(); it != affectation[PS[s][i]].end(); it++)
				{
					ppi = position(*it, PC[PS[s][i]]);
					if (ppi > pps)
					{
						affectation[PS[s][i]].erase(it);
						freeS.push_back(*it);
						affectation[PS[s][i]].insert(it, s);
						affected = true;
						cout << "Student " << s << " is affected to class : " << PS[s][i] << endl;
						freeS.erase(freeS.begin());
						break;
					}
				}
				if (affected)
					break;
			}
		}
	}
	return affectation;
}

void print_result(map<int, vector<int>> res)
{
	for ( unsigned int i = 0; i < res.size(); i++)
	{
		cout << i << "\t:\t";
		for (unsigned int j = 0; j < res[i].size(); j++)
		{
			cout << res[i][j] << " ";
		}
		cout << endl;
	}
}
