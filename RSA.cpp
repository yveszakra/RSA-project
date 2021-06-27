#include "RSA.h"


#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <vector>
#include <random>
#include <chrono>


using namespace std;

// constructor for now
RSA::RSA(int primeLength,std::vector<InfInt> vec) 
{
  blocks = vec;
  length = primeLength;

}


void RSA::generatePrimes()
{

  p = numberGen(length);
  q = numberGen(length);

  cout << "Generating primes please wait!" << endl;
 while(isPrime(p, 4) == false)
    {
        p = numberGen(length);
    }
  
  cout << "1st prime generated..." << endl;
  while(isPrime(q, 4) == false)
    {
        q = numberGen(length);
    }
  cout << "2nd prime generated..." << endl;
  
  eulerTotient = (p-1) * (q - 1);
  InfInt gcdE = e;
  InfInt gcdT = eulerTotient;


 if(gcd(gcdE,gcdT) == 1)
  {
  mod = p * q; //calculate p * q AKA mod
  eulerTotient = (p-1) * (q - 1);

  cout << endl << "Prime p =  " << endl << p << endl << endl;
  cout << "Prime q =  " << endl << q << endl << endl;
  cout << "mod  =  " << endl << mod << endl << endl;
  cout << "Eulers Totient = " << endl << eulerTotient << endl << endl;

 }
else
{
  cout << "GCD(e,totient) wasnt 1.. regenerating primes" <<endl;
  generatePrimes();
}

}


void RSA::generateKey()
{
	e = 7;
	d = modInverse(e, eulerTotient);

	cout << "public key e =  "  << endl << e << endl << endl;
	cout << "private key d =  " << endl << d << endl << endl;

}


void RSA::EncryptMessage()
{ 
  
  // for loop to encrypt each block
  cout << "Cipher text blocks in decimal seperated by commas : " <<endl;

  for(int i = 0; i < blocks.size(); i ++)
  {
    blocks[i] = modular_exp(blocks[i], e, mod);   
  }

  // cout blocks in their cipher text form
  for(int i = 0; i < blocks.size() -1; i ++)
  {
    cout << blocks[i] << ",";
  }

  cout << blocks[blocks.size() - 1]; // cout last block without comma

  cout <<endl;
}

void RSA::DecryptMessage()
{
  string temp; //help to convert int back to string

   // for loop to decrypt each block
   for(int i = 0; i < blocks.size(); i ++)
   {
    blocks[i] = modular_exp(blocks[i], d, mod);
    temp = temp + blocks[i].toString();
   }
    cout << endl << "Decoded Message: " <<endl;
    asciiToPrint(temp, temp.length()); // to function to convert ASCII string to characters

}


/* InfInt helper functions that will help with our RSA calculations */
InfInt RSA::modular_exp(InfInt base, InfInt exponent, InfInt modulus)
{
	if (modulus == 0) 
		return 0;     // Initialize result 

	base %= modulus;
	InfInt result = 1;


	while (exponent > 0)
	{
		if (exponent % 2 == 1)
			result = ((result * base) % modulus);
		base = ((base * base) % modulus);
			exponent /= 2;
			
	}
	
	return result;
}

InfInt RSA::modInverse(InfInt public_key, InfInt modNumber)
{
  InfInt m0 = modNumber;
	InfInt y = 0, x = 1;

	if (modNumber == 1)
		return 0;

	while (public_key > 1) {
		// q is quotient
		InfInt q = public_key / modNumber;
		InfInt t = modNumber;

		// m is remainder now, process same as
		// Euclid's algo
		modNumber = public_key % modNumber, public_key = t;
		t = y;

    /* continued */
		// Update y and x
		y = x - q * y;
		x = t;
	}

	// Make x positive
	if (x < 0)
		x += m0;

	return x;
}


bool RSA::isPrime(InfInt n, int k) 
{ 
    // Corner cases 
    if (n <= 1 || n == 4)  return false; 
    if (n <= 3) return true; 
  
    // Find r such that n = 2^d * r + 1 for some r >= 1 
    InfInt d = n - 1; 
    while (d % 2 == 0) 
        d /= 2; 
  
    // Iterate given nber of 'k' times 
    for (int i = 0; i < k; i++) 
    	if (!miillerTest(d, n)) 
            return false; 
  
    return true; 
}


bool RSA::miillerTest(InfInt d, InfInt n) 
{ 
    // Pick a random number in [2..n-2] 
    // Corner cases make sure that n > 4  
	//int a = 2 + rand() % (n - 4); 
  InfInt small1 = 2;
  InfInt small2 = 4;
	int ra = rand();
	string ra_str = to_string(ra);
	InfInt raBig = ra_str;
	InfInt a = small1 + raBig % (n - small2);
    //string a_str = to_string(a);
    //InfInt aBig = a_str;
    // Compute a^d % n 
    InfInt x = modular_exp(a, d, n);
   
    if (x == 1  || x == n-1) 
       return true; 
    // Keep squaring x while one of the following doesn't 
    // happen 
    // (i)   d does not reach n-1 
    // (ii)  (x^2) % n is not 1 
    // (iii) (x^2) % n is not n-1 
    while (d != n-1) 
    { 
        x = (x * x) % n; 
        d *= 2; 
        if (x == 1)      return false; 
        if (x == n-1)    return true; 
    } 
  
    // Return composite 
    return false; 
} 

InfInt RSA::gcd(InfInt a, InfInt b) 
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

void RSA::asciiToPrint(std::string temp, int stringLength)
{
    int num = 0;
    for (int i = 0; i < stringLength; i++) {
 
        // Append the current digit
        num = num * 10 + (temp[i] - '0');
 
        // Make sure ASCII values are within correct range
        if (num >= 32 && num <= 122) {
 
            // Convert number string to chararacter
            char ch = (char)num;
            cout << ch;
 
            // Reset num to 0
            num = 0;
        }
    }
    cout << endl;
}

InfInt RSA::numberGen(int max_length){
    string possible_characters = "0123456789";
    random_device rd;
    mt19937 engine(rd());
    uniform_int_distribution<> dist(0, possible_characters.size()-1);
    string ret = "";
    for(int i = 0; i < max_length; i++){
        int random_index = dist(engine); //get index between 0 and possible_characters.size()-1
        ret += possible_characters[random_index];
    }
    
    InfInt number = ret; //string to InfInt / bignumber

    if (number % 2 == 0)
      {
        return numberGen(max_length);
      }
    else
    {
      /* Gurantees that the returned number is odd! */
      return number;
    }

}