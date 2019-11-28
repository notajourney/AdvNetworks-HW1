#ifndef IP_FILE_HANDLER_H_
#define IP_FILE_HANDLER_H_

#include "ip_header.h"

#include<iostream>
using namespace std;


class ip_file_handler {
public:
	ip_file_handler(){}
	virtual ~ip_file_handler(){}
	static bool file_to_ip_packets(std::string input_file_name, std::string output_file_name, unsigned int source_ip, unsigned int destination_ip);
	static bool ip_packets_to_file (std::string input_file_name, std::string output_file_name, unsigned int source_ip, unsigned int destination_ip);

private:
	static int read_file_to_buffer(char* buffer, std::string input_file_name);

};

#endif			/* IP_FILE_HANDLER_H_ */
