#ifndef RSA_H
#define RSA_H

#include <vector>
#include <iostream> 

#include "InfInt.h"

class RSA
{
  private:

    /* private instance variables */
    /*----------------------------*/
    int length = 0; // to store the prime number length

    InfInt p; // 1st prime
    InfInt q; // 2nd prime

    InfInt mod; // (p * q)
    InfInt eulerTotient; // (p-1) * (q - 1)

    std::vector<InfInt> blocks; // where 3 letter parsed blocked are stored as numbers/InfInt

    InfInt e = 7; // default public key of prime number: 7
    InfInt d; // private key
	
  public:
  
    /* Constructor for RSA */
    RSA(int primeLength,std::vector<InfInt> vec);
   

    /* public member functions */


    /*@param none
    * @pre none
    * @post generates two prime numbers for RSA calculations
    * @return none  */
    void generatePrimes();


    /*@param none
    * @pre generatePrimes() must be ran first
    * @post generates the private key for RSA encryption
    * @return none  */ 
    void generateKey();


    /*@param none
    * @pre generateKey() must be be ran first
    * @post encrypt the blocks that are in vector: blocks
    * @returns none */
    void EncryptMessage();


    /*@param none
    * @pre EncryptMessage();
    * @post decrypts each message from the blocks.
    * @returns none */
    void DecryptMessage();
    

    /*@param string and string.length();
    * @post displays a string containing ASCII values
    * @returns none */
    void asciiToPrint(std::string temp, int stringLength);


    /*@param (d = number to test,n = number of iterations for accuracy)
    * @pre non negative input
    * @post Evaluates a user specified prime number
    * @returns a boolean value 0/1 T/F */
    bool miillerTest(InfInt d, InfInt n);
    

    /*@param none
    * @pre none
    * @post Evaluates the users expression and displays it to the User
    * @returns a boolean value 0/1 T/F */
    bool isPrime(InfInt n, int k);


    /*@param InfInt A and InfInt B
    * @post finds the GCD between two InfInts
    * @returns an InfInt value */
    InfInt gcd(InfInt a, InfInt b);


    /*@param InfInt publicKey, InfInt mod
    * @post Evaluates D by using the theorem D = e^-1 % totient
    * @returns an InfInt value */
    InfInt modInverse(InfInt public_key, InfInt modNumber); 


    /*@param InfInt base, InfInt exponent, InfInt modulus
    * @post Evalutes equations that are in the form (a^b) % c very quickly
    * @returns an InfInt value */
    InfInt modular_exp(InfInt base, InfInt exponent, InfInt modulus);


    /*@param integer max_length
    * @post calculates a random number using the MT19937 generator
    * @returns an InfInt value */
    InfInt numberGen(int max_length);
    
};
#endif