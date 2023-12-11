// calendar.hpp

// Use header guards to prevent multiple inclusion
#pragma once

// Include the necessary headers or forward declarations
#include "ID.hpp"

// cereal is used for serialization
#include <cereal/archives/binary.hpp> // Include the cereal headers
#include <cereal/types/map.hpp> // Include the cereal headers
#include <cereal/types/string.hpp> // Include the cereal headers
#include <ctime> // Used for tm
#include <fstream> // Used for ifstream ofstream
#include <iomanip> // Used for setw
#include <iostream> // Used for cin cout endl
#include <map> // Used for map
#include <string> // Used for string
#include <vector> // Used for vector


// Use a namespace to avoid name conflicts
namespace cal
{
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
	static cal::Calendar loadFromFile(std::string fileName) {
		// Setup variable to handle file
		std::ifstream inFile;
		cal::Calendar data;

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
	static void saveToFile(std::string fileName, cal::Calendar data) {
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

	// Function to display notes
	static void displayNotes(cal::DayNotes Notes) {
		// Display Notes
		std::cout << "Day Quality: " << Notes.dayQuality << std::endl;
		std::cout << "Sleep Quality: " << Notes.sleepQuality << std::endl;
		std::cout << "Took Meds: " << (Notes.tookMeds ? "Yes" : "No") << std::endl;
		std::cout << std::endl;
	}

	// Function to draw Calendar
	static void drawCalendar(std::string ID) {
		tm date = IDToDate(ID);

		// Convert date to time_t
		time_t t = std::mktime(&date);

		// Extract week number, day of the week, and year
		int weekNumber = date.tm_yday / 7 + 1; // Display in front of calendar
		int day = date.tm_mday; // Day of the month
		int dayOfWeek = date.tm_wday; // First day is 0 Sunday
		std::string year = std::to_string(date.tm_year + 1900);

		//Figure out the days of the week
		int days[7]{};
		time_t t2;
		for (int i = 0; i < 7; i++) {
			t2 = t - (static_cast<long long>(dayOfWeek) - i) * (static_cast<long long>(24 * 60) * 60);
			tm prev;
			localtime_s(&prev, &t2);
			days[i] = prev.tm_mday;
			//int sunday = sundayDay.tm_mday;
		}

		// Asign month name to month
		std::string month{};
		switch (date.tm_mon) {
		case (0):
			month = "January";
			break;
		case (1):
			month = "Febuary";
			break;
		case (2):
			month = "March";
			break;
		case (3):
			month = "April";
			break;
		case (4):
			month = "May";
			break;
		case (5):
			month = "June";
			break;
		case (6):
			month = "July";
			break;
		case (7):
			month = "August";
			break;
		case (8):
			month = "September";
			break;
		case (9):
			month = "October";
			break;
		case (10):
			month = "November";
			break;
		case (11):
			month = "December";
			break;
		default:
			month = "MONTH ERROR";
		}

		std::cout << "Week: " << weekNumber << "                         " << year << std::endl;
		std::cout << month << std::endl;
		std::cout << "_______________________________________________________________________" << std::endl;
		std::cout << "|  Sunday |  Monday | Tuesday |Wednesday| Thursday| Friday  | Saturday|" << std::endl;
		std::cout << "|   " << std::setw(2) << days[0] <<
			"    |   " << std::setw(2) << days[1] <<
			"    |   " << std::setw(2) << days[2] <<
			"    |   " << std::setw(2) << days[3] <<
			"    |   " << std::setw(2) << days[4] <<
			"    |   " << std::setw(2) << days[5] <<
			"    |   " << std::setw(2) << days[6] <<
			"    |" << std::endl;
		std::cout << "|_________|_________|_________|_________|_________|_________|_________|" << std::endl;
	}

}
