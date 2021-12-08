#include <string>
#include <iostream>
#include <fstream>
#include "transportation.h"
#include "BTVectorBased.h"
using namespace std;

/****************************Class Vehicle Method Implementations***************************************/
Vehicle::Vehicle() {
	/*default constructor
	//fields are initialized with default data.
	//for the vehicle object, an empty dynamic array is allocated.
	*/
	vehicleID = -1;
	make = "NA";
	model = "NA";
	seats = 0;
	available = true;
	extarFeatures = 0;
	//Refactor Below
	//features();
};

Vehicle::Vehicle(int _vehicleID_, string _make_, string _model_, int _seats_,
	bool _available_, int _extraFeatures_, VectorTree<string> _otherFeaturesList_) {
	/*overloaded constructor
	//fields are initialized with data sent via the constructor.
	//the array of features is sent fro outsite as a pointer.
	*/
	vehicleID = _vehicleID_;
	make = _make_;
	model = _model_;
	seats = _seats_;
	available = _available_;
	extarFeatures = _extraFeatures_;
	//Refactor Below
	featuresList = _otherFeaturesList_;
};

//-------------
// if (v1>v2) 
bool Vehicle::operator> (const Vehicle& v) {
	/*
	// overloading the greater than operator >. number of seats is used for
	//comparing the vehcle. If equal, then the number of extra features is used to break the ties.
	*/
	return ((seats > v.seats) || ((seats == v.seats) && (extarFeatures > v.extarFeatures)));
}

bool Vehicle::operator< (const Vehicle& v) { // used seats then extrafeatures as keys
		/*
	// overloading the less than operator <. number of seats is used for
	//comparing the vehcle. If equal, then the number of extra features is used to break the ties.
	*/
	return ((seats < v.seats) || ((seats == v.seats) && (extarFeatures < v.extarFeatures)));
}


bool Vehicle::operator==(const Vehicle& v) // uses seats then extrafeatures as keys to compare between Vehicle objects
{
	/*
// overloading the equality operator ==. Number of seats and extra features are used
//for determining if two vehicles are equal.
*/
	return (this->seats == v.seats && this->extarFeatures == v.extarFeatures);
}

bool Vehicle::operator<=(const Vehicle& v) // seats is the key
{
	/* overloading operator <= */
	return ((this->seats == v.seats && this->extarFeatures == v.extarFeatures) || ((seats < v.seats) || ((seats == v.seats) && (extarFeatures < v.extarFeatures))));
}
bool Vehicle::operator>=(const Vehicle& v) // seats is the key
{	/* overloading operator >= */
	return ((this->seats == v.seats && this->extarFeatures == v.extarFeatures) || ((seats > v.seats) || ((seats == v.seats) && (extarFeatures > v.extarFeatures))));

}

bool Vehicle::operator!=(const Vehicle& v) // seats is the key
{
	/* overloading the  operator != not equal*/
	return (!((this->seats == v.seats) && (this->extarFeatures == v.extarFeatures)));
}

//Rule of Three:
//destructor
Vehicle::~Vehicle() {};

// copy constructor	
Vehicle::Vehicle(const Vehicle& org) {
	vehicleID = org.vehicleID;
	make = org.make;
	model = org.model;
	seats = org.seats;
	available = org.available;
	extarFeatures = org.extarFeatures;
	//Refactored
	if (extarFeatures > 0) {
		featuresList = org.featuresList;
	}
}

//assignment operator overloading
Vehicle Vehicle::operator=(const Vehicle& rhs) {
	if (this != &rhs)
	{
		//delete[] otherFeaturesList;
		vehicleID = rhs.vehicleID;
		make = rhs.make;
		model = rhs.model;
		seats = rhs.seats;
		available = rhs.available;
		extarFeatures = rhs.extarFeatures;
		//Refactored
		if (extarFeatures > 0) {
			featuresList = rhs.featuresList;
		}
	}
	return *this;
}

/******** Friend Functions to the Vehicle***********/
ostream& operator<<(ostream& out, Vehicle& objV)
// overleaoding the insertion operator <<
{
	out << "------------------------------------------\n";
	out << "ID: " << objV.vehicleID << endl;
	out << "Make: " << objV.make << endl;
	out << "Model: " << objV.model << endl;
	out << "Vumber of seats: " << objV.seats << endl;
	if (objV.available)
		out << "Availability: available" << endl;
	else
		out << "Availability: Not available" << endl;
	out << "Extra Features[" << objV.extarFeatures << "]: " << endl;
	if (objV.extarFeatures < 1)
		out << "Basic trim" << endl;
	else {
		//Refactor Below
		out << "[";
		//VectorTree<string>::Iterator i = objV.features.begin();
		//out << *i;
		//for (++i; i != objV.features.end(); ++i) {
		//	out << ", " << *i;
		//
		//}
		//How the hell do I implement this? How can I make a position ADT into an iterator
		//VectorTree<int>::Position i = objV.features.size();
		
		for (VectorTree<string>::Position p1 = objV.featuresList.root(); p1 <= objV.featuresList.last(); ++p1)
		{

			out << (*p1);
			if (p1 != objV.featuresList.last()) {
				out << ", ";
			}
		}
		
		

		out << "]" << endl;

	}
	return out;
}
ofstream& operator<<(ofstream& out, Vehicle& objV)
// overleaoding the insertion operator << for the output file stream
{
	out << objV.vehicleID << endl;
	out << objV.make << endl;
	out << objV.model << endl;
	out << objV.seats << endl;
	out << objV.available << endl;
	out << objV.extarFeatures << endl;
	//Refactor Below
	//for (int i = 0; i < objV.extraFeatures; ++i)
	//out << objV.features << endl;
	/*for (VectorTree<string>::Iterator i = objV.features.begin(); i != objV.features.end(); ++i) {
		out << *i << endl;
	}*/
	
	for (VectorTree<string>::Position p1 = objV.featuresList.root(); p1 <= objV.featuresList.last(); ++p1)
	{
		out << (*p1) << endl;
	}

	return out;
}



/****************************Class Inventory Method Implementations***************************************/
//default constructor
Inventory::Inventory() {
	registredVehiclesNo = 0;

	//capacity = 100; //default size
	//v_List = new Vehicle[capacity];
}

//constructor II
Inventory::Inventory(VectorTree<Vehicle> currentList) {
	v_List = currentList;
	registredVehiclesNo = currentList.size();
}

Inventory::~Inventory() {} //destructor

//copy constructor
Inventory::Inventory(const Inventory& obj) {
	
	registredVehiclesNo = obj.registredVehiclesNo;
	v_List = obj.v_List;
}

//assignment overloading.
Inventory Inventory::operator=(const Inventory& rhs) {
	if (this != &rhs) {
		
		registredVehiclesNo = rhs.registredVehiclesNo;

		v_List = rhs.v_List;
	}
	return *this;
}

bool Inventory::push_Back(Vehicle  ve) {
	/*inserting vehilce object to the inventory list*/
	/*Project 6: improve it by extending the underlining list, expands as needed.*/
	/*Project 6: make sure that it is consistent with the new data structure (VectorTree) you used for this class.*/
	v_List.addLast(ve);
	registredVehiclesNo++;
	
	return true;
}

void Inventory::sortList() {
	for (VectorTree<Vehicle>::Position curr = v_List.root(); curr != v_List.last(); ++curr)
		for (VectorTree<Vehicle>::Position currentV = curr; currentV != v_List.last(); ++currentV)
			if (*currentV > *curr) {
				Vehicle strTmpTask = *currentV;
				*currentV = *curr;
				*curr = strTmpTask;
			}
	
}

void Inventory::printList(VectorTree<Vehicle>::Position i) {
	/*Project 6: Refactoring is needed here. You need to reimplement this method in a recursive way.*/
	/*so the method will traverse the list reursively to print out the vehicle info for all the list*/
	if (i <= v_List.last()) {
		cout << (*i);
		cout << "------------------------------------------\n";
		printList(++i);
	}
}
void Inventory::printResevedList(VectorTree<Vehicle>::Position i) {  // print list of the reserved vehicles
	/*Project 6: Refactoring is needed here. You need to reimplement this method in recursive way.*/
	if (i <= v_List.last()) {
		if (!(*i).status()) cout << *i;
		printResevedList(++i);
	}
}
void Inventory::printAvailableList(VectorTree<Vehicle>::Position i) {// print list of the available vehicles
	/*Project 6: Refactoring is needed here. You need to reimplement this method in recursive way.*/
	if (i <= v_List.last()) {
		if ((*i).status()) cout << *i;
		printAvailableList(++i);
	}
}
bool Inventory::found(int seatsNo, VectorTree<Vehicle>::Position i) {// print list of the available vehicles that has AT LEAST seatsNo seats.
	//Pre-conditions: seatsNo is a positive value > 0
	/*Project 6: Refactoring is needed here. You need to reimplement this method in recursive way.*/
	bool Yes = false;
	if (i <= v_List.last()) {
		if ((*i).getSeats() >= seatsNo) { cout << (*i); Yes = true; }
		found(seatsNo, ++i);
	}

	return Yes;
}

bool Inventory::reserveVehicle(int _vehicleID_) {
	
	typename VectorTree<Vehicle>::Position tmpVehicleIDItr = checkID(_vehicleID_, v_List.root());
	if ((tmpVehicleIDItr <= v_List.last()) && ((*tmpVehicleIDItr).status())) {  //found and available			
		(*tmpVehicleIDItr).reserve();
		cout << "Reserved" << endl;
		return true;
	}
	return false;
	//beginIter() { return features.begin(); }
}
bool Inventory::returnVehicle(int _vehicleID_) {

	typename VectorTree<Vehicle>::Position tmpVehicleIDItr = checkID(_vehicleID_, v_List.root());
	if ((tmpVehicleIDItr <= v_List.last()) && (!(*tmpVehicleIDItr).status())) {  //found and reserved available			
		//cout << (*tmpVehicleIDItr).status() << " The begin" << endl;
		(*tmpVehicleIDItr).unReserve();
		//cout << (*tmpVehicleIDItr).status() << " The end" << endl;
		return true;
		cout << "Returned!" << endl;
	}
	return false;
	cout << "COULD NOT RETURN" << endl;
}
typename VectorTree<Vehicle>::Position Inventory::checkID(int _vehicleID_, VectorTree<Vehicle>::Position i) {
	/*Project 6: Refactoring is needed here. You need to reimplement this method in recursive way.*/

	//non-recursive
	/*for (int i = 0; i < registredVehiclesNo; ++i)
		if (v_List[i].getID() == _vehicleID_)
			return i;
	return -1;*/

	if (i <= v_List.last()) {
		if ((*i).getID() == _vehicleID_) {
			return i;
		}
		return checkID(_vehicleID_, ++i);
	}
	return(v_List.last());
}

bool Inventory::saveToFile(string fileName) {
	/*this method prints the list data in a text file (received as a parameter) */
	//pre-conditions: fileName is a valid file name.  something.txt
	ofstream outFile;
	outFile.open(fileName);
	if (outFile.fail()) return false;
	outFile << size() << endl;

	//for (int i = 0; i < size(); ++i) { // updating the database
	//	outFile << v_List[i];
	//}

	for (VectorTree<Vehicle>::Position i = v_List.root(); i <= v_List.last(); ++i) 
	{
		outFile << *i; 
	}
	outFile.close();
	return true;

}

/************** Freind functions to class Inventory ******************/

ofstream& operator<<(ofstream& outfile, Inventory& objV)
// overleaoding the insertion operator << for the output file stream
{
	outfile << objV.size() << endl;
	for (VectorTree<Vehicle>::Position i = objV.v_List.root(); i != objV.v_List.last(); ++i)
	{
		outfile << *i;
	}

	return outfile;
}


