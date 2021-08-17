#include <iostream>
#include <iomanip> 

using namespace std;

int gameboard[4][4];

void gameboard_display();

void gameboard_initialization() {
	int numbers[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
	int numbers_random_order[16];
	for (int i = 0; i < 16;i++) {
		int tmp = rand() % (16 - i);
		numbers_random_order[i] = numbers[tmp];
		for (int j = tmp;j < 15;j++) {
			numbers[j] = numbers[j + 1];
		}
	}
	//int tmp[16] = { 1,16,3,4,5,2, 6,7,8,9,10,11,12,13,14,15};
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			gameboard[i][j] = numbers_random_order[i * 4 + j];
		}
	}
	cout << "Random Start Position:" << endl;
	gameboard_display();
}

void gameboard_display(){
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			if (gameboard[i][j] == 16) {
				cout << setfill(' ') << setw(4) << " ";
			}
			else cout << setfill(' ') << setw(4) << gameboard[i][j];
		}
		cout << endl;
	}
	cout << endl;
}


int moves_test(int input) {
	// find the location of the empyty spot
	int x, y;
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			if (gameboard[i][j] == 16) {
				x = i;
				y = j;
			}
		}
	}

	if (input != 2 && input != 4 && input != 6 && input != 8) return 0;

	if ((y == 0 && input == 6) || (y == 3 && input == 4) || (x == 0 && input == 2) || (x == 3 && input == 8)) return 0;
	else return 1;
}

void gameboard_update(int input) {
	// find the location of the empyty spot
	int x, y;
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			if (gameboard[i][j] == 16) {
				x = i;
				y = j;
			}
		}
	}

	if (input == 2) {
		gameboard[x][y] = gameboard[x - 1][y];
		gameboard[x - 1][y] = 16;
	}
	else if (input == 4) {
		gameboard[x][y] = gameboard[x][y+1];
		gameboard[x][y+1] = 16;
	}
	else if (input == 6) {
		gameboard[x][y] = gameboard[x][y -1];
		gameboard[x][y - 1] = 16;
	}
	else if (input == 8) {
		gameboard[x][y] = gameboard[x+1][y ];
		gameboard[x+1][y] = 16;
	}

	gameboard_display();
}


int result_test() {
	int numbers[15];
	int tmp = 0;
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			if (gameboard[i][j] != 16) {
				numbers[tmp] = gameboard[i][j];
				tmp++;
			}
		}
	}

	for (int i = 0;i < 14;i++) {
		if (numbers[i] > numbers[i + 1]) return 0;
	}
	return 1;
}

int main() {
	// Initialize gameboard;
	gameboard_initialization();
	if (result_test()) {
		cout << "You are lucky! You win!\n\n";
		return 0;
	}
	int input;
	while (1) {
		cout << "Your move: (4=left, 8=up, 6=right, 2=down, 0=stop game): ";
		cin >> input;
		//Testify moves;
		if (input == 0) {
			cout << "You stopped the game!" << endl;
			return 0;
		}
		else {
			if (!moves_test(input)) cout << "You entered an invalid number. Please re-enter it! " << endl;
			else gameboard_update(input);
		}

		//Testify end of game;
		if (result_test()) {
			cout << "Congratulations! You win!\n\n";
			return 0;
		}

	}
	return 0;
}
