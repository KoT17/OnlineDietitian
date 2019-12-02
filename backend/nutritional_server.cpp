#include <stdlib.h>
#include <string>
#include <cmath>
#include <iostream>
#include <mysql.h>
#include <mysqlx/xdevapi.h>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/http_listener.h> 
#include <cpprest/json.h>  
#include <cpprest/uri.h>
#include <cpprest/asyncrt_utils.h>
#include "NutritionalServer.h"


using namespace std;
using namespace mysqlx;
using namespace utility;
using namespace web;
using namespace pplx;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;
using namespace http::experimental::listener;

std::string convertToStd(utility::string_t str);
float calculateBMI(utility::string_t weight, utility::string_t height);

NutritionalServer::NutritionalServer(utility::string_t url) : listener(url) {
	listener.support(methods::GET, std::bind(&NutritionalServer::handle_get, this, std::placeholders::_1));
	listener.support(methods::PUT, std::bind(&NutritionalServer::handle_put, this, std::placeholders::_1));
	listener.support(methods::POST, std::bind(&NutritionalServer::handle_post, this, std::placeholders::_1));
	listener.support(methods::DEL, std::bind(&NutritionalServer::handle_delete, this, std::placeholders::_1));
}

void NutritionalServer::handle_get(http_request message) {
	ucout << message.to_string() << endl;
	json::value food = json::value::object();

	utility::string_t sourceField = utility::conversions::to_string_t("source");
	utility::string_t userField = utility::conversions::to_string_t("user");
	utility::string_t passField = utility::conversions::to_string_t("password");

	utility::string_t source = (message.headers().find(sourceField))->second;
	utility::string_t username = (message.headers().find(userField))->second;
	utility::string_t password = (message.headers().find(passField))->second;

	// No login information required for this block
	if (strcmp(utility::conversions::to_utf8string(source).c_str(), "lookup") == 0) {
		ucout << "GET Nutritional Lookup has been hit" << endl;
	}

	// Login information required for this block
	if (strcmp(utility::conversions::to_utf8string(source).c_str(), "user_info") == 0) {
		ucout << "GET User Info has been hit" << endl;
	}

	// Login information required for this block
	if (strcmp(utility::conversions::to_utf8string(source).c_str(), "diet_choice") == 0) {
		ucout << "GET Diet Choices has been hit" << endl;
	}
	message.reply(status_codes::OK);
}

void NutritionalServer::handle_put(http_request message) {
	ucout << message.to_string() << endl;
	message.reply(status_codes::OK);
}

void NutritionalServer::handle_post(http_request message) {
	ucout << message.to_string() << endl;
	utility::string_t sourceField = utility::conversions::to_string_t("source");
	utility::string_t userField = utility::conversions::to_string_t("user");
	utility::string_t passField = utility::conversions::to_string_t("password");

	utility::string_t source = (message.headers().find(sourceField))->second;
	utility::string_t username = (message.headers().find(userField))->second;
	utility::string_t password = (message.headers().find(passField))->second;

	json::value jsonReturn;
	http_response res;
	http_client client(L"http://localhost:4200/NutritionalLookup");

	if (strcmp(utility::conversions::to_utf8string(source).c_str(), "login") == 0) {
		utility::string_t emailField = utility::conversions::to_string_t("email");

		utility::string_t email = (message.headers().find(emailField))->second;
		Session sess("localhost", 33060, "root", "root");
		Schema db = sess.getSchema("user_db");
		Table table = db.getTable("users");

		Row userRow = table.select().where("email like :email AND password like :password").bind("email", convertToStd(email)).bind("password", utility::conversions::to_utf8string(password)).execute().fetchOne();

		// Sending back the response, need to figure out where to send this as a response. May need handler in main? 
		jsonReturn[L"email"] = json::value::string(utility::conversions::to_utf16string(email));
		jsonReturn[L"password"] = json::value::string(utility::conversions::to_utf16string(password));

		res.set_body(jsonReturn);

		pplx::task<json::value> response = res.extract_json(false);

		if (!userRow.isNull()) {
			ucout << "A JSON has been returned to the client from login page" << endl;
		}
		else {
			ucout << "Username or Password is incorrect" << endl;
		}
	}
	else if (strcmp(utility::conversions::to_utf8string(source).c_str(), "registration") == 0) {
		utility::string_t emailField = utility::conversions::to_string_t("email");
		utility::string_t fNameField = utility::conversions::to_string_t("fName");
		utility::string_t lNameField = utility::conversions::to_string_t("lName");

		utility::string_t email = (message.headers().find(emailField))->second;
		utility::string_t fName = (message.headers().find(fNameField))->second;
		utility::string_t lName = (message.headers().find(lNameField))->second;

		Session sess("localhost", 33060, "root", "root");
		Schema db = sess.getSchema("user_db");
		Table table = db.getTable("users");
		int count = table.count();
		try {
			table.insert("username", "password", "first_name", "last_name", "email").values(convertToStd(username), convertToStd(password), convertToStd(fName), convertToStd(lName), convertToStd(email)).execute();
		}
		catch (const Error & err) {
			cout << "ERROR: " << err << endl;
			message.reply(status_codes::NotAcceptable); // May need to be modified to ensure for proper reply
		}

		// Set up the response of the user's information as a json 
		if (table.count() == (count + 1)) {
			ucout << "User has successfully registered" << endl;
		}
		else {
			ucout << "Username or Email is not unique" << endl;
		}
	}
	else if (strcmp(utility::conversions::to_utf8string(source).c_str(), "survey") == 0) {
		utility::string_t emailField = utility::conversions::to_string_t("email");
		utility::string_t heightField = utility::conversions::to_string_t("height");
		utility::string_t weightField = utility::conversions::to_string_t("weight");
		utility::string_t genderField = utility::conversions::to_string_t("gender");
		utility::string_t DOBField = utility::conversions::to_string_t("DOB");
		utility::string_t activityField = utility::conversions::to_string_t("lvlOfActivity");
		utility::string_t restrictField = utility::conversions::to_string_t("dietaryRestriction");

		utility::string_t email = (message.headers().find(emailField))->second;
		utility::string_t height = (message.headers().find(heightField))->second;
		utility::string_t weight = (message.headers().find(weightField))->second;
		utility::string_t gender = (message.headers().find(genderField))->second;
		utility::string_t DOB = (message.headers().find(DOBField))->second;
		utility::string_t activity = (message.headers().find(activityField))->second;
		utility::string_t restrict = (message.headers().find(restrictField))->second;

		int birthYear = stoi(convertToStd(DOB).substr(0, 4));
		int birthMonth = stoi(convertToStd(DOB).substr(5, 6));
		int birthDay = stoi(convertToStd(DOB).substr(8, 9));

		int currentYear = stoi(convertToStd(datetime::utc_now().to_string()).substr(11, 15));

		Session sess("localhost", 33060, "root", "root");
		Schema db = sess.getSchema("user_db");
		Table table = db.getTable("users");

		try {
			table.update()
				.set("weight", convertToStd(weight))
				.set("height", convertToStd(height))
				.set("gender", convertToStd(gender))
				.set("age", currentYear - birthYear)
				.set("BMI", calculateBMI(weight, height))
				.set("activity_level", convertToStd(activity))
				.set("diet_restriction", convertToStd(restrict))
				.where("username like :username").bind("username", convertToStd(username))
				.execute();
		}
		catch (const Error & err) {
			cout << "ERROR: " << err << endl;
			message.reply(status_codes::NotAcceptable); // May need to be modified to ensure for proper reply
		}

		ucout << "Survey information has been updated" << endl;
		message.reply(status_codes::OK);
	}
	else if (strcmp(utility::conversions::to_utf8string(source).c_str(), "selection") == 0) {
		utility::string_t emailField = utility::conversions::to_string_t("email");
		utility::string_t dietField = utility::conversions::to_string_t("diet");

		utility::string_t email = (message.headers().find(emailField))->second;
		utility::string_t diet = (message.headers().find(dietField))->second;

		Session sess("localhost", 33060, "root", "root");
		Schema db = sess.getSchema("user_db");
		Table table = db.getTable("users");

		try {
			table.update()
				.set("diet_plan_id", convertToStd(diet))
				.where("username like :username").bind("username", convertToStd(username))
				.execute();
		}
		catch (const Error & err) {
			cout << "ERROR: " << err << endl;
			message.reply(status_codes::NotAcceptable); // May need to be modified to ensure for proper reply
		}
		message.reply(status_codes::OK);
	}

}

void NutritionalServer::handle_delete(http_request message) {
	ucout << message.to_string() << endl;
	message.reply(status_codes::OK);
}

std::string convertToStd(utility::string_t str) {
	return utility::conversions::to_utf8string(str);
}

float calculateBMI(utility::string_t weight, utility::string_t height) {
	return (703 * stof(convertToStd(weight))) / pow(stof(convertToStd(height)), 2);
}

int calculateUserDiet(float userBMI) {
	float targetBMI = 19.2;
	float diff = targetBMI - userBMI;


}

int nutritional_load() {

	try {
		Session sess("localhost", 33060, "root", "root");
		Schema db = sess.getSchema("OnlineDietitian");


		// Create a new collection 'my_collection'
		Table table = db.getTable("Food");

		cout << distance(db.getTables().begin(), db.getTables().end()) << endl;

		cout << "Connected to food DB" << endl;

		list<Row> values = table.select().execute().fetchAll();

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