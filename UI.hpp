// UI.hpp

#pragma once

#include "calendar.hpp" // Used for classes Calendar and DayNotes
#include "ID.hpp" // Used for dateToID IDToDate
#include <ctime> // Used for tm
#include <iostream> // Used for cin cout endl
#include <iomanip> // Used for setw

	// Function to display notes
void displayNotes(DayNotes Notes) {
	if (Notes.exists) {
		std::cout << "Day Quality: " << Notes.dayQuality << std::endl;
		std::cout << "Sleep Quality: " << Notes.sleepQuality << std::endl;
		std::cout << "Took Meds: " << (Notes.tookMeds ? "Yes" : "No") << std::endl;
		std::cout << std::endl;
	}
	else {
		std::cout << "No notes yet" << std::endl;
		std::cout << std::endl;
	}
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
