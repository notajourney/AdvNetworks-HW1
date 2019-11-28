#include "ip_file_handler.h"
using namespace std;
#include <fstream>

bool ip_file_handler::file_to_ip_packets(std::string input_file_name, std::string output_file_name, unsigned int source_ip, unsigned int destination_ip){

	const unsigned int FULL_SIZE = 256;
	const unsigned int HEADER_SIZE = 20;
	std::fstream fout;
	char* buffer= NULL;
	fout.open(output_file_name, ios::out | ios::binary);
	char* header_bytes = NULL;
	char* last_header_bytes = NULL;
	unsigned int file_length= read_file_to_buffer( buffer,input_file_name);


	if(file_length == 0)
	{
		cout<<"File: "<<input_file_name<<" is empty. ";
		cout<<"Nothing to do (or home exercise was not properly defined"<<endl;
		return false;
	}

	int full_packets_count = (file_length/FULL_SIZE);//Number of 256 Fragments
	if(file_length>=FULL_SIZE)

	{

		for(int i=0;  i<full_packets_count-1;  i++)//Happens only if file_size > 256
			//Loop writes only 256 fragments
		{
			if(i==0){
				TempIp header(source_ip, destination_ip,FULL_SIZE);
				header_bytes = header.get_header_as_bytes();
			}

			fout.write(header_bytes, HEADER_SIZE);
			fout.write(buffer+i*FULL_SIZE, FULL_SIZE);
		}
		delete []header_bytes;
	}//end if:file_length>=FULL_SIZE


	//calculate the number of bytes reminder
	int reminder_size = (file_length%FULL_SIZE);
	if(reminder_size > 0)//write reminding bytes if there are any
	{
		TempIp last_header(source_ip, destination_ip,reminder_size);
		last_header_bytes = last_header.get_header_as_bytes();
		//write  last header and last bytes to file
		fout.write(last_header_bytes, HEADER_SIZE);
		fout.write(buffer+full_packets_count*FULL_SIZE-1, reminder_size);//TODO: i doubt this logic
		//fout.write(buffer+full_packets_count*FULL_SIZE ,length%FULL_SIZE);//or this?
	}

	fout.close();
	delete []buffer;
	delete []last_header_bytes;

	return true;
}

bool ip_file_handler::ip_packets_to_file (std::string input_file_name, std::string output_file_name, unsigned int source_ip, unsigned int destination_ip){
	return true;
}//TODO :ip_file_handler::ip_packets_to_file



//****************************************************Private Functions*******************************************//

int ip_file_handler::read_file_to_buffer(char* buffer, std::string input_file_name)//reads input file entirely into buffer and return file's size
{//Note: Adding 'static' to this declaration causes an error. is it ok to implement static function without static keyword?
	std::fstream fin;
	int length;
	fin.open (input_file_name, ios::in | ios::binary);
	fin.seekg (0, fstream::end);
	length = fin.tellg();
	fin.seekg (0, fstream::beg);
	buffer = new char [length];
	fin.read (buffer,length);  //file is entirely in buffer
	fin.close();
	return length;
}

//
//#include "ip_file_handler.h"
//
//
//bool ip_file_handler::file_to_ip_packets(std::string input_file_name, std::string output_file_name, unsigned int source_ip, unsigned int destination_ip){
//  open file
//  while{
//  read from mile [256]
//  build header() x
//  x.write to file
//  }
//	return true;
//}
//
//bool ip_file_handler::ip_packets_to_file (std::string input_file_name, std::string output_file_name, unsigned int source_ip, unsigned int destination_ip){
//	open file to read
//  open file to write
// while{
//   read 20 byted (b_1_2 = first and second byte and so on)
//   checks for header
//   if header OK read DATASIZE - 20 (to buffer)
//   write buffer to new file
//   }
//  return true;
//}
