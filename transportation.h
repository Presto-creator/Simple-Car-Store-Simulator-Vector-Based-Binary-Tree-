#pragma once
#ifndef Transportation_H
#define Transportation_H
#include <string>
#include <iostream>
#include <fstream>
#include "BTVectorBased.h"

using namespace std;

class Vehicle {
public:
	Vehicle();
	Vehicle(int, string, string, int, bool, int, VectorTree<string>);
	void reserve() { available = 0; }
	void unReserve() { available = 1; }
	
	int status() const { return available; }
	int getID() const { return vehicleID; }
	string getmake() const { return make; }
	string getmodel() const { return model; }
	int getSeats()const { return seats; }
	int getextarFeatures()const { return extarFeatures; }

	/*string* getFeaturesList() const {
		return otherFeaturesList;
	}*/

	//Return Customers Recursivley
	/*string getFeaturesList() {
		return otherFeaturesList;
	}*/

	//typename VectorTree<string>::Position beginIter() { return features.begin(); }
	//typename VectorTree<string>::Position endIter() { return features.end(); }
	//do I need an equivalent for this? How would I do this?
	typename VectorTree<string>::Position beginIter() {
		return featuresList.root();
	}
	typename VectorTree<string>::Position endIter() {
		return featuresList.last();
	}
	//there are my equivalents letsa go

	~Vehicle(); // destructor
	Vehicle(const Vehicle&);   //copy Constructor

	Vehicle operator=(const Vehicle& rhs);  // assignment overlaoding

	// operators overloading 
	bool operator>(const Vehicle&);
	bool operator<(const Vehicle&);
	bool operator==(const Vehicle&);
	bool operator<=(const Vehicle&);
	bool operator>=(const Vehicle&);
	bool operator!=(const Vehicle&);

	friend ostream& operator << (ostream& out,  Vehicle&);
	friend ofstream& operator << (ofstream& out,  Vehicle&);

private:
	int vehicleID; //an integer number automatically assigned when object is created.
	string make;
	string model;
	int seats; // number of seats
	bool available; //a Boolean variable that is initially has true indicating that the vehicle is available.
	int extarFeatures; // number of the extra features in the vehicle

	//typedef VectorTree<string> FeaturesList;
	typedef VectorTree<string> f_List;
	f_List featuresList;

};  // end of class Vehicle

//========================================================================

class Inventory {
public:
	Inventory();

	Inventory(VectorTree<Vehicle>);
	//rule of three
	Inventory(const Inventory&);  //C.C
	Inventory operator=(const Inventory&); // =.O.L
	~Inventory();

	bool push_Back(Vehicle);// push_back
	void sortList();
	void printList(VectorTree<Vehicle>::Position);
	void printResevedList(VectorTree<Vehicle>::Position);
	void printAvailableList(VectorTree<Vehicle>::Position);
	bool found(int, VectorTree<Vehicle>::Position);
	bool reserveVehicle(int);
	bool returnVehicle(int);
	typename VectorTree<Vehicle>::Position checkID(int, VectorTree<Vehicle>::Position);
	int size() { return registredVehiclesNo; }  // inline implementation
	bool saveToFile(string fileName);

	//ofstream & operator<<(ofstream &outfile)
	//	// overleaoding the insertion operator << for the output file stream
	//{
	//	for (int i = 0; i < registredVehiclesNo; i++) {
	//		outfile << v_List[i];
	//		outfile << "------------------------------------------\n";
	//	}
	//	return outfile;
	//}
	//ofstream & operator << (ofstream & oufile );

	friend ofstream& operator<<(ofstream&, Inventory&);
	//

	//v_List VectorTree Operators
	typename VectorTree<Vehicle>::Position beginIter() { return  v_List.root(); }
	typename VectorTree<Vehicle>::Position endIter() { return  v_List.last(); }

	ofstream& operator<<(Inventory& objV)
	{
		// TODO: insert return statement here
	}
private:

	
	int registredVehiclesNo;

	//Vehicle* v_List;   //dynamic array

	/*Project 6: Refactoring is needed here. You need to replace the dynamic array with a VectorTree object.
	  you must update all the affected methods in the entire project*/
	VectorTree<Vehicle> v_List;

};

#endif