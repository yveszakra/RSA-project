/*
*  RSA PROGRAM
*  CREATED BY 
*  Tyler Lewis, Thomas Tran, Sagar Shahi, Yves Zakra, Joseph Winker
*
*  Use:  g++ -std=c++11 main.cpp RSA.cpp to compile
*/

#include <iostream>
#include <string>
#include <numeric>
#include <math.h>
#include <chrono>
#include <stdio.h>
#include <streambuf>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <math.h> 
#include <fstream>

#include "InfInt.h"
#include "RSA.h"

using namespace std; 


/* PROTOTYPE DECLARATIONS */


/*@param int a, int b, int c
* @post concatenates 3 integers like: 1,1,4 into one: 114
* @returns an integer value */
int concatenate(int a, int b, int c) ;


/*@param vector<InfInt> &storage
* @post parses msg.txt and stores ASCII values of 3 letters into blocks
* @returns a vector of InfInt */
vector<InfInt> generateBlocks(vector<InfInt> &storage);


// Driver program 
int main() 
{ 

  //to help with timing the program time..
  using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;
	using std::chrono::milliseconds;


  vector<InfInt> blocks; // vector to store the plaintext into blocks
  generateBlocks(blocks); // function to get plaintext from .txt file
  
  
  cout << endl << "RSA Program" <<endl;
  cout << "This program will encrypt and decrypt messages from msg.txt"<<endl;
  cout << "It will also generate prime numbers of inputted length" << endl;
  cout << "digits between 70-100 may take a few minutes!" << endl;
  cout << "-------------------------------------------------" << endl;
  cout << endl << "enter prime number length: ";
  int length = 2;
  cin >> length;
  cout << endl;
  

  auto start = chrono::high_resolution_clock::now(); // start time

  RSA t(length, blocks);

	t.generatePrimes();
	t.generateKey();
  auto startEncrypt = chrono::high_resolution_clock::now();// start Encryption time 
	t.EncryptMessage();
  auto stopEncrypt = chrono::high_resolution_clock::now();// stop Encryption time 

  auto startDecrypt = chrono::high_resolution_clock::now();// start Decryption time 
	t.DecryptMessage();
  auto stopDecrypt = chrono::high_resolution_clock::now();// stop Decryption time

  cout << "-------------------------------------------------" << endl;



  auto stop = chrono::high_resolution_clock::now(); // stop time
	auto time = duration_cast<milliseconds>(stop - start); // total time = stop - start
	cout << "Total Time: "<< time.count() << " ms" << endl;

  auto encryptTime = duration_cast<milliseconds>(stopEncrypt - startEncrypt);
  cout << "Encryption Time: " << encryptTime.count() << " ms" << endl;

  auto decryptTime = duration_cast<milliseconds>(stopDecrypt - startDecrypt);
  cout << "Decryption Time: " << decryptTime.count() << " ms" << endl;
  
  
    return 0; 
} //end of main

int concatenate(int a, int b, int c) 
{ 
  
  // Convert both the integers to string 
  string s1 = to_string(a); 
  string s2 = to_string(b); 
  string s3 = to_string(c);
  
  // Concatenate both strings 
  string string_cat = s1 + s2 + s3; 
  
  // Convert the concatenated string 
  // to integer 
  int cat = stoi(string_cat); 
  
  // return the formed integer 
  return cat;
} //end of concatenate

vector<InfInt> generateBlocks(vector<InfInt> &storage)
{
  string a;
  int i = 0;
 
  std::ifstream t("msg.txt");
  std::stringstream buffer; // textfile data stored in here
  buffer << t.rdbuf(); // read textfile into buffer

  a = buffer.str(); // convert buffer to an actual string
  vector<string> letterBlocks; // vector to store blocks of 3 letters
 
  //substr(pos,length) 
  // IE string = "hello" 
  // cout << hello.substr(0,2) ----> would output "he"

  for(int i = 0; i < (a.length()); i++)
  {
    if(a.length() - i >= 3)
    {
      letterBlocks.push_back(a.substr(i,3)); // push 3 letters into h
      
      i++;
      i++;
    }
    else if(a.length() - i == 2)
    {
      letterBlocks.push_back(a.substr(i,2) + " "); // + a space to make sure message is 2 --> 3 bytes
      
      i++;
    }
    else if(a.length() - i == 1)
    {
      letterBlocks.push_back(a.substr(i,1)+ "  "); // + a two spaces to make sure message is 1 --> 3 bytes
    }
  }

  for(int i = 0; i < letterBlocks.size(); i ++) //convert each element of letterblock to char to Int
  {
    int convert = letterBlocks[i][0];  //[string][characterOFstring]
    int convert1 = letterBlocks[i][1]; 
    int convert2 = letterBlocks[i][2]; 

    // to concatenate 3 characters into ASCII codes
    // IE AAA ---> 656565
    storage.push_back(concatenate(convert, convert1, convert2)); 

   }

  return storage;
} //end of generateBlocks