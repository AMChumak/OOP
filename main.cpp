#include <iostream>
//for work with files
#include <fstream>
//for work with strings and their methods
#include <string>
// STL containers
#include <map>
#include <list>
#include <set>


using namespace std;

//type for showing connection between string and it's count
typedef pair<string, int> statisticPair;


//function that checks count of arguments and sets files variables
int checkArguments(int argumentCount, char **argumentValues, string &inputFile, string &outputFile);

//function that takes words from file
void processingFile(ifstream &stream, map<string, int> &wordList, set<char> &delimitersSet, int &wordCounter);

//main block of the processingFile function that takes and count words from the one string
void processingString(ifstream &stream, map<string, int> &wordList, set<char> &delimitersSet, int &wordCounter);

//function that adds word to map of string and int: adds new pair or increments value of  the pair which exists
void addStringAtMap(string source, map<string, int> &wordList);

//Copies data from map of <string, int> to list of statisticPairs
void transformMapToList(map<string, int> &source, list<statisticPair> &destination);

//transmits data from the list to the output file
void transmitToFile(ofstream &stream, list<statisticPair> &table, int WordCounter);

//sort function which compare pairs of <string, int>
bool comparePair(statisticPair firstOperand, statisticPair secondOperand);


int main(int argc, char **argv)
{
    string inputFile, outputFile;
    //exit if program have nothing or too many arguments
    if(checkArguments(argc, argv, inputFile, outputFile) == 1) return 0;

    //set of delimiters
    set<char> delimiters = {' ', '`', '~', '\'', '\"', '!', '\t', '\0', '@', '#', '$', ';', '%', '^', ':', '&','?','*','(',')','[',']','{','}','\\','/','|','<','>','.','-','_','+','=','\v','\a','\r','\b'};

    ifstream inputFileStream;
    inputFileStream.open(inputFile, fstream::in);

    // checks existing file
    if (!inputFileStream) {
      printf("input file does not exist\n");
      return 0;
    }

    int totalWordCounter = 0;
    map<string, int> wordDictionary = {};

    //take and count word from the file
    processingFile(inputFileStream, wordDictionary, delimiters, totalWordCounter);
    inputFileStream.close();

    //Create list for sort and copy data from map to list
    list<statisticPair> statisticList = {};
    transformMapToList(wordDictionary, statisticList);
    //sort data by values of pairs
    statisticList.sort(comparePair);

    //print result to the output file
    ofstream outputFileStream;
    outputFileStream.open(outputFile, fstream::out);
    transmitToFile(outputFileStream, statisticList, totalWordCounter);
    outputFileStream.close();

    return 0;
}

//CheckArguments - function that checks, counts arguments and sets files variables
//it has parametrs: argumentCount - integer number of arguments, arrayValues - char* array of values
//&inputFile, &outputFile - files refferences
//returns 1 if parametrs isn't correct else returns 0
int checkArguments(int argumentCount, char **argumentValues, string &inputFile, string &outputFile){
    //checks argumentCount and when decided on sets files names
    switch (argumentCount)
    {
    case 1:
        cout << "Program has no input file." << endl;
        cout << "You should write one full path to input file at least." << endl;
        cout << "Also you can point path to output csv file" << endl;
        return 1;
        break;
    case 2:
        inputFile = argumentValues[1];
        //if user didn't point output file program would use "result.csv" file 
        outputFile = "result.csv";
        return 0;
        break;
    case 3:
        inputFile = argumentValues[1];
        outputFile = argumentValues[2];
        return 0;
        break;
    case 4:
        cout << "Too many arguments." << endl;
        return 1;
        break;
    default:
        return 0;
        break;
    }
}

//comparePair - function that compares statisticPairs by their int values
//returns bool value of compare expression
bool comparePair(statisticPair firstOperand, statisticPair secondOperand) {
    return firstOperand.second > secondOperand.second;
}

//takes words and count them from file
// stream - input file stream, wordList = map of pairs of string and it's count, delimitersSet - set of delimiters, wordCounter - counter of all words
void processingFile(ifstream &stream, map<string, int> &wordList, set<char> &delimitersSet, int &wordCounter)
{
    // use processingString function for each string
    while(!stream.eof()){
        processingString(stream, wordList, delimitersSet, wordCounter);
    }

}
// takes words from the one string
// stream - input file stream, wordList = map of pairs of string and it's count, delimitersSet - set of delimiters, wordCounter - counter of all words
void processingString(ifstream &stream, map<string, int> &wordList, set<char> &delimitersSet, int &wordCounter)
{
    string currentString, currentWord = "";
    //take string to next line feed or end of file 
    getline(stream, currentString);
    const int currentStringLength = currentString.length();
    //sort through each symbol
    for (int i = 0; i < currentStringLength; i++) {
        // if symbol isn't delimiter - add it in word
        if (delimitersSet.find(currentString[i]) == delimitersSet.end()){
            currentWord.push_back(currentString[i]);
        //else it delimiter of non-empty word - add word in map
        } else if(currentWord.length() != 0){
            addStringAtMap(currentWord, wordList);
            wordCounter++;
            currentWord.clear();
        }
    }
    // if there are any symbols in buffer left - add this word in map
    if (currentWord.length() != 0){
        addStringAtMap(currentWord, wordList);
        wordCounter++;
        currentWord.clear();
    }
}

//function that adds string in map of pairs of string(key) and int(value)
// source - string which function adds to map, wordList - destination
void addStringAtMap(string source, map<string, int> &wordList){
    map<string, int>::iterator foundPair;
    //find pair by key
    //if found - increment value, else - add new pair with source(key) and 1(value)
    if((foundPair = wordList.find(source)) != wordList.end()) {
        (foundPair->second)++;
    }else {
        wordList.insert(pair<string, int>(source, 1));
    }
}

// function that transform map of words and their counts to list of same pairs
// source - map of <(word)string, (count)int>, destination - list of statisticPair = <(word)string, (count)int>
void transformMapToList(map<string, int> &source, list<statisticPair> &destination){
    map<string, int>::iterator currentPair = source.begin();
    while(currentPair != source.end()){
        destination.push_back({currentPair->first, currentPair->second});
        currentPair++;
    }
}

// function that prints table to file
// stream - output file stream, table - list of statisticPair = <(word)string, (count)int>, wordCounter - counter of all words 
void transmitToFile(ofstream &stream, list<statisticPair> &table, int wordCounter){
    list<statisticPair>::iterator currentPair = table.begin();
    //print headers
    stream << "Слово, Частота, Частота (в %)" << endl;
    while (currentPair != table.end())
    {
        stream << currentPair->first << ',' << currentPair->second << ',' << (double)(currentPair->second) / (double)wordCounter * 100 << endl;
        currentPair++;
    }
}

