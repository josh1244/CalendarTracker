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
#include <algorithm>
#include <chrono>
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
        std::cout << "No calendar found. Making new one." << std::endl;
        return data;
    }
    if (inFile.peek() == EOF) {
        std::cout << "No calendar found. Making new one." << std::endl;
        return data;
    }

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
    if (ID.length() == 6) { // add zero if weekNumber is single digit
        ID.insert(0, 1, '0');
    }

    //cout << weekNumber << endl << dayOfWeek << endl << year << endl; //Output info if needed to test

    return ID;
}

void displayNotes(DayNotes Notes) {
    // Display Notes
    std::cout << "Day Quality: " << Notes.dayQuality << std::endl;
    std::cout << "Sleep Quality: " << Notes.sleepQuality << std::endl;
    std::cout << "Took Meds: " << (Notes.tookMeds ? "Yes" : "No") << std::endl;
    std::cout << endl;
}

void drawCalendar(tm Date) {
    time_t t = mktime(&Date); // Convert date to time_t

    // Extract week number, day of the week, and year
    int weekNumber = Date.tm_yday / 7 + 1; // Display in front of calendar
    int day = Date.tm_mday;
    int dayOfWeek = Date.tm_wday; // First day is 1 Sunday
    string year = std::to_string(Date.tm_year + 1900);
    
    //Figure out the days of the week
    int days[7];
    time_t t2;
    for (int i = 0; i < 7; i++) {
        t2 = t - (dayOfWeek - i) * (static_cast<long long>(24 * 60) * 60);
        tm prev;
        localtime_s(&prev, &t2);
        days[i] = prev.tm_mday;
        //int sunday = sundayDay.tm_mday;
    }
    //if (day < 7 or > 22) then something else
    //int day1 = day - dayOfWeek;
    std::cout << "Week: " << weekNumber << "                           " << year << std::endl;
    std::cout << "  _______________________________________________________________________" << std::endl;
    std::cout << "  |  Sunday |  Monday | Tuesday |Wednesday| Thursday| Friday  | Saturday|" << std::endl;
    //cout << weekNumber << std::setw(2 - std::to_string(weekNumber).length()) <<
    std::cout << "  |   " << std::setw(2) << days[0] <<
               "    |   " << std::setw(2) << days[1] <<
               "    |   " << std::setw(2) << days[2] <<
               "    |   " << std::setw(2) << days[3] <<
               "    |   " << std::setw(2) << days[4] <<
               "    |   " << std::setw(2) << days[5] <<
               "    |   " << std::setw(2) << days[6] <<
               "    |" << std::endl;
    std::cout << "  |_________|_________|_________|_________|_________|_________|_________|" << std::endl;
}

int main() {
    // Load Calendar data
    Calendar myCalendar = loadFromFile("calendar");
    DayNotes retrievedNotes;

    // Get the current time
    time_t t = time(0);
    tm now;
    localtime_s(&now, &t);

    string todayID = dateToID(now);
    cout << "Today is  " << put_time(&now, "%c") << endl;
    cout << "ID is " << todayID << endl << endl;

    retrievedNotes = myCalendar.getDayNotes(todayID);
    // Display today's Notes
    displayNotes(retrievedNotes);
   
    drawCalendar(now);

    
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

    // Retrieve and print notes for the day
    cout << "Current Notes: " << endl;
    retrievedNotes = myCalendar.getDayNotes(inputID);
    displayNotes(retrievedNotes);







    // Add notes for a day
    DayNotes notes;
 

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
    // Use setw and setfill to format the output
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
    // Use setw and setfill to format the output
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

*/