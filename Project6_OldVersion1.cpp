#include "transportation.h"
#include "testers.h"
#include "BTVectorBased.h"
#include <string>
#include <iostream>
#include <fstream>

/*
Testing file and original Vector Based Binary Tree by Dr. Anaeli, UW-Stout
Binary Tree implemented and debugged by Preston Leigh, UW-Stout
*/
using namespace std;
string menu() {
	string message;
	message = "0. Clear Screen..\n1. Print All of the registered  vehicles.\n2. Print list of the available vehicles.";
	message = message + "\n3.List of the reserved vehicles.\n4. Check availability.\n5.Reserve a vehicle.\n6. return a vehicle.\n7. Print All of the registered vehicles to a text file.\n8. Exit.\nYour Selection --> ";
	return message;
}
bool readingDataFromDBfile(Inventory& myInventory, ifstream& inFile, int recordsInFile);

int main() {
	ifstream inFile;
	ofstream outFile;

	try {
		inFile.open("vehicles.txt"); if (inFile.fail()) { throw string("Failed opening the file! Fix it."); }
	} // exception for file not found/cannot open file
	catch (string e) { cout << "Exception: " << e << endl; exit(17); }
	catch (...) { cout << "Unknown error opening file, exiting code 10." << endl; exit(10); } // end try catch


	int recordsInFile;
	inFile >> recordsInFile; // reading number of the records in the file.
	//inFile.ignore(1000, '\n');  // ignore the \n

	Inventory myInventory;
	//NodeList<Vehicle> v_List;
	if (!readingDataFromDBfile(myInventory, inFile, recordsInFile)) {
		cout << "Could not read data from the database, exiting error 1" << endl;
		exit(1); //terminate// exceptions
	}
	cout << endl;
	//myInventory.sortList();
	//myInventory.printList(myInventory.beginIter()); //testing

	//cout << endl;
	//cout << menu();

	int userEntry = 0;
	bool done;
	int seatsNo = 0;

	
	//system("cls") is used for clearing the console screen. cls is a Dos command
	while (userEntry != 8) {
		cout << "**********************************\n";
		cout << menu();

		do {
			try { done = false; if (!(cin >> userEntry)) throw 12; done = true; } // input checking first time
			catch (int e) { if (e == 12) { userEntry = 0; cin.clear();  cin.ignore(1000, '\n'); cout << "Incorrect input! Please input a valid option." << endl; } } // end try catch
		} while (!done); // end do while


		switch (userEntry) {
		case 0: 
			system("cls");
			break;
		case 1: 
			system("cls");  
			myInventory.printList(myInventory.beginIter());
			break;
		case 2:
			system("cls"); 
			myInventory.printAvailableList(myInventory.beginIter());
			break;
		case 3:
			system("cls"); myInventory.printResevedList(myInventory.beginIter());
			break;
		case 4: {
			system("cls");
			cout << "Enter number of seats? ";
			do { // input checking for valid value (integer not below 0)
				try { done = false; cin >> seatsNo; if (!seatsNo || seatsNo < 1) throw 12; done = true; }
				catch (int e) {
					if (e == 12) {
						seatsNo = 0; cin.clear();  cin.ignore(1000, '\n');
						cout << "Incorrect input! Please input a valid option." << endl;
					}
				} // end try catch
			} while (!done); // end while

			//cout<<"GPS [Y/N]?"
			if (!myInventory.found(seatsNo, myInventory.beginIter()))
			{
				cout << "Nothing was found!" << endl;
			}// end if 
		}break;

		case 5: {
			system("cls");
			cout << "Please Enter the Vehicle ID: ";
			int tmpVehicleID;


			do { // input checking for valid value (integer not below 0)
				try { done = false; cin >> tmpVehicleID; if (!tmpVehicleID || tmpVehicleID < 1) throw 12; done = true; }
				catch (int e) { if (e == 12) { tmpVehicleID = 0; cin.clear();  cin.ignore(1000, '\n'); cout << "Incorrect input! Please input a valid option." << endl; } }
			} while (!done);// end do while
			try {
				if (myInventory.reserveVehicle(tmpVehicleID))
				{
					if (!myInventory.saveToFile("vehicles.txt"))
					{
						throw 18;
					} // end if
				} // instead of if statements
				else { throw 18; } // end else
			} // end try
			catch (int e)
			{
				if (e == 18)
				{
					cout << "Reserve Failed...... Make sure that the Vehicle ID is valid." << endl;
				} //end if
			} // end try catch

			break;

		case 6: {system("cls"); cout << "Please Enter the Vehicle ID: ";
			int tmpVehicleID;

			do { // input checking for valid value (integer not below 0)
				try { done = false; cin >> tmpVehicleID; if (!tmpVehicleID || tmpVehicleID < 1) throw 12; done = true; }
				catch (int e) { if (e == 12) { tmpVehicleID = 0; cin.clear();  cin.ignore(1000, '\n'); cout << "Incorrect input! Please input a valid option." << endl; } }
			} while (!done); // end do while

			try {
				if (myInventory.returnVehicle(tmpVehicleID)) { if (!myInventory.saveToFile("vehicles.txt")) { throw 18; } } // instead of if statements, use exception
				else { throw 18; }
			}
			catch (int e) { if (e == 18) { cout << "Return Failed...... Make sure that the Vehicle ID is valid." << endl; break; } } // end try catch

			break;

		case 7: {
			cout << endl;
			string fileName = "";
			cout << endl << endl << "Please enter a file name without an extension(Ex: myFile) -> ";
			cin >> fileName;
			ofstream outFile;
			fileName.append(".txt");
			try { // try catch if file cannot be opened
				outFile.open(fileName);
				if (outFile.fail()) { throw 18; }
				outFile << myInventory;
				outFile.close();
			}
			catch (int e) { if (e == 18) { cout << "\nSystem was not able to create a file" << endl; break; } } // end try catch

			cout << "\nData sent to file " + fileName + "\n"; }
			  break;

		case 8:
			system("cls");
			break;

		default:
			userEntry = 0;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Incorrrect input! Please input a valid option." << endl;
			break; }
		}// end switch

			  if (userEntry == 8) break; // exit

		}

	}
	cout << "Ending the program..... Done!" << endl;
	return 0;
}

bool readingDataFromDBfile(Inventory& myInventory, ifstream& inFile, int recordsInFile) {
	/*reading the inventory informaton (cars that are registered) from the file to the inventory list (data structure.*/
	try {
		int vehicleID;
		string make;
		string model;
		int seats;
		bool available;
		int extarFeatures;
		//NodeList<string> featuresListTmp;
		VectorTree<string> featuresListTmp;
		string tempstring;

		int count = 0;

		while (count < recordsInFile) {
			inFile >> vehicleID;
			inFile.ignore(1000, '\n');
			getline(inFile, make);
			getline(inFile, model);
			inFile.clear();
			inFile >> seats;
			inFile >> available;
			inFile >> extarFeatures;
			inFile.clear();
			inFile.ignore();

			for (int j = 0; j < extarFeatures; ++j) {
				getline(inFile, tempstring);
				featuresListTmp.addLast(tempstring);
				tempstring.clear();
			}

			myInventory.push_Back(Vehicle(vehicleID, make, model, seats, available, extarFeatures, featuresListTmp));
			featuresListTmp.clear();

			++count;
		}
	}
	catch (...) {
		inFile.close();
		return false;
	}

	/*
	for (int i = 0; i < recordsInFile; ++i) { // reading the vehcile information from the file
		//cout << " .";
		inFile >> vehicleID;
		inFile.ignore(1000, '\n');
		getline(inFile, make);
		getline(inFile, model);
		inFile >> seats;
		inFile >> available;
		inFile >> extarFeatures;
		if (extarFeatures > 0)
		{
			inFile.ignore(1000, '\n');

			for (int k = 0; k < extarFeatures; ++k)
			{
				getline(inFile, tempstring);
				featuresListTmp.insertBack(tempstring);
			}
		}
		Vehicle tempVehicle(vehicleID, make, model, seats, available, extarFeatures, featuresListTmp);
		myInventory.push_Back(tempVehicle);
		featuresListTmp.clear();
	}
	*/
	inFile.close();
	

	return  true;
}