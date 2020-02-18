#include <iostream>

#include "GameBoard.hpp"

GameBoard::~GameBoard(){
	for(int i=0; i< players.size(); i++)
		delete players[i];
}

void GameBoard::initializeGameBoard(int no_players){
	std::string name;
	for(int i=0; i< no_players; i++){
		std::cout << "Give player's name: " << std::endl;
		std::cin >> name;
		players.push_back(new Player(name));
	}

		printGameStatistics();
}

void GameBoard::printGameStatistics(){
	std::cout << "\nPrinting Statistics: " << std::endl << std::endl;
	for(int i=0; i< players.size(); i++){
		std::cout<< "PLAYER "<< players[i]->name << " is #"<< i<< std::endl;
		players[i]->printGameStatistics();
		std::cout<< std::endl;
	}
}

int GameBoard::checkWinningCondition(){
	int flag= 0, winner= 0;
	for(int i=0; i< players.size(); i++){
		if(players[i]->give_no_provinces()== 0)
			continue;
		else{
			flag++;
			winner= i;
		}
	}
	if(flag== 1) return winner;
	else return -1;
}

void GameBoard::gameplay(){
	int winner= -1;

	while(1){ //Rounds until winner is foun
		cout<< "\033[1;35mSTARTING PHASE\033[0m"<< endl;

		for(int i=0; i< players.size(); i++){
			if(players[i]->give_no_provinces()== 0)
				continue;
			players[i]->startingPhase();
		}

		cout<< "\033[1;35mEQUIPMENT PHASE\033[0m"<< endl;
		for(int i=0; i< players.size(); i++){
			if(players[i]->give_no_provinces()== 0)
				continue;
			players[i]->equipPhase();
		}

		cout<< "\033[1;35mBATTLE PHASE\033[0m"<< endl;
		for(int i=0; i< players.size(); i++){
			if(players[i]->give_no_provinces()== 0)
				continue;

				cout << "Player: " << players[i]->name << " is playing " << endl;
				cout << "Battle Phase ..." << endl << endl;
				if (!players[i]->hasArmy()){
					cout << "No army found, phase is skipped :(" << endl << endl;
					continue;
				}

			char c;
			cout<< "Defense or Battle? [Type D/B]: ";
			cin>> c;

			if(c== 'D')
				players[i]->battlePhase(NULL);
			else{
				cout<< "\nWhich Player do you want to battle?"<< endl<< "Suggested list:"<< endl;
				for(int j=0; j< players.size(); j++){
					if(i!= j)
						cout<< j+1<< ") "<< players[j]->name<< endl;
				}
				cout<< "Type a number from suggested list: ";
				int n;
				while(n< 1 || n> players.size()){
					cin>> n;
					cout<< endl;
				}
				players[i]->battlePhase(players[n-1]);
			}
		}

		cout<< "\033[1;35mECONOMY PHASE\033[0m"<< endl;
		for(int i=0; i< players.size(); i++){
			if(players[i]->give_no_provinces()== 0)
				continue;
			players[i]->economyPhase();
		}

		cout<< "\033[1;35mFINAL PHASE\033[0m"<< endl;
		for(int i=0; i< players.size(); i++){
				if(players[i]->give_no_provinces()== 0)
				continue;
			players[i]->endingPhase();
		}
			winner= checkWinningCondition();
			if(winner> 0){
		cout<< "PLAYER "<< players[winner]->name<< " IS THE WINNER!"<< endl;
			break;
		}
	}
}
