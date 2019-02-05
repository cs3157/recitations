#include <vector>
#include <iostream>
#include <string>

using namespace std;

template <typename T>
void printList(std::vector<T> list) {
	for (size_t i = 0; i<list.size(); i++) {
		cout << list.at(i) << endl;
	}
	
	cout << endl;
}

int main() {
	vector<int> intList;
	vector<int> intList2;
	vector<string> stringList;

	intList.push_back(1);
	intList.push_back(2);
	// intList.push_back("asdf");

	intList2.push_back(-1);
	intList2.push_back(-2);

	stringList.push_back("hello ");
	stringList.push_back("AP!");

	vector<vector<int>> listOfLists;
	listOfLists.push_back(intList);
	listOfLists.push_back(intList2);
	// listOfLists.push_back(stringList);

	for (int i = 0; i < listOfLists.size(); ++i)
		for (size_t j = 0; j < listOfLists.at(i).size(); ++j)
			cout << listOfLists.at(i).at(j) << endl;

	for (int i = 0; i < stringList.size(); ++i)
		cout << stringList.at(i) << endl;
}
