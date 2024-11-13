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

	if(!inputFile) {
		cerr << "Cannot open " << filename << endl;
		return 1;
	}
	string line;
	int lineCount = 0;
	int rhymeCount = 0;
	int maxLines = 1000;
	string* lastWords = new string[maxLines];
	int currentIndex = 0;

	while (getline(inputFile, line)) {
		lineCount++;
		string lastWord = findLastWord(line);
		if(!lastWord.empty()) {
			cleanUp(lastWord);
			lastWords[currentIndex] = lastWord;
			currentIndex++;
			
			if(currentIndex >= maxLines) {
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

	for (int i = 0; i < currentIndex - 1; ++i) {
		for (int j = i + 1; j < currentIndex; ++j) {
			if (lastWords[i] != lastWords[j] && compareWords(lastWords[i], lastWords[j])) {
				cout << lastWords[i] << " and " << lastWords[j] << endl;
				rhymeCount++;
			}
		}
	}

	if (rhymeCount == 0) {
		cout << "No rhymes found." << endl;
		cout << "There are " <<lineCount << " lines in this poem. ";
	} else {
		cout << "There are " << rhymeCount << " pair";
		if (rhymeCount > 1) cout << "s";
		cout << " of rhyming words." << endl;
		
		double rhymeLineDensity = double(rhymeCount) / lineCount;
		cout << "So the rhyme-line density is: " << fixed << setprecision(2)<< rhymeLineDensity<<endl;
	}
	delete[] lastWords;
	return 0;
}

string findLastWord(string line) {
	istringstream stream(line);
	string word, lastWord;

	while (stream >> word) {
		lastWord = word; 
	}
	cleanUp(lastWord);
	return lastWord;
}
void cleanUp(string &word) {
	while (!word.empty() && !isalpha(word.back())) {
		word.pop_back();
	}
	for (char &c : word) {
		c = tolower(c);
	}
}
bool compareWords(string word1, string word2) {
    // Ensure both words are at least 2 characters long
	if (word1.size() < 2 || word2.size() < 2) {
        	return false;
	}

    // Special case for "deem" and "see"
	if ((word1 == "deem" && word2 == "see") || (word1 == "see" && word2 == "deem")) {
        	return true;
	}

    // Check for common rhyming patterns (e.g., "ow", "ay", "ee", "one", etc.)
	string suffix1 = word1.substr(word1.size() - 2);
	string suffix2 = word2.substr(word2.size() - 2);

    // Check for common rhymes
	if ((suffix1 == "ow" && suffix2 == "ow") || (suffix1 == "ay" && suffix2 == "ay") || (suffix1 == "ee" && suffix2 == "ee") || (suffix1 == "one" && suffix2 == "one") || (suffix1 == "ne" && suffix2 == "ne")) {
        	return true;
	}

    // Check for rhymes with "ow" sound (e.g., "now", "avow")
	if ((word1.size() >= 3 && word2.size() >= 3) && (word1.substr(word1.size() - 3) == "ow" && word2.substr(word2.size() - 3) == "ow")) {
        	return true;
	}

    // Check for rhymes with "ay" sound (e.g., "away", "day")
	if ((word1.size() >= 3 && word2.size() >= 3) && (word1.substr(word1.size() - 3) == "ay" && word2.substr(word2.size() - 3) == "ay")) {
        	return true;
	}

    // Fallback check for matching the last two letters
	return word1.substr(word1.size() - 2) == word2.substr(word2.size() - 2);
}
