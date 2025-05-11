/** ************************************
 * Credit Card Validator using Luhn Algorithm
 *
 * * |---- Details for author, date, version, etc....
 * @filename: LuhnAlgorithmPaudelCapstone.cpp
 * @author:Sudip Paudel
 * @version: 1.0
 * @Since: 2023-10-28
 ************************************ */

#include <iostream>
#include <iomanip>
#include <fstream> // File I/O
#include <ctime> // Needed for date/time
#include <string>

using namespace std;

/**
 * @brief Finds and returns the position of the first non-numeric digit in the string.
 *
 * This function iterates through each character in the input string `cardNo`
 * and identifies the position of the first character that is not a numeric digit.
 *
 * @param cardNo The input string representing a credit card number.
 * @return The position of the first non-numeric digit in the string.
 */
int findNonNumericPosition(const string& cardNo) {
    int position = 0;
    for (char ch : cardNo) {
        int v = ch;
        if (!(v >= 48 && v <= 57))
            break;
        position++;
    }
    return position;
}

// Function to return date and time to display
/** ************************************
 * Function: rtnDateTime
 * Return date and time to display
 * This function retrieves the current date and time and prints
 * it along with the student's name and ID.
 *
 */

void rtnDateTime() {

    time_t curr_time;
    tm* curr_tm;
    char date_string[100];
    char time_string[100];

    time(&curr_time);
    curr_tm = localtime(&curr_time);

    strftime(date_string, 50, "Today is %B %d, %Y", curr_tm);
    strftime(time_string, 50, "Current time is %T", curr_tm);

    cout << date_string << " and " << time_string << endl;

    cout << "Student Name: Sudip Paudel." << endl;
    cout << "Student ID: 3697484" << endl;
    cout << date_string << endl;
}

// Function to check if a credit card number is valid using the Luhn Algorithm
/** ************************************
 * Function: luhnAlgorithm
 * Check if a credit card number is valid using the Luhn Algorithm
 * This function implements the Luhn Algorithm to determine the
 * validity of a credit card number.
 *
 */

bool luhnAlgorithm(const string& cardNo) {
    int sum = 0;
    bool doubleDigit = false;

    for (int i = cardNo.length() - 1; i >= 0; --i) {
        int digit = cardNo[i] - '0';

        if (doubleDigit) {
            digit *= 2;
            if (digit > 9) {
                digit -= 9;
            }
        }

        sum += digit;
        doubleDigit = !doubleDigit;
    }

    return (sum % 10 == 0);
}

/** ************************************
 * Function: main
 * Main function driving the program
 * a:Open a file for input and read credit numbers from this file
 * and store them in a list. Ex file: credit_cards.txt
 * b:Display student information and date/time
 * c:Display credit card validation report
 * d:Calculate and display total records count and valid/invalid counts
 *
 * The main function orchestrates the entire program. It reads credit
 * card numbers from a file, validates them using the Luhn Algorithm,
 * and displays a report with details on each card's validity.
 *
 * @param args Unused.
 * @return Nothing.
 */

int main() {
    const int MAX_RECORDS = 100;
    string cardLyst[MAX_RECORDS];
    int aSize = 0;

    ifstream inputFile("credit_cards.txt");

    if (!inputFile) {
        cerr << "Error opening file: credit_cards.txt" << endl;
        return 1;
    }

    // Read credit card numbers from the file
    while (aSize < MAX_RECORDS && inputFile >> cardLyst[aSize]) {
        aSize++;
    }

    inputFile.close();

    cout << "This program is used to implement the Luhn Algorithm for Credit Card Validation." << endl;

    // Displaying student information and date/time
    rtnDateTime();

    // Displaying credit card validation report
    cout << endl;
    cout << setw(6) << "Record #"
        << setw(25) << "Credit Card"
        << setw(30) << "Valid/Invalid Report" << endl;

    int validCount = 0;
    for (int i = 0; i < aSize; ++i) {
        cout << setw(6) << i + 1
            << setw(25) << cardLyst[i];

        if (cardLyst[i].length() != 16) {
            cout << setw(50) << " is Not Valid, length should be 16." << endl;
        }
        else {
            bool isValid = luhnAlgorithm(cardLyst[i]);
            if (isValid) {
                cout << setw(25) << " is Valid." << endl;
                validCount++;
            }
            else {
                int missingDigit = (10 - (luhnAlgorithm(cardLyst[i] + '0') % 10)) % 10;
                cout << setw(30) << " is Not Valid, ";
                if (missingDigit == 0) {
                    cout << "check digit should be 0." << endl;
                }
                else {
                    cout << "check digit should be " << missingDigit << "." << endl;
                }
            }
        }
    }

    // Displaying total records count and valid/invalid counts
    cout << endl;
    cout << "Total number of records read: " << aSize << endl;
    cout << "Records containing Valid credit card numbers: " << validCount << endl;
    cout << "Records containing Invalid credit card numbers: " << aSize - validCount << endl;

    return 0;
}
