#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

//	-->	XOR a charachter
unsigned char XOR(unsigned char x){
	unsigned char KEY = 0xAA; // 10101010
	x = x ^ KEY; // Bitwise xor operator
	return x;
}

//	-->	Invert a character
unsigned char INV(unsigned char x){
	x = ~x; // Bitwise not operator
	return x;
}


//	-->	Takes a int number and returns a binary string
//		Useful for visualizing what the binary operation would look like
//		if your brain is short of RAM like myself
void toBinString(int number){
	string x;
	int p = 128;

	for(int i = 0; i < 8; i++){
		if(number >= p){
			x += '1';
			number -= p;
		}
		else{
			x += '0';
		}
		p /= 2;
		
	}
	cout << x << endl;
}

//	-->	Rotates the bits in an unsigned char to the left
//		doing a bitwise or on:
//		A: uchar shifted by n ||
//		B: uchar shifted by 8 - n
unsigned char ROTL (unsigned char x, unsigned int n){
	assert (n<8); //Check if n is smaller than 8, throw exception when it's not
	if (!n) return x;
	x = (x<<n) | (x>>(8-n));
	return x;
}

//	-->	Rotates the bits in an unsigned char to the right
//		same equation, but mirrored to have the opposite effect
unsigned char ROTR (unsigned char x, unsigned int n){
	assert (n<8);
	if (!n) return x;
	x = (x<<(8-n) | (x>>n));
	return x;
}

int main(int argc, char* argv[]){
	ifstream fs; // filestream reader
	ofstream out;
	out.open("output.txt", ios::out | ios::trunc | ios::binary); // output to binary
	

	
	//Open the file given as argument	
	try {
		fs.open(argv[1], fstream::in); // Read from the file given as an argument
	} catch(int e){
		cout << e << endl;
	}


	string output = "";
	string line;
	while(!fs.eof()){ //While not at the end of the file, do the following
		getline(fs, line);
		for(unsigned char c : line){ //Read every character from every line of text
			cout << c << endl;
			unsigned short counter = 2;
			while(counter != argc){
				switch(*argv[counter]){
				
					default:
						cout << "Unkown operation" << endl;
						break;

					case 'R' :
						c = ROTR(c, 1);
						cout << "Got ROTR" << endl;
						break;

					case 'L' :
						c = ROTL(c, 1);
						cout << "Got ROTL" << endl;
						break;

					case 'I' :
						c = INV(c);
						cout << "Got Inversion" << endl;
						break;
						
					case 'X' :
						c = XOR(c);
						cout << "Got XOR" << endl;
						break;
			}
			counter += 1;
		}
			out << c;
			output += c;
	}
}

	//See what the value of each character is doing after the encryption operations are done
	for(unsigned char c : output){
		toBinString((int)c);
		cout << (int)c << endl;
	}

	return 0;
}
