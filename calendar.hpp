// calendar.hpp

// Use header guards to prevent multiple inclusion
#pragma once

// cereal is used for serialization
#include <cereal/archives/binary.hpp> // Include the cereal headers
#include <cereal/types/map.hpp> // Include the cereal headers
#include <cereal/types/string.hpp> // Include the cereal headers
#include <fstream> // Used for ifstream ofstream
#include <iostream> // Used for cin cout endl
#include <map> // Used for map
#include <string> // Used for string
#include <vector> // Used for vector


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
	std::map<std::string, DayNotes> days;  // Using string to store the unique ID

public:
	// Function to add a day with notes to the calendar
	void addDay(std::string id, const DayNotes& notes) {
		days[id] = notes;
	}

	// Function to get notes for a specific day
	DayNotes getDayNotes(std::string id) {
		return days[id];
	}

	// Define a serialize function for Calendar
	template <class Archive>
	void serialize(Archive& archive)
	{
		archive(days); // Serialize the map
	}
};

// Function to load calendar from file
static Calendar loadFromFile(std::string fileName) {
	// Setup variable to handle file
	std::ifstream inFile;
	Calendar data;

	// Open File
	inFile.open("calendarData");
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

// Function to save calendar to file
static void saveToFile(std::string fileName, Calendar data) {
	// Setup variable to handle file
	std::ofstream outFile;

	// Open File
	outFile.open("calendarData");
	if (!outFile) {
		std::cout << "No calendar found. Making new one.\n";
	}

	// Save to file
	cereal::BinaryOutputArchive oarchive(outFile); // Create a cereal output archive
	oarchive(data); // Serialize the data

	// Close the file
	outFile.close();
}

