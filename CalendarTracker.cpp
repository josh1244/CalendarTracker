// Tracker Base
// Joshua Ham

#define __STDC_WANT_LIB_EXT1__ 1
//Custom class
#include "calendar.hpp"
#include "ID.hpp"

#include <algorithm> // Used for clamp and transform
#include <ctime> // Used for tm
#include <iostream> // Used for set

int main() {
	using namespace std;

	// Load Calendar data
	cal::Calendar myCalendar = cal::loadFromFile("calendar");
	cal::DayNotes retrievedNotes;

	// Get the current time
	time_t t = time(0);
	tm now;
	localtime_s(&now, &t);

	string todayID = dateToID(now);
	cout << "Today is  " << put_time(&now, "%c") << endl;
	cout << "ID is " << todayID << endl << endl;


	// Draw Calendar
	cal::drawCalendar(todayID);
	// Display today's Notes
	retrievedNotes = myCalendar.getDayNotes(todayID);
	displayNotes(retrievedNotes);





	// Input Date
	tm inputDateTime{};
	while (1) { // Make sure input is valid
		cout << "Input date (mm/dd/yyyy): ";
		// Initialize the tm structure with zeros
		memset(&inputDateTime, 0, sizeof(inputDateTime));

		cin >> get_time(&inputDateTime, "%m/%d/%Y");
		if (cin.fail()) {
			//Try again
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Invalid input" << endl;

		}
		else {
			cout << "You entered: " << put_time(&inputDateTime, "%c") << endl;
			break;
		}
	}
	string inputID = dateToID(inputDateTime);

	cout << "ID is " << inputID << endl << endl;

	// Draw Calendar
	cal::drawCalendar(inputID);

	// Retrieve and print notes for the day
	cout << "Current Notes: " << endl;
	retrievedNotes = myCalendar.getDayNotes(inputID);
	displayNotes(retrievedNotes);







	// Add notes for a day
	cal::DayNotes notes;


	// Day Quality
	while (1) { // Make sure input is valid
		cout << "Input Day Quality: ";
		int temp{ 1 }; //Use temp to make sure input is valid and to store numerical input
		string input{}; // Declare a string variable to store the input
		cin >> input;
		for (char c : input) { // Loop through each character in the input
			if (!std::isdigit(c)) { // If the character is not a digit
				temp = 0; // Invalid
				break;
			}
		}
		if (temp == 1) { // If the input is a valid integer
			temp = stoi(input); // Convert the input to an integer
			temp = clamp(temp, 0, 10); // Clamp the input to the range of 0 to 10
		}
		else { // If the input is not a valid integer
			// Print an error message and try again
			cerr << "Invalid input" << endl;
			cin.clear(); // Clear the fail state
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the remaining input
			continue; // Skip the rest of the loop
		}
		// Success
		cout << "You entered: " << temp << endl;
		notes.dayQuality = temp;
		break;
	}
	cout << endl;

	// Sleep Quality
	while (1) { // Make sure input is valid
		cout << "Input Sleep Quality: ";
		int temp{ 1 }; //Use temp to make sure input is valid and to store numerical input
		string input{}; // Declare a string variable to store the input
		cin >> input;
		for (char c : input) { // Loop through each character in the input
			if (!std::isdigit(c)) { // If the character is not a digit
				temp = 0; // Invalid
				break;
			}
		}
		if (temp == 1) { // If the input is a valid integer
			temp = stoi(input); // Convert the input to an integer
			temp = clamp(temp, 0, 10); // Clamp the input to the range of 0 to 10
		}
		else { // If the input is not a valid integer
			// Print an error message and try again
			cerr << "Invalid input" << endl;
			cin.clear(); // Clear the fail state
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the remaining input
			continue; // Skip the rest of the loop
		}
		// Success
		cout << "You entered: " << temp << endl;
		notes.sleepQuality = temp;
		break;
	}
	cout << endl;

	// Took Meds
	while (1) { // Make sure input is valid
		cout << "Took Meds?: ";
		bool temp{};
		string input{}; // Declare a string variable to store the input
		cin >> input;
		// Convert the input to lowercase
		transform(input.begin(), input.end(), input.begin(), ::tolower);

		if (input == "1" || input == "yes" || input == "true" || input == "y") {
			temp = true;
		}
		else if (input == "0" || input == "no" || input == "false" || input == "n") {
			temp = false;
		}
		else {
			// Invalid input, try again
			cin.clear(); // Clear the fail state
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the remaining input
			cout << "Invalid input" << endl;
			continue; // Skip the rest of the loop
		}
		// Success
		cout << "You entered: " << (temp ? "Yes" : "No") << endl;
		notes.tookMeds = temp;
		break;
	}
	cout << endl;


	myCalendar.addDay(inputID, notes);

	// Retrieve and print notes for the day
	cout << "New Notes: " << endl;
	retrievedNotes = myCalendar.getDayNotes(inputID);
	displayNotes(retrievedNotes);

	saveToFile("calendar", myCalendar);

	return 0;
}

/*
Next steps
Loop script
Change what notes can contain
If notes for that day does not exist, then say "no notes for day" instead of 0's
Move Notes for day under that day
Highlight Current day

*/