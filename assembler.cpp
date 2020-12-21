#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <iomanip>
using namespace std;
bool dec2bin(int , char *,int );
int asm_to_bin(const char* asm_file, const char* bin_file);
void covert_hex(const char* in_text_file_bin, const char* out_text_file_hex);
int chrcnt(char [],int,char);

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		asm_to_bin("test.asm", "out_bin.txt");
		covert_hex("out_bin.txt", "out_hex.txt");
	}
	else if (argc == 2)
	{
		asm_to_bin(argv[1], "out_bin.txt");
		covert_hex("out_bin.txt", "out_hex.txt");
	}
	else if (argc == 3)
	{
		asm_to_bin(argv[1], "out_bin.txt");
		covert_hex("out_bin.txt", argv[2]);
	}
	else if (argc == 4)
	{
		asm_to_bin(argv[1], argv[2]);
		covert_hex(argv[2], argv[3]);
	}
	else
	{
		cout << "Program takes at max three arguments" << endl;
	}


}

int asm_to_bin(const char* asm_file, const char* bin_file)
{
	/*char * add 		= 	"ADD"	;		//ADD two register and store in other register	
	char * sub 		= 	"SUB"	;		//SUBTRACT two register and store in other register			
	char * mul 		= 	"MUL"	;		//MULTIPLY two register and store in other register	
	char * and 		= 	"NAND"	;		//bitwise NAND two register and store in other register	
	char * lw 		= 	"LW"	;		//LOAD data from memory to register
	char * sw		= 	"SW"	;		//STORE data from register
	char * brz 		= 	"BRZ"	;		//Branch if register0 is zero 
	char * brn 		= 	"BRN"	;		//Branch if register0 is not zero  
	char * j 		= 	"J"		;		//JUMP to an offset relative to PC  
	char * jr 		= 	"JR"	;		//JUMP to an address in a register
	char * jal 		= 	"JAL"	;		//JUMP and Link: Jump to an offset relative to PC and save PC to return address register (RA) 
	char * addi 	= 	"ADDI"	;		//Add immediate value in a register value 
	char * lwr		= 	"LWR"	;		//LOAD from data memory. The data memory address is Source Register+Offset and the data from memory is written in a Destination register
	char * swr 		= 	"SWR"	;		//STORE into data memory. The data from Source Register is written at Data memory address calculated by  Destination Register+Offset 
	char * lui 		= 	"LUI"	;		//Load lower immediate: Load 16 bits into LSBs of a register
	char * lli 		= 	"LLI"	;		//Load upper immediate: Load 16 bits into MSBs of a register 
	*/
	const char * opcode [16] = {"ADD","SUB","MUL","NAND","LW","SW","BRZ","BRN","J","JR","JAL","ADDI","LWR","SWR","LLI","LUI"};
	char str[20];
	int len;
	int num;
	char * pch;
	char * pars[4];
	int i =0;
	int right_op;
	int val;
	char temp[3];
	int size_5 = 5;
	char * binary_5 = new char[size_5+1];
	for (int k = 0;k<=size_5;k++)
		binary_5[k] = '0';
	char * binary_5_op = new char[size_5+1];
	for (int k = 0;k<=size_5;k++)
		binary_5_op[k] = '0';
	int size_17 = 17;
	char * binary_17 = new char[size_17+1];
	for (int k = 0;k<=size_17;k++)
		binary_17[k] = '0';	
	int size_27 = 27;
	char * binary_27 = new char[size_27+1];
	for (int k = 0;k<=size_27;k++)
		binary_27[k] = '0';
	int size_22 = 22;
	char * binary_22 = new char[size_22+1];
	for (int k = 0;k<=size_22;k++)
		binary_22[k] = '0';

	ifstream read(asm_file,ios::in);
	ofstream output(bin_file,ios::out);
//	ifstream read("test.asm", ios::in);
//	ofstream output("output.txt", ios::out);
	if (!read)
	{
		cout<<"ERROR"<<endl;
	}
	if (!output)
	{
		cout<<"ERROR"<<endl;
	}
	while ( read.getline(str,20))
	{
		i = 0;
		len = strlen(str);
		if (str[len-1]==';')
		{
			num = chrcnt(str,len, ',');
			pch = strtok(str," ,");
			while (pch!=NULL)
			{
				//cout<<pch<<endl;
				pars[i++] = pch;
				pch = strtok(NULL," ,;");
			}
			//convert opcode to 5 bit binary number
			for (int j = 0 ; j<=15 ; j++)
			{
				if (!strcmp(pars[0], opcode[j]))
				{
					dec2bin(j,binary_5_op,size_5);
					cout << setw(6) << pars[0]<<" | "<<binary_5_op<<"_";
					output<<binary_5_op;
					right_op =1;
					break;
				}
				else
					right_op = 0;
			}
			if (right_op)
			{
				if (num == 0 && (strcmp(pars[0],"J")==0||strcmp(pars[0],"JR")==0||strcmp(pars[0],"JAL")==0||strcmp(pars[0],"BRZ")==0||strcmp(pars[0],"BRN")==0))
				{
					if (strcmp(pars[0],"JR")==0)
					{
						cout<<"00000_";
						output<<"00000";
	
						if (pars[1][0] == 'r')
						{
							for (int l= 0;l<3;l++)
								temp[l] = pars[1][l+1];
							val = atoi(temp);
							if (val <= 31)
							{
								dec2bin(val,binary_5,size_5);
								cout<<binary_5<<"00000000000000000"<<endl;
								output<<binary_5<<"00000000000000000";
							}
							else
							{
								cout<<endl;
								cout<<"REGISTRE NUMBER EXCEEDS"<<endl;
								output<<"\nREGISTRE NUMBER EXCEEDS"<<endl;
								break;
							}
						}
						else
						{
						cout<<endl;
						cout<<"WRONG INSTRUCTION: WITHOUT 'R' "<<endl;
						output<<"\nWRONG INSTRUCTION: WITHOUT 'R' "<<endl;
						}
					}
					else
					{
						val = atoi(pars[1]);
						dec2bin(val,binary_27,size_27);
						cout<<binary_27<<endl;
						output<<binary_27;
					}
					
					
				}
				else 
				if (num == 1 && (strcmp(pars[0],"LW")==0||strcmp(pars[0],"SW")==0||strcmp(pars[0],"LLI")==0||strcmp(pars[0],"LUI")==0))
				{

					if (strcmp(pars[0],"SW")==0)
					{
						cout<<"00000_";
						output<<"00000";
					}
					else ;

					if (pars[1][0] == 'r')
					{
						for (int l= 0;l<3;l++)
							temp[l] = pars[1][l+1];
						val = atoi(temp);
						if (val <= 31)
						{
							dec2bin(val,binary_5,size_5);
							cout<<binary_5<<"_";
							output<<binary_5;
						}
						else
						{
							cout<<endl;
							cout<<"REGISTRE NUMBER EXCEEDS"<<endl;
							output<<"\nREGISTRE NUMBER EXCEEDS"<<endl;
							break;
						}
					}
					else
					{
					cout<<endl;
					cout<<"WRONG INSTRUCTION: WITHOUT 'R' "<<endl;
					output<<"\nWRONG INSTRUCTION: WITHOUT 'R' "<<endl;
					break;
					}
					if (strcmp(pars[0],"LW")==0){
						cout<<"00000_";
						output<<"00000";
					}
					else ;
					if ((strcmp(pars[0],"SW")==0)||(strcmp(pars[0],"LW")==0))
					{
						val = atoi(pars[2]);
						dec2bin(val,binary_17,size_17);
						cout<<binary_17<<endl;
						output<<binary_17;
					}
					else
					if ((strcmp(pars[0],"LLI")==0)||(strcmp(pars[0],"LUI")==0))
					{
						val = atoi(pars[2]);
						dec2bin(val,binary_22,size_22);
						cout<<binary_22<<endl;
						output<<binary_22;
					}
				}
				else 
				if (num == 2 && (strcmp(pars[0],"ADD")==0||strcmp(pars[0],"SUB")==0||strcmp(pars[0],"MUL")==0||strcmp(pars[0],"NAND")==0||strcmp(pars[0],"ADDI")==0||strcmp(pars[0],"SWR")==0||strcmp(pars[0],"LWR")==0))
				{
					for (int j = 1;j<=3;j++)
					{
						if (pars[j][0]== 'r')
						{
							for (int l= 0;l<3;l++)
								temp[l] = pars[j][l+1];
							val = atoi(temp);
							if (val <= 31)
							{
								dec2bin(val,binary_5,size_5);
								cout<<binary_5<<"_";
								output<<binary_5;
								for (int k = 0; k<6; k++)
								binary_5[k] = '0';
							}
							else
							{
								cout<<endl;
								cout<<"REGISTRE NUMBER EXCEEDS"<<endl;
								output<<"\nREGISTRE NUMBER EXCEEDS"<<endl;
								break;
							}
						}
						else if (j == 3 && (!strcmp(pars[0],"ADDI")||!strcmp(pars[0],"SWR")||!strcmp(pars[0],"LWR")))
						{
							val = atoi(pars[3]);
							dec2bin(val,binary_17,size_17);
							cout<<binary_17;
							output<<binary_17;
						}
						else
						{
							cout<<endl;
							cout<<"WRONG INSTRUCTION: WITHOUT 'R' "<<endl;
							output<<"\nWRONG INSTRUCTION: WITHOUT 'R' "<<endl;
							break;
						}
						
					}
					if ((strcmp(pars[0],"ADD")==0||strcmp(pars[0],"SUB")==0||strcmp(pars[0],"MUL")==0||strcmp(pars[0],"NAND")==0))
					{
						cout<<"000000000000";
						output<<"000000000000";
					}
					cout<<endl;
				}
			
				//cout<<endl;
			
				////////
				for (int k = 0;k<=size_5;k++)
					binary_5[k] = '0';
				for (int k = 0;k<=size_5;k++)
					binary_5_op[k] = '0';
				for (int k = 0; k<=size_17; k++)
					binary_17[k] = '0';
				for (int k = 0; k<=size_27; k++)
					binary_27[k] = '0';
				for (int k = 0;k<4;k++)
					pars[k] = NULL;
			}
			else
			{
				cout<<"Wrong OPCODE"<<endl<<endl;
				output<<"WRONG OPCODE";
			}
		}
		else
			cout<<"WRONG INSTRUCTION: WITHOUT ENDING ; "<<endl;
		output<<endl;
	}
	cout << "\n*Binary output written to " << bin_file << endl << endl;
	return 0;
}
	
int chrcnt(char str[],int length,char delim)
{
	int cont = 0;
	for (int i=0;i<length;i++)
	{
		if (str[i] == delim)
		{
			cont ++;
		}
	}
	return cont;
}
bool dec2bin(int decimal, char *binary,int num)
{
  int  k = 0, n = 0;
  int  neg_flag = 0;
  int  remain;
  int  old_decimal;  // for test
  
  
  char * temp = new char[num+1];	
  char * binary1 =new char [num+1];
  for (int i = 0;i<=num;i++)
	  temp[i] = '0';
  temp[num+1] = 0;
  if (decimal < 0 )//|| decimal > (double)pow((double)2,(double)num))
  {      
	  return 0;
  }
 
	  do 
	  {
		old_decimal = decimal;   // for test
		remain    = decimal % 2;
		// whittle down the decimal number
		decimal   = decimal / 2;
		// this is a test to show the action
	   // printf("%d/2 = %d  remainder = %d\n", old_decimal, decimal, remain);
		// converts digit 0 or 1 to character '0' or '1'
		temp[k++] = remain + '0';
	  } while (decimal > 0 );
	 
	  while (k >= 0)
		binary1[n++] = temp[--k];
	 
	  binary1[n-1] = 0;         // end with NULL
	  int len = strlen(binary1);
	  for (int j = 0; j<len; j++)
		  binary[j+(num - len )] = binary1[j];

	  binary[num] = 0;
  return 1;
  
}

char bin2hex (char arr[5])
{
	if (strcmp(arr,"0000") == 0)
		return '0';
	else if (strcmp(arr,"0001") == 0)
		return '1';
	else if (strcmp(arr,"0010") == 0)
		return '2';
	else if (strcmp(arr,"0011") == 0)
		return '3';
	else if (strcmp(arr,"0100") == 0)
		return '4';
	else if (strcmp(arr,"0101") == 0)
		return '5';
	else if (strcmp(arr,"0110") == 0)
		return '6';
	else if (strcmp(arr,"0111") == 0)
		return '7';
	else if (strcmp(arr,"1000") == 0)
		return '8';
	else if (strcmp(arr,"1001") == 0)
		return '9';
	else if (strcmp(arr,"1010") == 0)
		return 'A';
	else if (strcmp(arr,"1011") == 0)
		return 'B';
	else if (strcmp(arr,"1100") == 0)
		return 'C';
	else if (strcmp(arr,"1101") == 0)
		return 'D';
	else if (strcmp(arr,"1110") == 0)
		return 'E';
	else if (strcmp(arr,"1111") == 0)
		return 'F';
	else	cout<<"Not binary"<<endl;

}

void covert_hex(const char* in_text_file_bin, const char* out_text_file_hex)
{
//	ifstream binary("output.txt", ios::in);
//	ofstream out_hex("out_hex.txt", ios::out);
	ifstream binary(in_text_file_bin, ios::in);
	ofstream out_hex(out_text_file_hex, ios::out);
	if (!out_hex)
	{
		cout << "No file " << endl;
		return;
	}
	if (!binary)
	{
		cout << "No file " << endl;
		return;
	}
	char str[33];
	char brak[8][5];
	char hex[9];
	while (binary.getline(str, 33))
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				brak[i][j] = str[(i * 4) + j];
				cout << brak[i][j];
			}
			brak[i][4] = 0;
		}
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				hex[i] = bin2hex(brak[i]);
			}
		}
		hex[8] = NULL;
		cout << " | " << hex;
		out_hex << hex << endl;
		cout << endl;
	}
	cout << "\n*Hex output written to " << out_text_file_hex << endl;


}
