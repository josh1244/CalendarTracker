// Tracker Base
// Joshua Ham

#define __STDC_WANT_LIB_EXT1__ 1
#include <iostream>
#include <ctime>
#include <vector> 
#include <map>
#include <iomanip>
#include <string>
#include <fstream>
// Include the cereal headers
#include <cereal/archives/binary.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/string.hpp>

using namespace std;


// Class to represent notes for a day
class DayNotes {
public:
    int dayQuality;
    int sleepQuality;
    bool tookMeds;

    DayNotes() : dayQuality(0), sleepQuality(0), tookMeds(false) {}

    // Define a serialize function for DayNotes
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(dayQuality, sleepQuality, tookMeds); // Serialize the members
    }
};

// Class to manage the calendar
class Calendar {
private:
    std::map<string, DayNotes> days;  // Using string to store the unique ID

public:
    // Function to add a day with notes to the calendar
    void addDay(string id, const DayNotes& notes) {
        days[id] = notes;
    }

    // Function to get notes for a specific day
    DayNotes getDayNotes(string id) {
        return days[id];
    }

    // Define a serialize function for Calendar
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(days); // Serialize the map
    }
};

//Function to load calendar from file
Calendar loadFromFile(string fileName) {
    // Setup variable to handle file
    ifstream inFile;
    Calendar data;

    // Open File
    inFile.open("calendar");
    if (!inFile) {
        cout << "No calendar found. Making new one.\n";
        return data;
    }

    /*
    // Load from file
    inFile.read((char*)&data, sizeof(data)); //For classes

    // Close the file
    inFile.close();

    return data;
    */


    // Load from file
    cereal::BinaryInputArchive iarchive(inFile); // Create a cereal input archive
    iarchive(data); // Deserialize the data

    // Close the file
    inFile.close();

    return data;
}

//Function to save calendar to file
void saveToFile(string fileName, Calendar data) {
    // Setup variable to handle file
    ofstream outFile;

    // Open File
    outFile.open("calendar");
    if (!outFile) {
        cout << "No calendar found. Making new one.\n";
    }

    // Save to file
    cereal::BinaryOutputArchive oarchive(outFile); // Create a cereal output archive
    oarchive(data); // Serialize the data

    //outFile.write((char*)&data, sizeof(data));

    // Close the file
    outFile.close();
}

// Function to convert tm date to ID
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
    // Load Calendar data
    Calendar myCalendar = loadFromFile("calendar");

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

    saveToFile("calendar", myCalendar);

    return 0;
}



/*
Next steps
Show notes for today
Show notes for inputted date
Loop script
save notes properly
Input Note varaibles
Change what notes can contain

*/