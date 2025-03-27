//Asahi Smith 10655230
//Object Oriented Programming with C++ 
//Assignment 1

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;



//Asahi Smith 15/3/25
//Define Word struct 
struct Word {
    string name;
    string type;
    string definition;

};



//Asahi Smith 15/3/25, 20/3/25
//Function to load and parse dictionary file 
//Function attempts to open file and produce error if unable to.
//Function then reads each line of the file and extracts a name, type and definition for each word and adds it to Word vector.
//Function closes file after.
void loadFile(vector<Word> & dictionary, const string & fileName) {
    
    ifstream file(fileName); //attempt to open dictionary file

    if (!file.is_open()) //If unable to open file, print error and end program.
    {
        cout << "Error - File not opened." << "\n";
        return;
    }

    cout << "File opened!" << "\n";
    string line;
    Word word;
    
    getline(file, line); //Skip first line of dictionary

    //while loop to read each line of the dictionary file
    while (getline(file, line)) {
        if (line.empty()) {
            if (!word.name.empty() && !word.type.empty() && !word.definition.empty()) {
                dictionary.push_back(word);
                word = Word();
            }
            continue;
        }

        if (word.name.empty()) {
            word.name = line;
        }
        else if (word.type.empty()) {
            word.type = line;
        }
        else {
            if (!word.definition.empty()) {
                word.definition += " ";
            }
            word.definition += line;
        }
    }

    if (!word.name.empty() && !word.type.empty() && !word.definition.empty()) {
        dictionary.push_back(word);
    }
  
    file.close();
    cout << "Dictionary loaded with " << dictionary.size() << " words." << "\n";
}



// Asahi Smith 15/3/25
//Stores the word types and their abbreviations
string getAbbrev(string type) {
    if (!type.empty() && type.back() == ';') {
        type.pop_back();
    }

    if (type == "n") return "(n.)";
    if (type == "v") return "(v.)";
    if (type == "adv") return "(adv.)";
    if (type == "adj") return "(adj.)";
    if (type == "prep") return "(prep.)";
    if (type == "misc") return "(misc.)";
    if (type == "pn") return "(pn.)";
    if (type == "n_and_v") return "(n. v.)";
    return "(" + type + ")";
}



//Asahi Smith 20/3/25
//Function to convert string to lowercase
string toLower(const string& str) {
    string lowerString = str;
    transform(lowerString.begin(), lowerString.end(), lowerString.begin(), ::tolower);
    return lowerString;
}



//Asahi Smith 15/3/25, 20/3/25
//Function asks user to enter a word to search the dictionary
//If dictionary is empty, return an error message
//If word is found, display the word name, abbreviated word type, and their definitions
void searchWord(const vector<Word>&dictionary) {
    // if dictionary is empty, print an error message 
    if (dictionary.empty()) {
        cout << "Error - dictionary empty." << "\n";
        return;
    }

    //Ask user to enter a word to search the dictionary, save input as searchWord string.
    string searchWord;
    cout << "\nEnter a word to search: ";
    cin >> searchWord;
    searchWord = toLower(searchWord); // Convert input to lowercase

    bool found = false;
    for (const Word& word:dictionary) {
        string dictWord = word.name;

        // Remove last semicolon if present
        if (!dictWord.empty() && dictWord.back() == ';') {
            dictWord.pop_back();
        }

        // Print word, type, definition
        if (toLower(dictWord) == searchWord) { 
            found = true;
            cout << "Word: " << dictWord << "\n";
            cout << "Type: " << getAbbrev(word.type) << "\n";
            cout << "Definition(s): " << "\n";
            
            // Split words with multiple definitions on multiple lines
            size_t start = 0, end;
            while ((end = word.definition.find(';', start)) != string::npos) {
                cout << "- " << word.definition.substr(start, end - start) << "\n";
                start = end + 1;
            }

            //Print final definition
            if (start < word.definition.length()) {
                cout << "- " << word.definition.substr(start) << "\n";
            }

            break;
        }
    }

    if (!found) {
        cout << "Word not found. " << "\n";
    }

}



//Asahi Smith 20/3/25
//Function picks a random index, then uses this index to choose a word from the dictionary and displays the name,type,definition
void randomWord(const vector<Word>& dictionary) {
    // if dictionary is empty, print an error message 
    if (dictionary.empty()) {
        cout << "Error - dictionary empty." << "\n";
        return;
    }

    //Pick random word from dictionary
    int randomIndex = rand() % dictionary.size();
    const Word& word = dictionary[randomIndex];

    cout << "\nRandom word: " << word.name << "\n";
    cout << "Type: " << getAbbrev(word.type) << "\n";
    cout << "Definition(s): " << "\n";

    // Split words with multiple definitions on multiple lines
    size_t start = 0, end;
    while ((end = word.definition.find(';', start)) != string::npos) {
        cout << "- " << word.definition.substr(start, end - start) << "\n";
        start = end + 1;
    }

    //Print final definition
    if (start < word.definition.length()) {
        cout << "- " << word.definition.substr(start) << "\n";
    }


}



//Asahi Smith 15/3/25
// Main function 
// Runs main menu loop, which calls the subsequent functions
int main()
{   
    string fileName = "D:/ECU/Y2S1 C++ Assignment 1/Assignment1/dictionary_2025S1.txt"; //dictionary file name 

    vector<Word> dictionary; // Stl vector of Word instance called Dictionary

    srand(static_cast<unsigned int>(time(0))); //seed for random index


    cout << "Welcome to Object-Oriented Programming with C++ 2025, Assignment 1. \nCreated by Asahi Smith - 10655230";

    //Asahi Smith 20/3/25
    // Menu function infinite loop
    for (;;) {
        int input;
        cout << "\n\nInput a number to perform an action: \n1) Load Dictionary \n2) Search Word \n3) Random Word \n4) Exit \n >> ";
        cin >> input;

        if (cin.fail()) { // Check if input is not a number
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input, please enter a valid number (1,2,3,4). ";
            continue;
        }

        if (input == 1) { // Load Dictionary
            loadFile(dictionary, fileName); // Calls to run loadFile Function 
        }
        else if (input == 2) { // Search Word
            searchWord(dictionary); // Calls to run searchWord function
        }
        else if (input == 3) { // Random Word
            randomWord(dictionary);
        }
        else if (input == 4) { // Exit
            cout << "Goodbye.";
            break;
        }
        else { // Error message
            cout << "Invalid input, please enter a valid number (1,2,3,4). ";
        }
    }
    return 0;
}

