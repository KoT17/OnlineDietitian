#include <stdlib.h>
#include <iostream>
#include <mysql.h>
#include <mysqlx/xdevapi.h>

using namespace std;
using namespace mysqlx;

int nutritional_load() {

	// When REST apk is installed, this code should work under a GET from the nutritional page
	try {
		Session sess("localhost", 33060, "root", "root");
		Schema db = sess.getSchema("OnlineDietitian");


		// Create a new collection 'my_collection'
		Table table = db.getTable("Food");

		cout << distance(db.getTables().begin(), db.getTables().end()) << endl;

		cout << "Connected to food DB" << endl;

		list<Row> values =  table.select().execute().fetchAll();
		
		cout << "ID\tNAME\t\tCALORIES\tFAT\tCARBS\tPROTEIN\tSERVING SIZE" << endl;

		for (list<Row>::iterator it = values.begin(); it != values.end(); it++) {
			cout << it->get(0) << "\t" // id 
				<< it->get(1) << "\t\t" // name
				<< it->get(2) << "\t" // calories
				<< it->get(3) << "\t" // fat
				<< it->get(4) << "\t" // carbs 
				<< it->get(5) << "\t" // protein
				<< it->get(6) << endl; // serving size
		}
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