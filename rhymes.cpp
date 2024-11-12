#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;

// FUNCTION DECLARATIONS: YOU MUST DEFINE AND USE THESE (do not remove):
//      You can declare/define other functions if you like as well,
//      but you must use the 3 functions below.
// See lab description for more on these functions.

string findLastWord(string line);
void cleanUp(string &word);
bool compareWords(string word1, string word2);

int main() {
	string filename;
	cout << "Enter Filename: ";
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
		if (compareWords(lastWords[i], lastWords[i + 1])) {
			cout << lastWords[i] << " and " << lastWords[i + 1]<< endl;
			rhymeCount++;
		}
	}
	cout << "There are " <<lineCount << " lines in this poem, ";
	
	if (rhymeCount == 0) {
		cout << "No rhymes found." << endl;
	} else {
		cout << "There are " << rhymeCount << " pair";
		if (rhymeCount > 1) cout << "s";
		cout << " of rhyming words." << endl;

		double rhymeLineDensity = double(rhymeCount) / lineCount;
		cout << "so the rhyme-line density is: " << fixed << setprecision(2)<< rhymeLineDensity<<endl;
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
	if (word1.size() < 2 || word2.size() < 2) {
		return false;
	}
	return (word1.substr(word1.size() - 2) == word2.substr(word2.size() - 2));
	}
	

