// ID.hpp

#pragma once

#include "split.hpp" // Used for split
#include <ctime> // Used for tm
#include <string> // Used for string

	// Function to convert string ID to tm date
static tm IDToDate(std::string ID) {
	std::tm date{};
	std::vector<std::string> parts = split(ID, '-'); // split the string by the hyphen character
	std::string WeekDay = parts[0]; // Day of Week Ignored
	date.tm_mon = stoi(parts[1]) - 1; // Month 0-11
	date.tm_mday = stoi(parts[2]); // Day
	date.tm_year = stoi(parts[3]) - 1900; //Year
	std::mktime(&date);
	return date;
}

// Function to convert tm date to string ID
static std::string dateToID(tm date)
{
	// normalize the date and time values
	std::mktime(&date);

	// Extract week number, day of the week, and year
	int dayOfWeek = date.tm_wday; // Week begins at 0 on Sunday
	int dayOfMonth = date.tm_mday; // Day of month
	int month = date.tm_mon + 1; // Month is 1-12
	int year = date.tm_year + 1900; // Year since 1900

	// DayOfWeek-Month-DayOfMonth-Year
	std::string ID{ 0 };

	ID.append(std::to_string(dayOfWeek));
	ID.append("-");
	if (std::to_string(month).length() == 1) { // add zero if month is single digit
		ID.append("0");
	}
	ID.append(std::to_string(month));
	ID.append("-");
	if (std::to_string(dayOfMonth).length() == 1) { // add zero if dayOfMonth is single digit
		ID.append("0");
		//ID.insert(0, 1, '0');
	}
	ID.append(std::to_string(dayOfMonth));
	ID.append("-");
	ID.append(std::to_string(year));

	return ID;
}


