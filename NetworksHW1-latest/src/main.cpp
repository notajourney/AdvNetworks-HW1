#include <iomanip>
#include <iostream>

#include "TempIp.h"
#include"ip_file_handler.h"

using namespace std;
int main() {
	//Ipv4Header tmp(0x01020304,0x05060708,0);
	//tmp.write_header();

	/* the program */
	ip_file_handler::file_to_ip_packets("test.txt","output.bin",0x01020304,0x05060708);
	ip_file_handler::ip_packets_to_file("output.bin","check.txt",0x01020304,0x05060708);

/*
	unsigned int a = 0x12345678;
	unsigned char *lol = (unsigned char*) &a;
	//TempIp s;
	//s.set_version(3);
	//cout<< s.version() <<endl;
	cout << "how it looks in memory" << endl;
	for (int i = 0; i < 4; i++) {
		cout << setw(2) << setfill('0') << hex << (unsigned int) *(lol + i)<< ' ';
	}
	cout << endl;
	cout << "how it should look in file" <<endl;
	for (int i = 3; i >= 0; i--) {
		cout << setw(2) << setfill('0') << hex << (unsigned int) *(lol + i)<< ' ';
	}
	cout << endl;*/
	return 0;
}

/*
 struct student
 {
 unsigned int student_number;
 unsigned int IpAddress;

 student ()
 {
 this->IpAddress = 0x01020304;
 this->student_number = 1;
 unsigned char* pointer = (unsigned char*)this;
 while (pointer < ((unsigned char*)this) +  (sizeof(student))) {
 cout<<(int)*pointer;
 cout<<" ";
 pointer++;
 }
 cout<<endl;
 }

 };
 */
