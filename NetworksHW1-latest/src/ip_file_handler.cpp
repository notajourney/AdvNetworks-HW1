#include "ip_file_handler.h"
using namespace std;
#include <fstream>

bool ip_file_handler::file_to_ip_packets(std::string input_file_name, std::string output_file_name, unsigned int source_ip, unsigned int destination_ip){

	const int FULL_SIZE = 256;
	std::fstream fout;
	char* buffer= NULL;
	int length= read_file_to_buffer( buffer,input_file_name);
	Ipv4Header* header = new Ipv4Header(source_ip,destination_ip,FULL_SIZE);


	fout.open(output_file_name, ios::out | ios::binary);
	int full_packets_count = (length/FULL_SIZE);


	for(int i=0;  i<full_packets_count-1;  i++)
	{
		//write header to file
		header->write_header();//this function should receive an output file name &  write header to file;
		//write  256 bytes to file
		fout.write(buffer+i*FULL_SIZE, FULL_SIZE);

	}
//check if there is  reminder
	//here :  making header with remainder data length
	int reminder_size = (length - full_packets_count*FULL_SIZE);
	Ipv4Header* last_header = new Ipv4Header(source_ip,destination_ip,reminder_size);
	//write header to file
	last_header->write_header();
	// write reminder data to file
	fout.write(buffer+full_packets_count*FULL_SIZE ,length%FULL_SIZE);
	fout.close();
	delete []buffer;

	return true;
}

bool ip_file_handler::ip_packets_to_file (std::string input_file_name, std::string output_file_name, unsigned int source_ip, unsigned int destination_ip){
	return true;
}

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
