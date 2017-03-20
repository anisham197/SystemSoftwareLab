#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <bitset>

using namespace std;

/* File does not have length of text record before bit mask,
File has only 3 byte object codes
To calculate increment need new - current start address ? */

class p1 {

 	string new_addr;

	public:

  	void enterAddr()
  	{
    		cout << "Enter the actual starting address" << endl;
    		cin >> new_addr;
  	}

	void parseInput()
	{

		fstream input_file, output_file;
		string line, addr, bitmask, binary;
		char cbuff[100], hex_loc[4], hex_opcode[7];
    		int loc, bm, inc, new_loc;

		// Open files
		input_file.open("load_input.txt", ios::in );
		output_file.open("reloc_loader_output.txt", ios::out | ios::app);

		// Read input file till end
		while ( getline(input_file, line) )
		{
			// Clears cbuff from previous input
			memset(&cbuff, 0, sizeof(cbuff));

			// Copies input line to cbuff(char array)
			strcpy(cbuff, line.c_str());

      			// Checks for header record
      			if(cbuff[0] == 'H')
        			continue;

			// Checks for end record
      			if ( cbuff[0] == 'E')
        			break;

			// Retrieves starting address from text record, converts to int
      			addr = line.substr(3,4);
      			loc = strtol(addr.c_str(), NULL, 16);

			// Convert new starting address to int            		
			inc = strtol(new_addr.c_str(), NULL, 16);

			//  Calculate locaton properly          		
			new_loc = loc + inc;

            		bitmask = line.substr(7, 3);
            		bm = strtol(bitmask.c_str(), NULL, 16);
            		binary = bitset<12>(bm).to_string(); //to binary

			// Iterates through object code bytes of text record
            		int count = 0;
            		int i;
      			for ( i = 10; cbuff[i] != '\0'; i = i+6 )
      			{
                		sprintf(hex_loc, "%X", new_loc);
                		if ( binary[count] == '0' )
                		{
                    			output_file << hex_loc <<"\t"<<cbuff[i]<<cbuff[i+1]<<cbuff[i+2]<<cbuff[i+3]<<cbuff[i+4]<<cbuff[i+5]<<endl;
                		}
                		else
                		{
                  			string temp = cbuff;
                  			temp = temp.substr(i,6);

                  			int temp_opcode = strtol(temp.c_str(), NULL, 16);
                  			temp_opcode += inc;

                  			sprintf(hex_opcode, "%X", temp_opcode);
                  			output_file << hex_loc <<"\t" << hex_opcode << endl;

                		}

          			new_loc = new_loc + 3;
                		count++;
      			}

    		}
  	}
};

int main ()
{
	p1 obj;
  	obj.enterAddr();
	obj.parseInput();
}
