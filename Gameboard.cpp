#include <iostream>
#include <cstdio>

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
	int i =3;
	while(i--){ //Rounds until winner is found
		std::cout<< "STARTING PHASE"<< std::endl;
		for(int i=0; i< players.size(); i++){
			if(players[i]->give_no_provinces()== 0)
				continue;
			players[i]->startingPhase();
		}

		std::cout<< "EQUIPMENT PHASE"<< std::endl;
		for(int i=0; i< players.size(); i++){
			if(players[i]->give_no_provinces()== 0)
				continue;
			players[i]->equipPhase();
		}
/*
		std::cout<< "BATTLE PHASE"<< std::endl;
		for(int i=0; i< players.size(); i++){
			if(players[i]->give_no_provinces()== 0)
				continue;
			players[i]->battlePhase();
		}
*/
		std::cout<< "ECONOMY PHASE"<< std::endl;
		for(int i=0; i< players.size(); i++){
			if(players[i]->give_no_provinces()== 0)
				continue;
			players[i]->economyPhase();
		}

		std::cout<< "FINAL PHASE"<< std::endl;
		for(int i=0; i< players.size(); i++){
			if(players[i]->give_no_provinces()== 0)
				continue;
			players[i]->endingPhase();
		}
		/*
		winner= checkWinningCondition();
		if(winner>= 0){
			cout<< "PLAYER "<< players[winner]->name << " IS THE WINNER!"<< endl;
			break;
		}*/
	}
}

/*void GameBoard::gameplay(){
	int winner= -1;

	while(1){ //Rounds until winner is found
		cout<< "STARTING PHASE"<< endl;

		for(int i=0; i< players.size(); i++){
			if(players[i]->give_no_provinces()== 0)
				continue;
			cout<< "PLAYER'S #"<< i<< " TURN"<< endl;
			players[i]->startingPhase();
		}

		cout<< "EQUIPMENT PHASE"<< endl;
		for(int i=0; i< players.size(); i++){
			if(players[i]->give_no_provinces()== 0)
				continue;
			cout<< "PLAYER'S #"<< i<< " TURN"<< endl;
			players[i]->equipPhase();
		}

		cout<< "BATTLE PHASE"<< endl;
		for(int i=0; i< players.size(); i++){
			if(players[i]->give_no_provinces()== 0)
				continue;

			cout<< "PLAYER'S #"<< i<< " TURN"<< endl;
				cout<< "Defense or Battle? [Type D/B]: ";
			int c= getchar();
			while(c!= 'D' || c!= "B"){
				cout<< "\nWrong character! Please type D or B: ";
				c= getchar();
			}
			putchar(c);
			if(c== 'D')
				players[i]->battlePhase(NULL);
			else{
				cout<< "\nWhich Player do you want to battle?"<< endl<<
					"Number of Players in the game: "<< players.size()<< endl<<
					"Type a number: (1- "<< players.size()<< "): ";
					c= getchar();
				while(c>= players.size() && c<= 1){
					cout<< "\nWrong number! Please type a number from 0 to "<< players.size()-1<< ":";
					c= getchar();
				}
				putchar(c);
				players[i]->battlePhase(&players[c-1]);
			}

		}

		cout<< "ECONOMY PHASE"<< endl;
		for(int i=0; i< players.size(); i++){
			if(players[i]->give_no_provinces()== 0)
				continue;
			cout<< "PLAYER'S #"<< i<< " TURN"<< endl;
			players[i]->economyPhase();
		}

		cout<< "FINAL PHASE"<< endl;
		for(int i=0; i< players.size(); i++){
				if(players[i]->give_no_provinces()== 0)
				continue;
			cout<< "PLAYER'S #"<< i<< " TURN"<< endl;
			players[i]->finalPhase();
		}
			winner= checkWinningCondition();
			if(winner> 0){
		cout<< "PLAYER "<< players[winner]->name<< " IS THE WINNER!"<< endl;
			break;
		}
	}
} */
