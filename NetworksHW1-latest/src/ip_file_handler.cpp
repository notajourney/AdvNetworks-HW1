#include "ip_file_handler.h"
using namespace std;
#include <fstream>

//TODO: Find bug: in big files input, something goes wrong with the output file size (file sizes are printed to std out)
void print_memory_bytes(void *start_addr, unsigned short int bytes_num);//TODO delete thisline

bool ip_file_handler::file_to_ip_packets(std::string input_file_name, std::string output_file_name, unsigned int source_ip, unsigned int destination_ip){
	const unsigned int FULL_SIZE = 256;
	const unsigned int HEADER_SIZE = 20;
	std::fstream fout;
	char* buffer= NULL;
	fout.open(output_file_name, ios::out | ios::binary);
	char* header_bytes = NULL;
	char* last_header_bytes = NULL;
	unsigned int file_length= read_file_to_buffer( buffer,input_file_name);


	cout<<input_file_name<<": "<<file_length<<endl;//TODO



	if(file_length == 0)
	{
		cout<<"File: "<<input_file_name<<" is empty. ";
		cout<<"Nothing to do (or home exercise was not properly defined"<<endl;
		return false;
	}

	int full_packets_count = (file_length/FULL_SIZE);//Number of 256 Fragments
	if(file_length>=FULL_SIZE)

	{

		for(int i=0;  i<full_packets_count;  i++)//Happens only if file_size > 256
			//Loop writes only 256 fragments
		{
			if(i==0){
				TempIp* header =  new TempIp(source_ip, destination_ip,FULL_SIZE);
				header_bytes = header->get_header_as_bytes();
			}

			fout.write(header_bytes, HEADER_SIZE);
			fout.write(buffer+i*FULL_SIZE, FULL_SIZE);
		}
		delete[] header_bytes;
	}//end if:file_length>=FULL_SIZE


	//calculate the number of bytes reminder
	int reminder_size = (file_length%FULL_SIZE);
	if(reminder_size > 0)//write reminding bytes if there are any
	{
		TempIp* last_header= new TempIp(source_ip, destination_ip,reminder_size);
		last_header_bytes = last_header->get_header_as_bytes();

		//write  last header and last bytes to file
		fout.write(last_header_bytes, HEADER_SIZE);
		fout.write(buffer+full_packets_count*FULL_SIZE-1, reminder_size);//TODO: i doubt this logic
		//fout.write(buffer+full_packets_count*FULL_SIZE ,length%FULL_SIZE);//or this?
	}

	fout.close();
	delete[] buffer;
	delete[] last_header_bytes;
	return true;
}

bool ip_file_handler::ip_packets_to_file (std::string input_file_name, std::string output_file_name, unsigned int source_ip, unsigned int destination_ip){


	//read header from file
	std::fstream fout;
	std::fstream fin;
	fin.open (input_file_name, ios::in | ios::binary);
	//fout.open(output_file_name, ios::in | ios::binary);
	fout.open(output_file_name);//TODO delete this
	unsigned long int file_size = 0;
	char header[20];
	int counter = 0;

	//getting file size:
	fin.seekg (0, fstream::end);
	file_size = fin.tellg();
	fin.seekg (0, fstream::beg);
	cout<<input_file_name<<": "<<file_size<<endl;//TODO

	for(unsigned int i = 0 ; i< file_size; i++)
	{


		//read a single header from file and build it:
		fin.read(header,20);
		i+=20;

		TempIp file_header(header);


		//checking conditions:
		if(file_header.get_source_ip()== source_ip &&
				file_header.get_dest_ip()== destination_ip &&
				file_header.get_checksum() == 0 )
		{//writing data if conditions are met
			int data_size = file_header.get_total_length()-20;

			char* data = new char[data_size];
			fin.read(data, data_size);
			i+=data_size;
			fout.write(data,data_size);
			counter++;
			delete[] data;

		}
		else{
			cout<<"Packet #"<<counter+1<<" was dropped"<<endl;
		}
	}

		fin.close();
		fout.close();

		//test
		fin.open (output_file_name, ios::in | ios::binary);
		fin.seekg (0, fstream::end);
		file_size = fin.tellg();
		fin.seekg (0, fstream::beg);
		cout<<endl;
		cout<<output_file_name<<": "<<file_size;//TODO


}


//****************************************************Private Functions*******************************************//

int ip_file_handler::read_file_to_buffer(char* &buffer, std::string input_file_name)//reads input file entirely into buffer and return file's size
{//Note: Adding 'static' to this declaration causes an error. is it ok to implement static function without static keyword?
	std::fstream fin;
	int length;
	fin.open (input_file_name, ios::in | ios::binary);//open to read binary
	fin.seekg (0, fstream::end);//set pointer to end of file
	length = fin.tellg();//tell size of file
	fin.seekg (0, fstream::beg);

	buffer = new char [length];
	fin.read (buffer,length);  //file is entirely in buffer
	fin.close();
	return length;
}

//**************************************************************************************************//

void print_memory_bytes(void *start_addr, unsigned short int bytes_num) {
	unsigned char mask = 0b10000000;
	unsigned short int adress_counter = 0;
	unsigned short int BITS_COUNT = 8 * bytes_num;

	for (int var = 0; var < BITS_COUNT; ++var) {
		if (var != 0 && var % 8 == 0) {
			cout << " ";
			adress_counter++;
			mask = 0b10000000;
		}

		if ((*((char*) (start_addr) + adress_counter) & mask) == 0)
			cout << "0";
		else {
			cout << "1";
		}
		mask = (mask >> 1);
	}
	cout << endl;
}
