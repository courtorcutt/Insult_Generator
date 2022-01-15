#include "insultgenerator.h"
#include <iostream>     // std::cout
#include <string>
#include <fstream>
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <sys/stat.h>   // NEEDED FOR READING IN FILE TO CHECK IF EXISTS

using namespace std;

InsultGenerator::InsultGenerator(){
}

// initialize method of the InsultGenerator class
void InsultGenerator :: initialize() { 
    // to seperate each column, I'm going to have a count that
    // iterates adding the insults into three seperate string vectors
    int count = 0;
    string a, b, c;
    
    // read in the file of insults and if it doesn't exist, throw the exception
    ifstream readFile("InsultsSource.txt");
    if (readFile.is_open()){
        // then make sure only reading in insults when not at the end of the file
        while (!readFile.eof( )){
            // if successful in reading in the file, then split into three columns
            // to do this I will split the columns into three vectors and push the string insults into it 
            // incrementing the count each time 
            readFile >> a >> b >> c;
            column1.push_back(a);
            column2.push_back(b);
            column3.push_back(c);
            count ++;
        } readFile.close();
    } else throw FileException();
    return;
}

string InsultGenerator :: talkToMe(){
    // this will return an insult that is generated from the three column arrays
    // since there are 50 insults in a column I am choosing one of the 50 to make a single insult
    int x = rand() % 50;
    int y = rand() % 50;
    int z = rand() % 50;

    // now the string will be created choosing different insults from each column to string together
    return ("Thou " + column1[x] + " " + column2[y] + " " + column3[z] + "!");
}

vector<string> InsultGenerator :: generate(int numberInsults){
    // want to generate a maximum of 10, 000 insults
    if (numberInsults <= 10000 && numberInsults > 0){
        // so the talkToMe() function only generates one insult 

        // for every insult generated it will be pushed into the insults list
        vector<string> insultsList;
        string insultGeneration;
        
        // so I will create a list of insults by incrementing i 
        // and calling the talkToMe() function every time
        // then I will push the generated insult string into the string vector
        for(int i = 0; i< numberInsults; i++){
            insultGeneration = talkToMe();
                insultsList.push_back(insultGeneration);
        } return insultsList;
    // if the number of insults wanted to be generated is out of bounds throw exception
    } else throw NumInsultsOutOfBounds(numberInsults);
}

void InsultGenerator :: generateAndSave(string writtenFilename, int numberInsults) {
    // this will be where the insults are generated and sorted alphabetically with sort algorithm
    vector<string> insultsList = generate(numberInsults);
    sort(insultsList.begin(), insultsList.end());
    
    // in order to throw a file exception, the name of the file to be written into must be checked
    bool fileExists = writtenFileExistsCheck(writtenFilename);

    // now instead of reading a file, I want to write to one that is passed in instead using ofstream
    ofstream writeFile(writtenFilename);
    
    // if the file does in fact exist, (SavedInsults.txt), write to it
    if(fileExists == true){
        // this will write all the insults in insultsList to the file by iterating through elements
        for (auto &elements : insultsList) {
            writeFile << elements << endl;
        } writeFile.close();
    } else throw FileException();
}

// will check if the file to be written to actually exists and return true if yes, false if no
bool InsultGenerator :: writtenFileExistsCheck(const string& filename) {
  struct stat buffer;   
  return (stat (filename.c_str(), &buffer) == 0); 
}

FileException :: FileException(){
}

const char * FileException :: what () const throw(){
    return "ERROR: The file does not exists or it cannot be found.";
};

NumInsultsOutOfBounds :: NumInsultsOutOfBounds(int numberInsults){
    // take in the number of insults they want generated, and convert it to a string as well
    // to print an error message if an exception is thrown
    errorMessage = string("The number of insults you want generated ( " + to_string(numberInsults) + " ), is not within 0 and 10 000 insults");
}

const char * NumInsultsOutOfBounds :: what () const throw (){
    // built in function which will return a pointer to the errorMessage to print
    return errorMessage.c_str();
}