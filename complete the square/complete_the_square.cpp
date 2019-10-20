#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <stdlib.h>
#include<math.h>
using namespace std;

#define GAME_ROUNDS 10
#define EASY 1
#define NORMAL 2
#define HARD 3
#define ONE_SEC 1000

int chooseDifficulty();
void generateNumbers(int a[], int b[], int c[],int difficulty);
void generateQuestions(int a[], int b[], int c[], int round);
int JudgeCorrectness(int a[], int b[], int c[],int round);
void initialGameStart();
int continueTheGame(int score);


int main() {
	int difficulty;
	int a[GAME_ROUNDS] = { 0 };
	int b[GAME_ROUNDS] = { 0 };
	int c[GAME_ROUNDS] = { 0 };
	int round;
	int score=0;

	

	initialGameStart();

	do{

		difficulty = chooseDifficulty();

		score = 0;

		for (round = 0; round < GAME_ROUNDS; round++) {
			generateNumbers(a, b, c, difficulty);
			generateQuestions(a, b, c, round);
			score += JudgeCorrectness(a, b, c, round);
		}

	} while (continueTheGame(score));

	system("pause");
	return 0;
}

int chooseDifficulty() {
	int choice;
	do {
		cout << "Please enter 1,2, or 3 to choose the difficulty" << endl;
		cout<< "1.EASY" << endl << "2.NORMAL" << endl << "3.HARD" << endl;
		cin >> choice;
	} while (choice != EASY && choice != NORMAL && choice != HARD);
	return choice;
}

void initialGameStart() {
	cout << "You will be given " << GAME_ROUNDS << " questions in the form of y=ax^2+bx+c." << endl;
	Sleep(2 * ONE_SEC);
	cout<< "For each question, you need to complete the square and give the answer for a,b, and c in the form of y=a(x-b)^2+c";
	cout << endl;
	Sleep(2 * ONE_SEC);
	cout << "Now you start!" << endl;
	cout << endl;
}

void generateNumbers(int a[], int b[], int c[], int difficulty) {
	srand(time(0));
	int i;
	if (difficulty == EASY) {
		for (i = 0; i < GAME_ROUNDS; i++) {
			a[i] = 1;
			 do{
				 b[i] = rand() % 20-10;
			 } while (b[i]==0||(i>=1&&b[i]==b[i-1]));

			 do {
				 c[i] = rand() % 20-10;
			 } while (i >= 1 && c[i] == c[i - 1]);
			
		}
	}

	if (difficulty == NORMAL) {
		for (i = 0; i < GAME_ROUNDS; i++) {
			do {
				a[i] = rand() % 3-2;
			} while (a[i]==0||(i >= 1 && a[i] == a[i - 1]));
			do {
				b[i] = rand() % 20 -10;
			} while (b[i]==0||(i >= 1 && b[i] == b[i - 1]));

			do {
				c[i] = rand() % 20-10;
			} while (i >= 1 && c[i] == c[i - 1]);

		}
	}

	if (difficulty == HARD) {
		for (i = 0; i < GAME_ROUNDS; i++) {
			do {
				a[i] = rand() % 3-2;
			} while (a[i]==0||(i >= 1 && a[i] == a[i - 1]));
			do {
				b[i] = rand() % 20 - 10;
			} while (b[i] == 0 || (i >= 1 && b[i] == b[i - 1]));

			do {
				c[i] = rand() % 100-50;
			} while (i >= 1 && c[i] == c[i - 1]);

		}
	}

}

void generateQuestions(int a[], int b[], int c[], int round) {
	cout << "Question" << round+1 << ":"<<endl<<"y=";

	if (a[round] == 1) {
		cout << "x^2";
	}
	else if (a[round] == -1) {
		cout << "-x^2";
	}
	else {
		cout << a[round] << "x^2";
	}

	if (b[round] == 1) {
		cout << "+x";
	}
	else if(b[round]>0){
		cout <<"+"<< b[round] << "x";
	}
	else if(b[round]==-1){
		cout << "-x";
	}
	else {
		cout << b[round] << "x";
	}

	if (c[round] > 0) {
		cout << "+" << c[round];
	}
	if (c[round] < 0) {
		cout << c[round];
	}

	cout << endl;
}

int JudgeCorrectness(int a[], int b[], int c[],int round) {
	int aAns;
	double bAns;
	double cAns;

	double A = (double)a[round];
	double B = (double)b[round];
	double C = (double)c[round];
	int CorrectA = a[round];
	double CorrectB = -1.0*B/(2.0*A);
	double CorrectC =(4.0*A*C-B*B)/(4.0*A) ;
	int correct=0;

	cout << "a=";
	cin >> aAns;
	
	cout << "b=";
	cin >> bAns;

	cout << "c=";
	cin >> cAns;

	if (aAns == CorrectA && bAns == CorrectB && cAns == CorrectC) {
		correct = 1;
		cout << "Correct!" << endl<<endl;
	}
	else {
		cout << "Wrong!" << endl;
		cout << "The correct answer is: \n";
		cout << "a=" << CorrectA << endl;

		if(a[round]>0&&b[round]>0){
			cout << "b=" << -b[round] << "/" << 2 * a[round] << endl;
		}
		else if (a[round] < 0 && b[round] < 0) {
			cout << "b=" << -abs(b[round]) << "/" << 2 * abs(a[round]) << endl;
		}
		else if(a[round]<0||b[round]<0){
			cout << "b=" << abs(b[round]) << "/" << 2 * abs(a[round]) << endl;
		}


		if(a[round]>0&&4 * a[round] * c[round] - b[round] * b[round]>0){
			cout << "c=" << 4 * a[round] * c[round] - b[round] * b[round] << "/" << 4 * a[round];
		}
		else if (a[round] < 0 && 4 * a[round] * c[round] - b[round] * b[round] < 0) {
			cout << "c=" << abs(4 * a[round] * c[round] - b[round] * b[round]) << "/" << abs(4 * a[round]);
		}
		else if (4 * a[round] * c[round] - b[round] * b[round] == 0) {
			cout << "c=0";
		}
		else if (a[round] < 0 || 4 * a[round] * c[round] - b[round] * b[round] < 0) {
			cout << "c=-" << abs(4 * a[round] * c[round] - b[round] * b[round]) << "/" << abs(4 * a[round]);
		}
		cout << endl << endl;
	}
	Sleep(3 * ONE_SEC);
	return correct;
}

int continueTheGame(int score) {

	cout << "The round is now over.\n";
	cout << "your score is " << score << "/" << GAME_ROUNDS<<endl;

	double percentage = (double)score / (double)GAME_ROUNDS;

	if ( percentage== 1) {
		cout << "Conguatulations!\n";
	}
	else if (percentage >= 0.8 && percentage < 1) {
		cout << "Good Work!\n";
	}
	else {
		cout << "You need more practice\n";
	}

	char response='a';
	do{
		cout << "Enter Y if you want to continue, or N to quit.\n";
		cin >> response;
	} while ((response != 'y' && response != 'Y') && (response != 'n' && response != 'N'));

	if (response == 'y' || response == 'Y') {
		return 1;
	}
	return 0;
}