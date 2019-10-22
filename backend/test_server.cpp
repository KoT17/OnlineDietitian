#include <stdlib.h>
#include <iostream>
#include <mysql.h>
#include <mysqlx/xdevapi.h>

using namespace std;
using namespace mysqlx;

// Current code is MySQL code for Database Connection
int main() {

	// Scope controls life-time of objects such as session or schema

	{
		Session sess("localhost", 33060, "user", "password");
		Schema db = sess.getSchema("test");
		// or Schema db(sess, "test");

		Collection myColl = db.getCollection("my_collection");
		// or Collection myColl(db, "my_collection");

		DocResult myDocs = myColl.find("name like :param")
			.limit(1)
			.bind("param", "S%").execute();

		cout << myDocs.fetchOne();
	}
}