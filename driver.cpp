//Name: Coleman Johnston
//Date: 20 Oct. 2015
//Description: Programming Practice- File IO A
#include<iostream>//cout 
#include<cstdlib>//toupper()
#include<fstream>//file IO
#include<string>//string processing
#include<cassert>//testing
using namespace std;

//*********************************************************************
int avgChars(string inFile);
//Description: A function to count the average number of characters 
//per word in a .txt file
//Precondition: The name of an input file to take in.
//Postconditon: returns the average characters per word in a file. 
//*********************************************************************

//*********************************************************************
int countWords(string inFile);
//Description: A function that counts the total number of words
//Precondition: The name of an input file to take in.
//Postcondition: returns the number of words in a file
//*********************************************************************

//*********************************************************************
string trimStr(string str);
//Description: A function that trims all non-letters off of a string
//Precondition: A string with characters in it.
//Postcondition: A string  with only letters.
//*********************************************************************

//*********************************************************************
int findNumLetters(string inFile, int lenLook);
//Description: A function the amount of words of a specified length.
//Precondition: The name of an existing file. And a specified length.
//Postcondition: returns the number of times words of a given length
//appear in a file.
//*********************************************************************

//*********************************************************************
void allCaps(string inFile, string outFile);
//Description: A function that turns all the letters in a file capital.
//Precondition: Takes in the name of both an input and an output file.
//Postcondition: Outputs a version of the input file that is all capital
//letters to the output file.

//***********************************************************************
void upperFirst(string inFile, string outFile);
//Description: A function that turns the first letter of all the words in
//a file to capital.
//Precondition: Takes in the name of both an input and an output file.
//Postcondition Outputs a version of the input file which has the first 
//letter of every word capitalied.
//************************************************************************

int main()
{
    string ifName = "gba.txt";
    string CapOFName = "capitalize.txt";
    string upOFName = "uppercase.txt";
    int numA;//general purpose number variable
    int tenOrLess = 0;//the total number of words with a length <= 10 
    ofstream fout;
    fout.open("result.txt");
    
    fout << "Average characters per word: " << avgChars(ifName) << endl;
    
    for(int i = 1; i < 11; i++)//find the total words in the file with i letters.
    {
        numA = findNumLetters(ifName,i);
        fout << numA << " words of length " << i << endl;    
        tenOrLess += numA;//add to the count of words with less than eleven letters.
    }
    
    //deduct the words of less than than eleven letters from the total words to get the amount of
    //words with 11 or more letters. 
    fout << countWords(ifName) - tenOrLess << " words of length 11 or longer" << endl;     
    fout << "Total number of words in " << ifName << ": " << countWords(ifName) << endl;
    allCaps(ifName,CapOFName);//write the file in all caps to another file.
    upperFirst(ifName,upOFName);//write the file with each first letter capital to another file.
    
    fout.close();
    return 0;
}

int avgChars(string inFile)
{
    ifstream fin;//declare file stream
    fin.open(inFile.c_str());//open the file with the name passed from the main
    
    if(fin.fail())//error checking
    {
        cout << "error opening input file." << endl;
        exit(1);
    }
    
    char ch;
    int totalCh = 0;//total characters in the file
    int avg;
   
    while(fin >> ch)//run to the end of the file
    {
        if(toupper(ch) >='A' && toupper(ch) <= 'Z')
        {
            totalCh++;
        }
  
    }
    fin.close();//close file stream
    avg = totalCh / countWords(inFile);//find the average letters per word
    
    //fix int division errors 
    if(((totalCh % countWords(inFile)) * 2) >= totalCh)
    {
        avg++;
    } 
       
    return avg;
}

int countWords(string inFile)
{
    ifstream fin;//declare file stream
    fin.open(inFile.c_str());//open the file with the name passed to the function
    int words = 0;//number of words in the file
    bool isWord;
    string str;
    
    if(fin.fail())//error checking
    {
        cout << "error opening input file." << endl;
        exit(1);
    }
    
    while(fin >> str)//run to the end of the file
    {
        isWord = false;//initialize to false
        for (int i = 0; i < str.length(); i++)
        {
            if(toupper(str[i]) >= 'A' && toupper(str[i]) <= 'Z')
            {
            isWord = true;//if a string has a letter it is a word
            break;//break once you find a letter
            }
        }
        if(isWord)
        {
            words++;//if the string read in is a word add one to the word count
        }//end for that checks for letter in a string
    }//end while reading from file
          
    fin.close();//close the file stream
       
    return words;   
}

string trimStr(string str)
{
    for(int i = 0; i < str.length();i++)//read each character of the string
    {
        if (toupper(str[i]) < 'A' || toupper(str[i]) > 'Z')
            {
            str.erase(i,1);//erase non-letters
            i--;
            }
    }
    return str;   
}

int findNumLetters(string inFile, int lenLook)
{
    ifstream fin;//declare file stream
    fin.open(inFile.c_str());//open the file with the name passed to the function   
    string str;
    int count = 0;
    if(fin.fail())//error checking
    {
        cout << "error opening input file." << endl;
        exit(1);
    }   
    while(fin >> str)//read all strings in the file
    {
        str = trimStr(str);//trim off non letters
        if(str.length() == lenLook)
        {
            count++;//add one to the count if a word is the length we're looking for           
        }       
    }
    fin.close();//close file stream
    return count;
}

void allCaps(string inFile, string outFile)
{
    ifstream fin;//declare input file stream
    ofstream fout;//declare output file stream
    fin.open(inFile.c_str());//open input file stream
    fout.open(outFile.c_str());//open output file stream
    string str; 
    while(fin >> str)
    {
        for(int i = 0; i < str.length(); i++)
        {
            str[i] = toupper(str[i]);
        }
        fout << str << " ";
    }
    fin.close();//close input file stream
    fout.close();//close output file stream
}

void upperFirst(string inFile, string outFile)
{
    ifstream fin;//declare input file stream
    ofstream fout;//declare output file stream
    fin.open(inFile.c_str());//open input file stream
    fout.open(outFile.c_str());//open output file stream
    string str; 
    while(fin >> str)
    {
            str[0] = toupper(str[0]);//Make the first letter of every word capital.
        fout << str << " ";//add a space after every word
    }
    fin.close();//close input file stream
    fout.close();//close output file stream
}
