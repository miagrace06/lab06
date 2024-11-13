#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;

string findLastWord(string line);
void cleanUp(string &word);
bool compareWords(string word1, string word2);

int main() {
    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Cannot open " << filename << endl;
        return 1;
    }

    string line;
    int lineCount = 0;
    int rhymeCount = 0;
    int maxLines = 1000;
    string* lastWords = new string[maxLines];
    int currentIndex = 0;

    // Read each line and extract the last word
    while (getline(inputFile, line)) {
        lineCount++;
        string lastWord = findLastWord(line);
        if (!lastWord.empty()) {
            cleanUp(lastWord);
            lastWords[currentIndex++] = lastWord;

            // Resize the array if necessary
            if (currentIndex >= maxLines) {
                maxLines *= 2;
                string* temp = new string[maxLines];
                for (int i = 0; i < currentIndex; ++i) {
                    temp[i] = lastWords[i];
                }
                delete[] lastWords;
                lastWords = temp;
            }
        }
    }
    inputFile.close();

    // Compare pairs of words to check for rhymes
    for (int i = 0; i < currentIndex - 1; ++i) {
        for (int j = i + 1; j < currentIndex; ++j) {
            if (compareWords(lastWords[i], lastWords[j])) {
                cout << lastWords[i] << " and " << lastWords[j] << endl;
                rhymeCount++;
            }
        }
    }

    // Print results
    if (rhymeCount == 0) {
        cout << "No rhymes found." << endl;
        cout << "There are " << lineCount << " lines in this poem." << endl;
    } else {
        cout << "There are " << rhymeCount << " pair";
        if (rhymeCount > 1) cout << "s";  // Pluralize "pair" if needed
        cout << " of rhyming words." << endl;
        double rhymeLineDensity = static_cast<double>(rhymeCount * 2) / lineCount;
        cout << "So the rhyme-line density is: " << fixed << setprecision(2) << rhymeLineDensity << endl;
    }

    delete[] lastWords;  // Free allocated memory
    return 0;
}

string findLastWord(string line) {
    istringstream stream(line);
    string word, lastWord;
    while (stream >> word) {
        lastWord = word;  // Update lastWord with the most recent word
    }
    cleanUp(lastWord);  // Clean up the last word
    return lastWord;
}

void cleanUp(string &word) {
    // Remove non-alphabetic characters at the end of the word
    while (!word.empty() && !isalpha(word.back())) {
        word.pop_back();
    }

    // Convert the word to lowercase for case-insensitive comparison
    for (char &c : word) {
        c = tolower(c);
    }
}

bool compareWords(string word1, string word2) {
    // Skip words that are too short to rhyme (less than 2 characters)
    if (word1.size() < 2 || word2.size() < 2) {
        return false;
    }

    // Check if the last 2 characters match
    string suffix1 = word1.substr(word1.size() - 2);
    string suffix2 = word2.substr(word2.size() - 2);
    if (suffix1 == suffix2) {
        return true;
    }

    // Check if the last 3 characters match (if the words are long enough)
    if (word1.size() > 2 && word2.size() > 2) {
        suffix1 = word1.substr(word1.size() - 3);
        suffix2 = word2.substr(word2.size() - 3);
        if (suffix1 == suffix2) {
            return true;
        }
    }

    return false;  // No rhyme found
}
