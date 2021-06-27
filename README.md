The main goal for our project is to demonstrate our understanding of RSA. We are analyzing the resistance of RSA to cryptanalytic attacks. Our implementation of the RSA program is written in C++. The program consists of finding two large (at least 100 digits) prime numbers p and q to generate the modulus for RSA. Those prime numbers are verified before being used in the necessary computations. Once this is done, we proceed with the encryption of a message contained in a text file. After the message is encrypted, the decryption of the cypher text follows. Thus, the implementation of the RSA is completed.

I. INTRODUCTION
Introduced in the late 1970’s by Rivest, Shamir, and Adleman, the RSA encryption algorithm provided a way to securely transmit messages electronically. This algorithm shortly became one of the most popular encryption methods used in modern technology. 

The RSA algorithm is an asymmetric cryptographic algorithm; meaning there are two different keys. These keys are a public key and a private key. The public key can be known by anyone and used to encrypt messages. These encrypted messages can then be decrypted using the private key. 

The keys are generated using the following method:
1.	Coming up with two different large prime numbers labeled p and q
2.	Calculating n = p*q
3.	Calculating totient Φ(n) = (p-1) (q-1)
4.	Choosing an integer e where 1<e<Φ(n), and the greatest common denominator between e and Φ(n) is 1. The public key will then be (n, e)
5.	Calculate private key d, such that 
 e*d = 1 mod (p-1) (q-1)

Encrypting a plaintext message is done by using the public key (n, e) and the following formula:
Encrypted Message = Pe mod n
Where P is the plaintext message.

To decrypt a message a user would need a private key d and the following formula:
P = (Encrypted Message) * d mod n

With this knowledge, the research group implemented the RSA algorithm in a C++ program.



II. RSA IMPLEMENTATION DETAILS
The implementation of the RSA algorithm is divided into 4 main sections: Key Generation, Encryption, Decryption, Tester/Main. Each section was created by different individuals and combined together to function as a RSA algorithm. 
RSA key generation:
Implement RSA using C/C++. You will need to find two large (at least 100 digit) prime numbers p and q to generate the modulus for RSA. The following processes are required:
·        GenerateKey - Generate RSA public and secret keys, using a 100 decimal digit prime number generator.
o   You must determine two primes at random p, q and select either e or d and compute the other.
§ You need to do a research about how to determine a prime. One suggestion is to use Miller-Rabin method, which is typically guess using probabilistic test.
§ Exponents e, d  are inverses, so you need to select an algorithm to compute the multiplicative inverse of the other. One suggestion is to use Extended Euclid’s algorithm.
Note: e and d are multiplicative inverse if.
 
 
The first part of our RSA project is the “generateKey”. The “generateKey” first generates the RSA public and secret keys using a 100 decimal digit prime number. In order to generate numbers with 100 decimal digits, we used a public library called InfInt. It is a header file that is simply included in our generateKey program. InfInt takes a string containing a very large number that is then converted into an integer.
#1 – The function “ InfInt generate(int max_length) “
Max_length parameter specifies the number of digits that will be produced (100 in our case, or more). The function picks a random integer (from 0 to 9 included) inside a string, then stores it in a different string that concatenates every new character (integer). This process is repeated max_length time (100 times).
The generate function is used to randomly determine our prime numbers p and q. The next step is to check for primality.
 
#2 – isPrime(InfInt n, int k) / millerTest(InfInt d, InfInt n )
We are using the Miller-Rabin method here. It uses guess probabilistic test. We are using an algorithm from the forum geeks for geeks which we slightly modified. We changed the data types (int to InfInt) and created some variables that will contains some small integer that will be considered big integers. The millerTest() function is called for all k trials. It returns false if n is composite and returns false if n is probably prime; d is an odd number such that d*2^r = n-1 for some r >= 1. This function will be then called in the isPrime() function. isPrime() returns false if n is composite and returns true if n is probably prime.  k is an input parameter that determines accuracy level. Higher value of k indicates more accuracy.
#3 – modInverse(int a, int m)
Returns modulo inverse of a with respect to m using extended Euclid Algorithm Assumption: a and m are coprimes, i.e., gcd(a, m) = 1
RSA Encryption:
The encryption starts by reading from the message file 3 characters at a time and placing them in an array of length 3. Once the array is filled it calls getTrigraph() which takes the string of plain text character and it converts those characters into the ASCII value and subtracts a number to convert them to the appropriate letter place. Then it uses the formula (First Letter Code) * 262 + (Second Letter Code) * 26 + (Third Letter code) to convert it into the trigraph integer. Then the trigraph is sent to encipherCode() which take the trigraph code and raises it to the public key and then it divides the resulting number by the modulo and takes the remainder as the enciphered code. Then GetQuadrigraph() divides the enciphered text code by 26^3 and then uses the reminder to divide by 26^2 and finally using the remainder to divide by 26. Taking the initial division number and the final remainder we get the quadragraph. Once the quadragraph has been calculated it adds the 4 characters to the cipher text string and continues till there is no characters left in the file.
RSA Decryption:
·        Decrypt - Take a ciphertext and perform RSA decrypt on it.
o   How do you decrypt the encrypted file? This procedure is the exact reverse of the encryption procedure.  As in LAB 1, you will read from the encrypted file in blocks of 4 bytes, with each set of 4 bytes forming an encrypted number. The RSA decryption algorithm specifies how to decrypt an encrypted number. This will give you the number that was formed from the original plaintext file. Now, remember that this number was formed by concatenating 3 bytes from the plain text file. To get back those 3 bytes from this number, you will have to pick out the lower order 3 bytes from this number and write them out in order to the output file.
 
The third part of our RSA project is the “decrypt”. The “decrypt” deciphers the blocks of ciphertext and displays them to the user via the console.
#1 – The function “void RSA::DecryptMessage()“
DecryptMessage is a member function that is ran in main.cpp and this function decrypts 3 letter blocks of ciphertext that are stored in an InfInt vector. We decipher each block one by one using modular exponentiation. Then once each block is deciphered it is still in decimal form as concatenated ASCII values. The blocks of ASCII values are stored as numbers then are converted to characters and then are printed out to the user.
 
#2 – The function “InfInt RSA::modular_exp(InfInt base, InfInt exponent, InfInt modulus)“
In this function the ciphertext block is passed as the base, the private key as the exponent, and the mod A.K.A (p*q) is passed as modulus. This function returns the plaintext as numbers/InfInt to which we can convert to characters to retrieve the original plaintext from the msg.txt file.
#3 – void RSA::asciiToPrint(std::string temp, int stringLength);
This function takes a concatenated string of all the plaintext text blocks that are deciphered from the modular exponentiation phase of decryptMessage and the length of that concatenated string. The string contains ASCII value in numeric form, but since a string is a character array… we can scan the array and convert the ASCII values in that string to actual characters. Then all those converted characters are outputted to the console.
