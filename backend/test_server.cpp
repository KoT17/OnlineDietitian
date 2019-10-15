// Documentation (https://downloads.mysql.com/docs/connector-cpp-8.0-en.pdf)
// Chapter 2-4 for installation and Chapter 5 for building

#include <stdlib.h>
#include <iostream>
#include <mysql.h>

// This include is not properly being set 
// with current additional directories (MySQL/MySQL Server 8.0/include and MySQL/Connector C++ 8.0/lib64)
// There needs to be an include or build that allows for this include to work.
#include <mysqlx/xdevapi.h>

using namespace std;

// Current code is outdated MySQL code for MySQL 1.1
// Will update when xdevapi functions
int main() {
	sql::mysql::MySQL_Driver* driver;
	sql::Connection* con;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "user", "password");

	delete con;
}