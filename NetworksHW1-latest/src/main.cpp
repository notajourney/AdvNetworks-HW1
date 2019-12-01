#include <iomanip>
#include <iostream>
#include <fstream>
#include "TempIp.h"
#include"ip_file_handler.h"



using namespace std;
int main() {


	ip_file_handler::file_to_ip_packets("test.bin","output.bin",0x01020304,0x05060708);//#1
	ip_file_handler::ip_packets_to_file("output.bin","check.txt",0x01020304,0x05060708);//#2

	//#1:divides "test.bin" into fragments of 256 bytes and encapsulates data with ip header. writes results to "output.bin"
	//#2: reads ip header from "outpu.bin", reads "datasize" data and writes data to output file (repeatedly)

	return 0;
}


