/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Floor.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */


#include "Floor.h"

using namespace std;

int Floor::tick(int currentTime) {
    //TODO: Implement tick
	int toRemove[MAX_PEOPLE_PER_FLOOR] = {0};
	int numberToRemove = 0;
	for (int i = 0; i < numPeople; i++) {
		if (people[i].tick(currentTime)) {
			toRemove[numberToRemove] = i;
			numberToRemove++;
		}
	}
    //returning 0 to prevent compilation error
    return 0;
}

void Floor::addPerson(Person newPerson, int request) {
    //TODO: Implement addPerson
	if (numPeople < MAX_PEOPLE_PER_FLOOR) {
		people[numPeople] = newPerson;
		if (request > 0) {
			hasUpRequest = true;
		}
		else if (request < 0) {
			hasDownRequest = true;
		}
		numPeople++;
	}
}

void Floor::removePeople(int indicesToRemove[MAX_PEOPLE_PER_FLOOR], int numPeopleToRemove) {
    //TODO: Implement removePeople
	for (int i = 0; i < numPeople; i++) {
		for (int j = 0; j < numPeopleToRemove; j++) {
			if (i == indicesToRemove[j]) {
				for (int k = i; k < numPeople - 1; k++) {
					people[k] = people[k + 1];
				}
				people[numPeople - 1] = Person();
				numPeople--;
				resetRequests();
			}
		}
	}
}

void Floor::resetRequests() {
    //TODO: Implement resetRequests
	bool upRequestFound = false;
	bool downRequestFound = false;
	for (int i = 0; i < numPeople; i++) {
		if (people[i].getCurrentFloor() < people[i].getTargetFloor()) {
			upRequestFound = true;
		}
		else if (people[i].getCurrentFloor() > people[i].getTargetFloor()) {
			downRequestFound = true;
		}
	}
	if (upRequestFound) {
		hasUpRequest = true;
	} else {
		hasUpRequest = false;
	}
	if (downRequestFound) {
		hasDownRequest = true;
	} else {
		hasDownRequest = false;
	}	
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Floor::Floor() {
    hasDownRequest = false;
    hasUpRequest = false;
    numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
	string up = "U";
	outs << (hasUpRequest ? up : " ") << " ";
	for (int i = 0; i < numPeople; ++i){
		outs << people[i].getAngerLevel();
		outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
	}
	outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream& outs) const {
	string down = "D";
	outs << (hasDownRequest ? down : " ") << " ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "o   ";
	}
	outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
	cout << endl;
	outs << "Select People to Load by Index" << endl;
	outs << "All people must be going in same direction!";
	/*  O   O
	// -|- -|-
	//  |   |
	// / \ / \  */
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " O   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "-|-  ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " |   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "/ \\  ";
	}
	outs << endl << "INDEX:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << i << "   ";
	}
	outs << endl << "ANGER:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getAngerLevel() << "   ";
	}
	outs << endl << "TARGET FLOOR: ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getTargetFloor() << "   ";
	}
}

void Floor::setHasUpRequest(bool hasRequest) {
    hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
	return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
    hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
	return hasDownRequest;
}

int Floor::getNumPeople() const {
    return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
    return people[index];
}
