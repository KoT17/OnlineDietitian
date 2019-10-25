#include <stdlib.h>
#include <iostream>
#include <mysql.h>
#include <mysqlx/xdevapi.h>

using namespace std;
using namespace mysqlx;

// Current code is MySQL code for Database Connection
int main() {

	// Scope controls life-time of objects such as session or schema

	try{
		Session sess("localhost", 33060, "root", "root");
		Schema db = sess.getSchema("testdb");
		// or Schema db(sess, "test");

		// Create a new collection 'my_collection'
		Collection myColl = db.createCollection("my_collection");

		// Insert documents
		myColl.add(R"({"name": "Nadya", "age": 54})").execute();
		myColl.add(R"({"name": "Laurie", "age": 19})").execute();
		myColl.add(R"({"name": "Lukas", "age": 32})").execute();

		// Find a document
		DocResult docs = myColl.find("name like :param1 AND age < :param2").limit(1)
			.bind("param1", "N%").bind("param2", 60).execute();

		// Print document
		cout << docs.fetchOne();

		// Drop the collection
		db.dropCollection("my_collection");
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