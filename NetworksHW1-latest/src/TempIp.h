#ifndef TEMPIP_H_
#define TEMPIP_H_
#include<iostream>
using namespace std;
//last//
class TempIp {

	char header[20];

private:
	TempIp(){}//default constructor is disabled

public:

	TempIp(unsigned long int src_ip, unsigned long int dst_ip, short int data_size) {

		for (int i = 0; i < 20; ++i) header[i] =0;

		this->set_version_IHL();
		this->set_DCP_ECN();
		this->set_total_length(data_size);
		this->set_identification();
		this->set_flags_offset();
		this->set_TTL();
		this->set_protocol();
		this->set_header_checksum();//zero by default
		this->set_source_ip(src_ip);
		this->set_dest_ip(dst_ip);

		//TODO: update checksum
		//short var = this->caculate_checksum(  );
		//this->set_header_checksum(var);

	}


	TempIp(char* header_from_file) {

		for (int i = 0; i < 20; ++i) header[i] =0;
		for (int i = 0; i < 20; ++i) header[i] = header_from_file[i];
	}//simply read 20 bytes from file and the whole header is initialized and class is functioning!



	void set_version_IHL() {
		header[0] = 0b01010100;
	} //byte#1::(version=4,IHL=5)

	void set_DCP_ECN() {
		header[1] = 0;
	} //byte#2

	void set_total_length(short int data_size) {

		unsigned short int total_length = data_size + 20;
		little_to_bigEndian(header + 2, &total_length, 2);

	}//byte#3+byte#4	::data_size +=20  and insert big endian

	void set_identification() {
		header[4] = 0;
		header[5] = 0;
	} //byte#5+byte#6

	void set_flags_offset() {
		header[6] = 0;
		header[7] = 0;
	} //byte#7+byte#8


	void set_TTL() {

		header[8] = 0b11001000;
	}//byte#9

	void set_protocol() {
		header[9] = 0b10001111;//143
	}//byte#10

	void set_header_checksum(unsigned short int check_sum = 0) {
		unsigned short int checksum = check_sum;
		little_to_bigEndian(header + 10, &checksum, 2);
	}//byte#11+byte#12 ::zero by default TODO:updated later

	void set_source_ip(unsigned long int source_ip) {
		unsigned long int ip = source_ip;
		little_to_bigEndian(header + 12, &ip, 4);

	}	//byte#13 - byte#16

	void set_dest_ip(unsigned long int dest_ip) {
		unsigned long int ip = dest_ip;
		little_to_bigEndian(header + 16, &ip, 4);

	} //byte#17 - byte#20

	char* get_header_as_bytes()
	{

		char* header_copy = new char[20];
		for (int i = 0; i < 20; ++i) {

			header_copy[i]=header[i];
		}

		return header_copy;
	}//TODO:free memory of header_copy

	unsigned short int get_total_length() {
		return bytes_to_shortInteger(header + 2, 1);
	}
	unsigned short int get_checksum() {
		return bytes_to_shortInteger(header + 10, 1);
	}
	unsigned long int get_source_ip() {
		return bytes_to_longInteger(header + 12, 1);
	}
	unsigned long int get_dest_ip() {
		return bytes_to_longInteger(header + 16, 1);
	}

private:

	unsigned short int calculate_checksum(); //TODO: Implement checksum algorithm

	//****************************************************************************************************//
	//Copies 'var_size' bytes from 'var_address' to 'target_address' (including 'target_address') in big endianess
	void little_to_bigEndian(char *target_address, void *var_address,unsigned short int var_size) {
		if (var_size <= 0) {
			cout << "Nothing to do" << endl;
			return;
		}

		int j = 0;
		for (int i = var_size - 1; i >= 0; i--)
			target_address[j++] = *((char*) (var_address) + i);
	}
	//****************************************************************************************************//

	//****************************************************************************************************//
	void big_to_littleEndian(char *target_address, void *var_address,unsigned short int var_size) {
		//Copies 'var_size' bytes from 'var_address' to 'target_address' (including 'target_address') in little endianess
		//Assumed: var_address[0]  to var_address[var_size-1] are in big endian
		char temp[var_size];
		for (int i = 0; i < var_size; ++i) {
			temp[i] = *((char*) (var_address) + i);
		}	//duplicating var_address content

		int j = 0;
		for (int i = var_size - 1; i >= 0; i--)
			target_address[j++] = temp[i];	//target is back to little endian
	}
	//****************************************************************************************************//

	//****************************************************************************************************//
	//Prints to std out 'bytes_num' bytes as bits (starting and including start_addr)
	//Assistant function
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
	//****************************************************************************************************//

	//****************************************************************************************************//
	unsigned long int bytes_to_longInteger(char *bytes, int option) {
		//This function converts the 4  char array bytes  into an actual long integer
		//endianess is optional:
		// 0 : little endian
		// 1: big endian
		// 2: 'bytes' endianess is not manipulated at all
		int size = sizeof(unsigned long int);
		char temp[size];
		for (int i = 0; i < size; ++i) {
			temp[i] = bytes[i];
		}//duplicating var_address content

		switch (option) {

		case 0:
			little_to_bigEndian(temp, bytes, size);
			return *((unsigned long int*) (temp));
		case 1:
			big_to_littleEndian(temp, bytes, size);
			return *((unsigned long int*) (temp));

		case 2:
			return *((unsigned long int*) (temp));

		default:
			cout << "bytes_to_longInteger ERROR : no such option " << option
			<< endl;
			return 0;
		}

	}
	//****************************************************************************************************//

	//****************************************************************************************************//
	unsigned short int bytes_to_shortInteger(char *bytes, int option) { // see 'bytes_to_longInteger' description
		int size = sizeof(unsigned short int);
		char temp[size];
		for (int i = 0; i < size; ++i) {
			temp[i] = bytes[i];
		}

		switch (option) {
		case 0:
			little_to_bigEndian(temp, bytes, size);
			return *((unsigned short int*) (temp));
		case 1:
			big_to_littleEndian(temp, bytes, size);
			return *((unsigned short int*) (temp));

		case 2:
			return *((unsigned short int*) (temp));
		default:
			cout << "bytes_to_shortInteger ERROR : no such option " << option
			<< endl;
			return 0;
		}

	}

};

#endif /* TEMPIP_H_ */

