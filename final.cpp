// GOOD ONE OF THE VERSIONS

#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <vector>
#include <random>

using namespace std;

/*
 * Replace the values inside the vector "actions" with the one of your solution.
 * The index of the vector increases from the bottom left to top right.
 * The value of the vector indicates the action to perform at the corresponding state.
 * You can show on screen your solution running the python script "show.py" in the build folder.
 */





////////////////////////////////////////////////////////////////////////////////
// functions prototypes
////////////////////////////////////////////////////////////////////////////////

// to store position information of an agent
struct agentStructure;
struct agentStructure {
	// grid world size
    int worldRowLength=0, worldColumnLength=0;
    // row and column numbers
    int rowPos=0, columnPos=0;
    // next values depend on the action
	int rowNext=0, columnNext=0, rowRight=0, columnRight=0, rowLeft=0, columnLeft=0;
	// direction of action
	int action=0;
};

int rndInt(int aa);

int indexOfMaxValue( double *ValPntr, int N);

double maxValue( double *part);

agentStructure executeAction(agentStructure agent);

int epsilonGreedy(double *ValPntr, double epsilon);

bool isItTermial(int terminals[][2], int terminalsNumber, int rowPos, int columnPos);



////////////////////////////////////////////////////////////////////////////////
// main function to solve grid world problem
////////////////////////////////////////////////////////////////////////////////
int main(){

	// **************************************************
	// parameters and variables
	// **************************************************

	agentStructure agent;		// Create an agent
	agent.worldRowLength=3;		// size of grid world
	agent.worldColumnLength=5;	// size of grid world

	// target and forbidden points in grid world
	int terminals[5][2]={{2, 2}, {3, 0}, {1 ,1}, {2, 3}, {2, 4}};
	int terminalsNumber=sizeof(terminals)/sizeof(terminals[0][0])/2;

	// agent uncertainties
	double Pleft=0.1;
	double Pright=0.1;
	double Pforward=1-Pleft-Pright;

	// learning parameters
	double gama=0.5;				// 0.5
	double alpha=0.2;				// 0.2 - 0.9
	double iteration=10000; 			// 30000
	double epsilon=0.2;				// 0.2
	double epsilonMin=0.0;			// 0.0
	double epsilonDelta=(epsilon-epsilonMin)/(iteration);
	double movementReward=-0.0004;	// -0.004
	double alphaDelta=0; 			//	0 - alphaDelta/iteration;

	// others
	double part1[4], part2[4], part3[4], gammaV;	// used to calculate fncV
	double gammaV1, gammaV2, gammaV3;
	int i=0, j=0, k=0;		// loop indexes

	// init utility matrix
	// 0=up 1=right 2=down 3=left
	double fncV[agent.worldRowLength+1][agent.worldColumnLength+1][4]={};

	// init rewards matrix
	double rewards[agent.worldRowLength+1][agent.worldColumnLength+1];
	for(i=0;i<=agent.worldRowLength;i++){
		for(j=0;j<=agent.worldColumnLength;j++){
			rewards[i][j]=movementReward;
		}
	}
	rewards[2][2]={1};  	// target
	rewards[3][0]={-1};		// forbidden
	rewards[1][1]={-1};
	rewards[2][3]={-1};
	rewards[2][4]={-1};

	// not used, can be deleted
	// Ns, to counts all times state has been visited
	double stateVisitNumber[agent.worldRowLength+1][agent.worldColumnLength+1]={};
	int trap=0;		// delete



	// **************************************************
	// main loop
	// **************************************************

	while (i<iteration){



		// select a random and valid starting point
		while (1){

			// starting position of the agent
			// agent.rowPos=rand() %4;
			// agent.columnPos=rand() %6;
			agent.rowPos=rndInt(3);
			agent.columnPos=rndInt(5);


			// check if starting point is one of terminal points
			if (~isItTermial(terminals, terminalsNumber, agent.rowPos, agent.columnPos)){
				break;
			}
		}


		// episode loop
		j=0;	// to control episode loop

		while (1){

			// next position - (up-downd-right-left) - Epsilon-greedy action selection
			agent.action=epsilonGreedy(&fncV[agent.rowPos][agent.columnPos][0], epsilon);

			// update next positions of agent depending on the action
			agent=executeAction(agent);

			// calculate how many times the state visited by the agent
			stateVisitNumber[agent.rowPos][agent.columnPos]=stateVisitNumber[agent.rowPos][agent.columnPos]+1;



			///////////////////////////////////////////////////
			// evaluate the function
			// TDL =>	Vs <-- Vs + alpha[R + gamaV(s+1)-Vs]
			//
			// gamaV(s+1) + R for possible states
			gammaV1=gama*maxValue(&fncV[agent.rowNext][agent.columnNext][0])+rewards[agent.rowNext][agent.columnNext];
			gammaV2=gama*maxValue(&fncV[agent.rowLeft][agent.columnLeft][0])+rewards[agent.rowLeft][agent.columnLeft];
			gammaV3=gama*maxValue(&fncV[agent.rowRight][agent.columnRight][0])+rewards[agent.rowRight][agent.columnRight];


			// based on probability
			gammaV = Pforward*gammaV1 + Pleft*gammaV2 + Pright*gammaV3;

			// fncV[agent.rowPos][agent.columnPos][agent.action] = fncV[agent.rowPos][agent.columnPos][agent.action] + alpha* ( gammaV-fncV[agent.rowPos][agent.columnPos][agent.action] ) ;
			fncV[agent.rowPos][agent.columnPos][agent.action] += alpha* ( gammaV-fncV[agent.rowPos][agent.columnPos][agent.action] ) ;

			// end of function evaluation
			///////////////////////////////////////////////////


	        // check if the next position is one of the terminal points
			// or if the end of episode
			// if (isItTermial(terminals, terminalsNumber, agent.rowNext, agent.columnNext) || j>episode_iteration){
			if (isItTermial(terminals, terminalsNumber, agent.rowNext, agent.columnNext)){

				epsilon -= epsilonDelta;	// decaying
				alpha -= alphaDelta;		// decaying

				break;
				
			} else {

				// update positions if the episode is continuing
				agent.rowPos=agent.rowNext;
				agent.columnPos=agent.columnNext;

				// increase episode number
				j++;

			}


		}	// end of episode

		i++;	// next iteration


	}	// end of main loop


	// **************************************************
	// create map vector
	// **************************************************
	vector<string> actions;
	//  select directions based on the biggest values
	for (j=0;j<=agent.worldRowLength;j++){
		for (i=0;i<=agent.worldColumnLength;i++){

			// find the index of best value
			switch (indexOfMaxValue(&fncV[j][i][0],4)){

				case 0:
					actions.push_back("up");
					break;

				case 1:
					actions.push_back("right");
					break;

				case 2:
					actions.push_back("down");
					break;

				case 3:
					actions.push_back("left");
			}

		}

	}	// end of create map vector



    // DO NOT CHANGE THE FOLLOWING CODE

    std::ofstream output_file("./actions.txt");
    std::ostream_iterator<std::string> output_iterator(output_file, "\n");
    std::copy(actions.begin(), actions.end(), output_iterator);
    cout << "Result wrote on file actions.txt" << endl;



    return 0;

}	// end of int main()


////////////////////////////////////////////////////////////////////////////////
// function/structure declarations
////////////////////////////////////////////////////////////////////////////////

// generate uniform random numbers
int rndInt(int aa){

	// Init of uniform_int_distribution class
	random_device rd;
	default_random_engine rndInt(rd());
	uniform_int_distribution<int> rnd01(0, aa);

	return rnd01(rndInt);

}	// end of rndInt


// check terminal points
bool isItTermial(int terminals[][2], int terminalsNumber, int rowPos, int columnPos ){

	int i, k;
	bool terminal=0;

	for (k=0;k<terminalsNumber;k++){
		if ( rowPos==terminals[k][0] && columnPos==terminals[k][0] ){
			terminal=1;
		}
	}

	return terminal;

}	// end of isItTerminal


// epsilon-greedy
int epsilonGreedy(double *ValPntr, double epsilon){

	int action;

	// Epsilon-greedy action selection (up-downd-right-left)
	//if ( ((double)rand()/RAND_MAX)>epsilon ){
	if ( rndInt(1000)/1000.0>epsilon ){
		// depends on the max value
		action=indexOfMaxValue(ValPntr, 4);
	}
	else {
		// random action selection 0-3
		// action=rand() %3;
		action=rndInt(3);
	}

	return action;

}	// end of epsilonGreedy


// to find the index of max value in the array
int indexOfMaxValue( double *ValPntr, int N){

	int i=0;
	int index=0;
	double max=*ValPntr;

	while (i<N){
		if( max<*(ValPntr+i) ){
			max=*(ValPntr+i);
			index=i;
		}
		i++;
	}

	return index;

}	// end of indexOfMaxValue


// to find the max value in the given part of the array
double maxValue( double *part ){

	int i=1;
	int index=0;
	int N=4;
	double max=*part;

	while (i<N){
		if( max<*(part+i) ){
			max=*(part+i);
			index=i;
		}
		i++;
	}

	return max;

}	// end of indexOfMaxValue


// new position calculations after an action in the grid world
agentStructure executeAction(agentStructure agent){

	int trap=0;

	// 0=up, 1=right, 2=down, 3=left

	switch (agent.action){

		case 0:	// to go forward
			if (agent.rowPos<agent.worldRowLength){
			 agent.rowNext=agent.rowPos+1;
			} else {
			 agent.rowNext=agent.rowPos;
			}
			agent.columnNext=agent.columnPos;

			// right of this position
			if (agent.columnPos<agent.worldColumnLength) {
				agent.columnRight=agent.columnPos+1;
			} else {
				agent.columnRight=agent.columnPos;
			}

			// left of this position
			if (agent.columnPos>0) {
				agent.columnLeft=agent.columnPos-1;
			} else {
				agent.columnLeft=agent.columnPos;
			}

			agent.rowLeft=agent.rowPos;
			agent.rowRight=agent.rowPos;
			break;

		case 1:	// to go right

			if (agent.columnPos<agent.worldColumnLength){
				agent.columnNext=agent.columnPos+1;
			} else {
				agent.columnNext=agent.columnPos;
			}
			agent.rowNext=agent.rowPos;
			break;

			// right of this position
			if (agent.rowPos>0) {
				agent.rowRight=agent.rowPos-1;
			} else {
				agent.rowRight=agent.rowPos;
			}

			// left of this position
			if (agent.rowPos<agent.worldRowLength) {
				agent.rowLeft=agent.rowPos+1;
			} else {
					agent.rowLeft=agent.rowPos;
			}

			agent.columnLeft=agent.columnPos;
			agent.columnRight=agent.columnPos;
			break;

		case 2: // to go down

			if (agent.rowPos>0){
				agent.rowNext=agent.rowPos-1;
			} else {
				agent.rowNext=agent.rowPos;
			}
			agent.columnNext=agent.columnPos;

			// right of this position
			if (agent.columnPos>0){
				agent.columnRight=agent.columnPos-1;
			} else {
				agent.columnRight=agent.columnPos;
			}

			// left of this position
			if (agent.columnPos<agent.worldColumnLength) {
				agent.columnLeft=agent.columnPos+1;
			} else {
				agent.columnLeft=agent.columnPos;
			}

			agent.rowLeft=agent.rowPos;
			agent.rowRight=agent.rowPos;
			break;

		case 3:	// to go left

			if (agent.columnPos>0){
			 agent.columnNext=agent.columnPos-1;
			} else {
			 agent.columnNext=agent.columnPos;
			}
			agent.rowNext=agent.rowPos;

			// right of this position
			if (agent.rowPos<agent.worldRowLength) {
				agent.rowRight=agent.rowPos+1;
			} else {
				agent.rowRight=agent.rowPos;
			}

			// left of this position
			if (agent.rowPos>0) {
				agent.rowLeft=agent.rowPos-1;
			} else {
				agent.rowLeft=agent.rowPos;
			}

			agent.columnLeft=agent.columnPos;
			agent.columnRight=agent.columnPos;
	}

	return agent;

}	// end of executeAction




////////////////////////////////////////////////////////////////////////////////
// end of function declarations	
////////////////////////////////////////////////////////////////////////////////

