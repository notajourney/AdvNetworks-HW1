#include <iomanip>
#include <iostream>
#include <fstream>
#include "TempIp.h"
#include"ip_file_handler.h"
//last//
using namespace std;
int main() {


	ip_file_handler::file_to_ip_packets("test.txt","output.bin",0x01020304,0x05060708);
	ip_file_handler::ip_packets_to_file("output.bin","check.txt",0x01020304,0x05060708);


	return 0;
}


