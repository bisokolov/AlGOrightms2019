#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class Attack {
	std::string Attackname;
	std::vector<std::string> monsters;
};


struct Monster {
	std::string name;
	std::vector<std::string> vurnabilities;
};

int main() {


	std::unordered_map<std::string, Monster> hashTable;

	int n;
	std::cin >> n;
	int i = 0;
	while (i < n) {
		std::string attackName;
		std::cin >> attackName;
		int k;
		std::cin >> k;
		int j = 0;
		
		while (j < k) {
			
			std::string monsterName;
			std::cin >> monsterName;
			
			std::unordered_map<std::string, Monster>::iterator it = hashTable.find(monsterName);
			if (it == hashTable.end()) {
				Monster mstr;
				mstr.name = monsterName;
				mstr.vurnabilities.push_back(attackName);
				hashTable[monsterName] = mstr;

				
			}
			else {
				hashTable[monsterName].vurnabilities.push_back(attackName);
			}
			++j;
		}

		
		++i;
	}
	

	int m = 0;
	std::cin >> m;
	 i = 0;
	while (i < m) {
		std::string checkMonster;
		std::cin >> checkMonster;
		
		if (hashTable[checkMonster].vurnabilities.empty()) {
			std::cout<<"[none]"<<std::endl;

		}
		else {
			for (int i = 0;i < hashTable[checkMonster].vurnabilities.size();++i) {
				std::cout << hashTable[checkMonster].vurnabilities[i] << " ";
			}
			std::cout << std::endl;
		}




		++i;
	}
	
	return 0;
}