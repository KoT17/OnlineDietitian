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
list<int> calculateUserDiet(Table table, float userBMI, int userRestrict, std::string activity);
json::value jsonCreateFromDiet(Row firstDiet, Row secondDiet);

NutritionalServer::NutritionalServer(utility::string_t url) : listener(url) {
	listener.support(methods::GET, std::bind(&NutritionalServer::handle_get, this, std::placeholders::_1));
	listener.support(methods::PUT, std::bind(&NutritionalServer::handle_put, this, std::placeholders::_1));
	listener.support(methods::POST, std::bind(&NutritionalServer::handle_post, this, std::placeholders::_1));
	listener.support(methods::DEL, std::bind(&NutritionalServer::handle_delete, this, std::placeholders::_1));
}

void NutritionalServer::handle_get(http_request message) {
	ucout << message.to_string() << endl;
	json::value food = json::value::object();
	json::value jsonReturn;
	json::value error;
	http_response res;

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

		Session sess("localhost", 33060, "root", "root");
		Schema db = sess.getSchema("user_db");
		Table table = db.getTable("users");
		Table diets = db.getTable("diet_plans");

		Row userRow = table.select().where("username like :username AND password like :password").bind("username", convertToStd(username)).bind("password", convertToStd(password)).execute().fetchOne();

		float userBMI;
		int userRestrict;
		std::string activityLevel;

		// MODIFY THESE VALUES ONCE FINAL TABLE RELEASES
		try {
			userBMI = userRow.get(8);
			userRestrict = userRow.get(10);
			activityLevel = Value(userRow.get(11)).operator std::string();
		}
		catch (const Error & err) {
			cout << "ERROR: " << err << endl;

			error[L"error"] = json::value::string(utility::conversions::to_utf16string("Username or Email is not unique"));
			res.set_body(error);
			json::value errorJson = res.extract_json(false).get();

			message.reply(status_codes::NotAcceptable, errorJson);
		}

		list<int> dietRows = calculateUserDiet(diets, userBMI, userRestrict, activityLevel);

		int	firstDietPlanID = dietRows.front();
		int	secondDietPlanID = dietRows.back();

		Row firstDiet = diets.select().where("diet_plan_id like :dietID").bind("dietID", firstDietPlanID).execute().fetchOne();
		Row secondDiet = diets.select().where("diet_plan_id like :dietID").bind("dietID", secondDietPlanID).execute().fetchOne();

		res.set_body(jsonCreateFromDiet(firstDiet, secondDiet));
		json::value response = res.extract_json(false).get();

		message.reply(status_codes::OK, response);
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
	json::value error;
	http_response res;

	if (strcmp(utility::conversions::to_utf8string(source).c_str(), "login") == 0) {
		utility::string_t emailField = utility::conversions::to_string_t("email");

		utility::string_t email = (message.headers().find(emailField))->second;
		Session sess("localhost", 33060, "root", "root");
		Schema db = sess.getSchema("user_db");
		Table table = db.getTable("users");

		Row userRow = table.select().where("email like :email AND password like :password").bind("email", convertToStd(email)).bind("password", utility::conversions::to_utf8string(password)).execute().fetchOne();

		if (!userRow.isNull()) {
			ucout << "A JSON has been returned to the client from login page" << endl;

			jsonReturn[L"email"] = json::value::string(utility::conversions::to_utf16string(email));
			jsonReturn[L"password"] = json::value::string(utility::conversions::to_utf16string(password));
			res.set_body(jsonReturn);
			json::value response = res.extract_json(false).get();

			message.reply(status_codes::OK, response);
		}
		else {
			ucout << "Email or Password is incorrect" << endl;

			error[L"error"] = json::value::string(utility::conversions::to_utf16string("Email or Password is not correct"));
			res.set_body(error);
			json::value errorJson = res.extract_json(false).get();

			message.reply(status_codes::NotAcceptable, errorJson);
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
			table.insert("username", "password", "first_name", "last_name", "email")
				.values(convertToStd(username), convertToStd(password), convertToStd(fName), convertToStd(lName), convertToStd(email))
				.execute();
		}
		catch (const Error & err) {
			cout << "ERROR: " << err << endl;

			error[L"error"] = json::value::string(utility::conversions::to_utf16string("Username or Email is not unique"));
			res.set_body(error);
			json::value errorJson = res.extract_json(false).get();

			message.reply(status_codes::NotAcceptable, errorJson);
		}

		// Set up the response of the user's information as a json 
		if (table.count() == (count + 1)) {
			ucout << "User has successfully registered" << endl;

			jsonReturn[L"name"] = json::value::string(utility::conversions::to_utf16string(username));
			jsonReturn[L"email"] = json::value::string(utility::conversions::to_utf16string(email));
			jsonReturn[L"password"] = json::value::string(utility::conversions::to_utf16string(password));

			res.set_body(jsonReturn);

			json::value response = res.extract_json(false).get();

			message.reply(status_codes::OK, response);
		}
		else {
			ucout << "Username or Email is not unique" << endl;

			error[L"error"] = json::value::string(utility::conversions::to_utf16string("Username or Email is not unique"));
			res.set_body(error);
			json::value errorJson = res.extract_json(false).get();

			message.reply(status_codes::NotAcceptable, errorJson);
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
				.set("BMI", (float) calculateBMI(weight, height))
				.set("activity_level", convertToStd(activity))
				.set("diet_restriction", convertToStd(restrict))
				.where("username like :username").bind("username", convertToStd(username))
				.execute();
		}
		catch (const Error & err) {
			cout << "ERROR: " << err << endl;

			error[L"error"] = json::value::string(utility::conversions::to_utf16string("Table failed on updating user values"));
			res.set_body(error);
			json::value errorJson = res.extract_json(false).get();

			message.reply(status_codes::BadGateway, errorJson);
		}

		jsonReturn[L"email"] = json::value::string(utility::conversions::to_utf16string(email));
		jsonReturn[L"height"] = json::value::string(utility::conversions::to_utf16string(height));
		jsonReturn[L"weight"] = json::value::string(utility::conversions::to_utf16string(weight));
		jsonReturn[L"gender"] = json::value::string(utility::conversions::to_utf16string(gender));
		jsonReturn[L"DOB"] = json::value::string(utility::conversions::to_utf16string(DOB));
		jsonReturn[L"lvlOfActivity"] = json::value::string(utility::conversions::to_utf16string(activity));
		jsonReturn[L"dietaryRestriction"] = json::value::string(utility::conversions::to_utf16string(restrict));
		jsonReturn[L"user"][L"email"] = json::value::string(utility::conversions::to_utf16string(email));

		ucout << "Survey information has been updated" << endl;
		res.set_body(jsonReturn);

		json::value response = res.extract_json(false).get();

		message.reply(status_codes::OK, response);
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

			jsonReturn[L"email"] = json::value::string(utility::conversions::to_utf16string(email));
			jsonReturn[L"diet"] = json::value::string(utility::conversions::to_utf16string(diet));

			res.set_body(jsonReturn);

			json::value response = res.extract_json(false).get();

			ucout << "User has updated their diet plan " << endl;
			message.reply(status_codes::OK, response);
		}
		catch (const Error & err) {
			cout << "ERROR: " << err << endl;

			error[L"error"] = json::value::string(utility::conversions::to_utf16string("Updating the User diet plan failed"));
			res.set_body(error);
			json::value errorJson = res.extract_json(false).get();

			message.reply(status_codes::BadGateway, errorJson);
		}
		message.reply(status_codes::OK, res.extract_json(false).get());
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

json::value jsonCreateFromDiet(Row firstDiet, Row secondDiet) {
	json::value result;

	result[L"firstDiet"][L"DietName"] = json::value::number(firstDiet.get(0).operator int());
	result[L"firstDiet"][L"calorie_count"] = json::value::number(firstDiet.get(1).operator int());
	result[L"firstDiet"][L"dietary_restrictions"] = json::value::string(utility::conversions::to_utf16string(firstDiet.get(2).operator std::string().c_str()));
	result[L"firstDiet"][L"breakfast"] = json::value::string(utility::conversions::to_utf16string(firstDiet.get(3).operator std::string().c_str()));
	result[L"firstDiet"][L"lunch"] = json::value::string(utility::conversions::to_utf16string(firstDiet.get(4).operator std::string().c_str()));
	result[L"firstDiet"][L"dinner"] = json::value::string(utility::conversions::to_utf16string(firstDiet.get(5).operator std::string().c_str()));

	result[L"secondDiet"][L"DietName"] = json::value::number(secondDiet.get(0).operator int());
	result[L"secondDiet"][L"calorie_count"] = json::value::number(secondDiet.get(1).operator int());
	result[L"secondDiet"][L"dietary_restrictions"] = json::value::string(utility::conversions::to_utf16string(secondDiet.get(2).operator std::string().c_str()));
	result[L"secondDiet"][L"breakfast"] = json::value::string(utility::conversions::to_utf16string(secondDiet.get(3).operator std::string().c_str()));
	result[L"secondDiet"][L"lunch"] = json::value::string(utility::conversions::to_utf16string(secondDiet.get(4).operator std::string().c_str()));
	result[L"secondDiet"][L"dinner"] = json::value::string(utility::conversions::to_utf16string(secondDiet.get(5).operator std::string().c_str()));

	return result;
}

list<int> calculateUserDiet(Table table, float userBMI, int userRestrict, std::string activity) {
	list<int> result;
	float targetBMI = 19.2;
	float diff = targetBMI - userBMI;
	int calorieCeiling;

	// Determine proper calorie count from BMI
	if (diff > 10.8)
		calorieCeiling = 1201;
	else if (diff > 5.8)
		calorieCeiling = 1501;
	else if (diff > 0)
		calorieCeiling = 2201;
	else
		calorieCeiling = 2701;
		
	// Factor excerise 
	if (strcmp(activity.c_str(), "Light Excersie") == 0)
		calorieCeiling += 200;
	else if (strcmp(activity.c_str(),"Moderate Excersie") == 0)
		calorieCeiling += 400;
	else if (strcmp(activity.c_str(), "Heavy Excerise") == 0) {
		calorieCeiling += 600;
	}

	// Create the results from the table to send to the client
	list<Row> values;
	std::string whereStr = "";
	std::string bindStr = "";
	cout << values.size() << endl;

	cout << "Passed Values" << endl;

	switch (userRestrict) {
	case 1: // Vegan Restriction
		whereStr = "dietary_restrictions like :restrict AND calorie_count < :calorie";
		bindStr = "Vegan";
		break;
	case 2: // Vegetratian Restriction
		whereStr = "dietary_restrictions like :restrict AND calorie_count < :calorie";
		bindStr = "Vegetarian";
		break;
	case 3: // GF Restriction
		whereStr = "dietary_restrictions like :restrict AND calorie_count < :calorie";
		bindStr = "GF";
		break;
	}

	if(userRestrict == 0)
		values = table.select().execute().fetchAll();
	else {
		values = table.select().where(whereStr).bind("restrict", bindStr).bind("calorie", calorieCeiling).execute().fetchAll();
	}

	int dietOneSpot = rand() % values.size();
	int dietTwoSpot = rand()/2 % values.size();
	int count = 0;
	while (dietTwoSpot == dietOneSpot && (values.size() != 1)) {
		dietTwoSpot = (dietTwoSpot+1) % values.size();
	}

	for (list<Row>::iterator it = values.begin(); it != values.end(); it++) {
		if(count == dietOneSpot || count == dietTwoSpot)
			result.push_back(it->get(0).operator int());
		count++;
	}
	return result;
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