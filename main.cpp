#include <string>
#include <iostream>
#include <ctime>
using namespace std;

int deposit(int balance) {
	int deposit = 0;

	 do{
		//if (cin.fail()) {cin.clear();cin.ignore(numeric_limits<streamsize>::max(), '\n');}
		cout << "How much money do you wish to deposit? (100, 300 or 500)" << endl;
		cin >> deposit;

		if (deposit == 100 || deposit == 300 || deposit == 500) {
			balance += deposit;
			cout << deposit << "kr has now been deposited." << endl;
		}
		else {
			cout << "We could not process your deposit due to a lager 8 problem. Please try again." << endl;
		}
	}while (deposit != 100 && deposit != 300 && deposit != 500); //do-while vilkoret.
	return balance;
}

string getRandomSlot() {
	string slotValue[3] = {"X","Y","Z"};
	return slotValue[rand() % 3];
	/*
	Restdivision utav tal som kommer från rand funktionen.
	Alternativen kan vara 0, 1 eller 2. 
	Funktionen returnerar sedan värdet på plats 0, 1 eller 2 i arrayn "slotValue".
	*/
}

int results(string board[3][3]) {
	int winningRows = 0;
	/*
	Kontrollerar vinst i alla möjliga fält på spelfältet och adderar 1 till variablen "winningRows" för varje hel rad.
	*/
	if (board[0][0] == board[0][1] && board[0][0] == board[0][2])
		winningRows++;
	if (board[1][0] == board[1][1] && board[1][0] == board[1][2])
		winningRows++;
	if (board[2][0] == board[2][1] && board[2][0] == board[2][2])
		winningRows++;

	if (board[0][0] == board[1][0] && board[0][0] == board[2][0])
		winningRows++;
	if (board[0][1] == board[1][1] && board[0][1] == board[2][1])
		winningRows++;
	if (board[0][2] == board[1][2] && board[0][2] == board[2][2])
		winningRows++;

	if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
		winningRows++;
	if (board[2][0] == board[1][1] && board[2][0] == board[0][2])
		winningRows++;

	//returnerar antal rader som vann
	return winningRows;
}

int runMachine(int balance) {
	string board[3][3];
	int multiplikationsTabellen[6] = {2, 3, 4, 5, 7, 10}; //Array med det som användarens bet ska multipliceras med vid vinst.
	int wonRows = 0;
	int bet;
	cout << "How much would you like to bet?" << endl;
	cin >> bet;
	if (bet > balance) {
		cout << "We could not verify your bet due to a lager 8 problem." << endl;
		bet = 0;
		return balance;
	}
	balance -= bet;
	
	//Looper igenom den tvådimensionella arrayen (spelfältet) och fyller den med X, Y eller Z beroende på vad som returneras ifrån funktionen "getRandomSlot".
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++){
			board[i][j] = getRandomSlot();
			cout << "|" << board[i][j] << "|";
		}
		cout << endl;
	}
	//får tillbaka antalet rader med vinst.
	wonRows = results(board);
	if (wonRows > 0) {
		cout << endl << "Congratz, you won on " << wonRows << " row(s)." << endl;
		cout << "Your profits are " << bet * multiplikationsTabellen[wonRows - 1] << "kr." << endl;
		balance += bet * multiplikationsTabellen[wonRows - 1]; //sätter in vinstpengar där användarens bet multiplicerats med värdet i arrayen ovan.
	}
	else
		cout << endl << "Sorry, you lost. Luckily we won at least! <3" << endl;
	return balance;
}

int main() {
	srand(time(0));
	int balance = 0;
	int choice;
	bool quit = false;

	cout << "Welcome to The Enarmad Bandit, someone wins every time. Either you or us. (TM)" << endl;
	cout << "1 row rewards 2x the bet" << endl;
	cout << "2 row rewards 3x the bet" << endl;
	cout << "3 row rewards 4x the bet" << endl;
	cout << "4 row rewards 5x the bet" << endl;
	cout << "5 row rewards 7x the bet" << endl;
	cout << "Full playing field rewards 10x the bet" << endl << endl;
	
	balance = deposit(balance); //sätter balance till värdet som returneras av funktionen balance.
	
	do {
		/*
		Då cin kan misslyckas med att tolka (parse) input ifall användaren anger annat än en integer
		som switch-caset förväntar sig hanteras detta genom att tömma cin cache samt ignorera bufferten som skapats.
		Detta för att undvika att switchen fastnar i en evig loop in i default.
		*/
		if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
		cout << endl << "Your current balance is: " << balance << "kr." << endl;
		cout << "Press 1 to play, 2 to deposit more money or 3 to quit the game." << endl;
		
		cin >> choice;

		//switch case som kör olika cases beroende på vad som finns i variabeln "choice". Alternativen är 1, 2 och 3. Om varken 1, 2 eller 3 finns i choice så körs default.
		switch (choice) {
		case 1: balance = runMachine(balance);
			break;
		case 2: balance = deposit(balance);
			break;
		case 3: cout << "Thank you for playing with us. Come back soon!";
			quit = true;
			break;
		default: cout << "Please choose by typing 1, 2 or 3.";
			break;
		}
	} while (!quit); //while som körs sålänge quit är false.
	return 0;
}
