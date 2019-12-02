#include <stdlib.h>
#include <iostream>
#include <mysql.h>
#include <mysqlx/xdevapi.h>

using namespace std;
using namespace mysqlx;

int test_all_units();
int test_database_insert();
int test_database_connection();
int test_database_delete();

int test() {
	test_all_units();
	return 0;
}

int test_all_units() {
	try{
		int errors = 0;
		errors += test_database_connection();
		errors += test_database_insert();
		errors += test_database_delete();
		if (errors == 0)
			cout << "Tests passed successfully with 0 errors" << endl;
		else
			cout << "Tests passed failed with " << errors << " errors" << endl;
		return 0;
	}
	catch (const Error & err)
	{
		cout << "ERROR: " << err << endl;
	}
	catch (std::exception & ex)
	{
		cout << "STD EXCEPTION: " << ex.what() << endl;
	}
	catch (const char* ex)
	{
		cout << "EXCEPTION: " << ex << endl;
	}
}

int test_database_connection() {
	Session sess("localhost", 33060, "root", "root");
	Schema db = sess.getSchema("testdb");

	Table table = db.getTable("test_table");

	assert(table.getSchema().getName() == "testdb");
	assert(table.getName() == "test_table");

	return !(table.getSchema().getName() == "testdb");
}

int test_database_insert() {
	Session sess("localhost", 33060, "root", "root");
	Schema db = sess.getSchema("testdb");

	Table table = db.getTable("test_table");
	table.insert("Name", "Number").values("Doritos", 20).execute();

	assert(table.count() == 1);
	table.remove().execute();
	return !(table.count() == 0);
}

int test_database_delete() {
	Session sess("localhost", 33060, "root", "root");
	Schema db = sess.getSchema("testdb");


	Table table = db.getTable("test_table");
	table.insert("Name", "Number").values("Doritos", 20).execute();

	assert(table.count() == 1);
	table.remove().where("Name='Doritos'").execute();
	assert(table.count() == 0);
	return !(table.count() == 0);
}