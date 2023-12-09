//Tracker Base
//Joshua Ham

#define __STDC_WANT_LIB_EXT1__ 1
#include <iostream>
#include <ctime>
#include <vector> 
#include <map>
#include <iomanip>
#include <string>

using namespace std;


// Class to represent notes for a day
class DayNotes {
public:
    int dayQuality;
    int sleepQuality;
    bool tookMeds;

    DayNotes() : dayQuality(0), sleepQuality(0), tookMeds(false) {}
};

// Class to manage the calendar
class Calendar {
private:
    std::map<string, DayNotes> days;  // Using long long to store the unique ID

public:
    // Function to add a day with notes to the calendar
    void addDay(string id, const DayNotes& notes) {
        days[id] = notes;
    }

    // Function to get notes for a specific day
    DayNotes getDayNotes(string id) {
        return days[id];
    }
};

//Function to convert tm date to ID
string dateToID(tm Date)
{
    time_t t = mktime(&Date); // Convert date to time_t

    // Extract week number, day of the week, and year
    int weekNumber = Date.tm_yday / 7 + 1; //First week is 1
    int dayOfWeek = Date.tm_wday + 1; // Week begins at 1 on Sunday
    int year = Date.tm_year + 1900;

    // Create a string in the desired format
    string ID = to_string(weekNumber) + to_string(dayOfWeek) + to_string(year);
    int number_of_zeros = 7 - ID.length(); // add zero if weekNumber is single digit
    ID.insert(0, number_of_zeros, '0');
    
    //cout << weekNumber << endl << dayOfWeek << endl << year << endl; //Output info if needed to test
    
    return ID;
}



int main() {
    // Get the current time
    time_t t = time(0);
    tm now;
    localtime_s(&now, &t);

    string todayID = dateToID(now);
    cout << "Today is  " << put_time(&now, "%c") << endl;
    cout << "ID is " << todayID << endl << endl;



    //Input Date to note
    cout << "Input date (mm/dd/yyyy): ";

    //Input date to check/edit
    tm inputDateTime{};
    cin >> get_time(&inputDateTime, "%m/%d/%Y");
    if (cin.fail()) {
        cout << "Invalid input\n";
    }
    else {
        cout << "You entered: " << put_time(&inputDateTime, "%c") << endl;
    }
    string inputID = dateToID(inputDateTime);
    
    cout << "ID is " << inputID << endl << endl;


    // Set up calendar
    Calendar myCalendar;

    // Add notes for a day
    DayNotes notes1;
    notes1.dayQuality = 8;
    notes1.sleepQuality = 9;
    notes1.tookMeds = true;

    myCalendar.addDay(inputID, notes1);

    // Retrieve and print notes for the day
    DayNotes retrievedNotes = myCalendar.getDayNotes(inputID);
    cout << "Day Quality: " << retrievedNotes.dayQuality << endl;
    cout << "Sleep Quality: " << retrievedNotes.sleepQuality << endl;
    cout << "Took Meds: " << (retrievedNotes.tookMeds ? "Yes" : "No") << endl;


    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
