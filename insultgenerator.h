#include <string>
#include <vector>

using namespace std;

class FileException {
public:                                                                 // access specifier
    FileException();                                                    // constructor
    const char * what () const throw();                                 // error from thrown Exception
};

class NumInsultsOutOfBounds : public exception{
public:
    const char * what () const throw();                                 // error from thrown Exception
    
    NumInsultsOutOfBounds(int numberInsults);                           // this will take in number of insults to be generated and throw exception if too high or low
    
private:
    string errorMessage;                                                // the message that the exception will display if out of bounds

};

class InsultGenerator{
public:
    InsultGenerator();                                                  // constructor

    void initialize();                                                  // initialize method of InsultGenerator which doesn't return anything
    string talkToMe();                                                  // talkToMe method of InsultGenerator which returns a single string of an insult
    vector<string> generate(int numberInsults);                         // generate method which takes in a number of insults and will return a vector of insult strings which can vary in size
    void generateAndSave(string writtenFilename, int numberInsults);    // take in the name of the file to save the insults generated in this method to that file

    bool writtenFileExistsCheck(const string& filename);                 // check if the SavedInsults.txt file even exists before writing into the file
    
private:
    // when the InsultsSouce.txt file is read, there must be three columns of insults split up 
    // the vectors must be able to be used in more than one method in insult generator 
    vector<string> column1;
    vector<string> column2;
    vector<string> column3;
};