// Copyright 2022 Caden Nelson
/*
 * This CGI script gets the post from insertion.html. It then makes a connecti
 * on with the 278 database in order to insert the data into the health table
 * and then it updates the stats table.
 * Author: Caden Nelson
 * Date: 11/30/2022
 */

#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include <string>
#include <iostream>
#include "getpost.h"

using namespace std;

int main(int argc, char* argv[]) {

	// First, initialize the get
    map<string,string> Get;
    initializePost(Get);
	// Output the HTML content
	cout << "Content-type: text/html" << endl << endl;
    cout << "<html>" << endl;
	// Output the embedded CSS
	cout << "<style>" << endl;
	cout << "@font-face {" << endl;
    cout << "font-family: 'Ink Free';" << endl;
    cout << "font-style: normal;" << endl;
    cout << "font-weight: 400;" << endl;
	cout << "}" << endl;
	cout << "img {" << endl;
	cout << "float: right;" << endl;
	cout << "margin: 5px;" << endl;
	cout << "margin-left: auto;" << endl;
	cout << "max-width: 50%;" << endl;
	cout << "border-radius: 8px;" << endl;
	cout << "}" << endl;
	cout << ".header {" << endl;
	cout << "background-color: #002060;" << endl;
	cout << "text-align: center;" << endl;
	cout << "height: 100px;" << endl;
	cout << "}" << endl;
	cout << "body {" << endl;
	cout << "text-align: justify;" << endl;
	cout << "background: #001030 ;" << endl;
	cout << "font-family: \"Ink Free\" ;" << endl;
	cout << "color: #ffa000;" << endl;
	cout << "}" << endl;
	cout << ".button {" << endl;
	cout << "background-color: #ffa000;" << endl;
	cout << "border: none;" << endl;
    cout << "color: #001030;" << endl;
	cout << "padding: 10px 30px;" << endl;
    cout << "text-align: center;" << endl;
    cout << "text-decoration-thickness: 6px;" << endl;
    cout << "display: inline-block;" << endl;
    cout << "font-size: 20px;" << endl;
    cout << "margin: 4px 2px;" << endl;
    cout << "cursor: pointer;" << endl;
    cout << "font-family: \"Ink Free\";" << endl;
    cout << "}" << endl;
    cout << "</style>" << endl;
	// Output the body of the html document
    cout << "<body>" << endl;
    cout << "<div class=\"header\">" << endl;
    cout << "<h1>Insert data for today</h1>" << endl;
    cout << "</div>" << endl;
    cout << "<img src=\"runner.jpg\">" << endl;
    cout << "<button class = \"button\" onclick = \"document."
	"location.href='index.html';\">Return to Home</button>" << endl;
    cout << "<h2>Please type your username</h2>" << endl;

	// Declares the variables
    int carbs;
    int exercise;
    int water;
    int protein;
    int sugar;
    int sleep;
    int fat;
    int calories;
    std::string date;
    std::string username;
	// Initialize the variables with the data from the get method
    if (Get.find("carbs")!=Get.end() && Get.find("exercise")!=Get.end() &&
		Get.find("water")!=Get.end() && Get.find("protein")!=Get.end() &&
		Get.find("sugar")!=Get.end() && Get.find("sleep")!=Get.end() &&
		Get.find("fat")!=Get.end() && Get.find("calories")!=Get.end() &&
		Get.find("date")!=Get.end() && Get.find("username")!=Get.end()) {
		carbs = std::stoi(Get["carbs"]);
		exercise = std::stoi(Get["exercise"]);
		water = std::stoi(Get["water"]);
		protein = std::stoi(Get["protein"]);
		sugar = std::stoi(Get["sugar"]);
		sleep = std::stoi(Get["sleep"]);
		fat = std::stoi(Get["fat"]);
		calories = std::stoi(Get["calories"]);
		date = Get["date"];
		username = Get["username"];
    } else {
        cout << "<h1>Fill out the from and press submit!</h1>"<<endl;
    }	
    // Connect to database with: database, server, userID, password
    mysqlpp::Connection conn(false); // Exceptions suppressed to keep code
	// simple
    if(conn.connect("cse278", "localhost", "cse278", "MonSepM1am1")) {

        // Create a query
        mysqlpp::Query query = conn.query();
	query << "INSERT into 01789014Health (username, date, carbs,"
	" exercise, water, protein, sugar, sleep, fat, calories) VALUES"
	"('"+username+"', '"+date+"', %2q, %3q,"
	"%4q, %5q, %6q, %7q, %8q, "
	"%9q);";
		
        query.parse();  // check to ensure it is correct

        // Run the query -- note INSERT does not return results so we
		// are using SimpleResult
        mysqlpp::SimpleResult result = query.execute(username, date, carbs,
		exercise, water, protein, sugar, sleep, fat, calories);
        //mysqlpp::SimpleResult result = query.execute(username, password);
        mysqlpp::Query query2 = conn.query();

	query2 << "INSERT into 01789014Stats (username, carbs,"
	" exercise, water, protein, sugar, sleep, fat, calories) VALUES"
	"('"+username+"', %1q, %2q,"
	"%3q, %4q, %5q, %6q, %7q, "
	"%8q);";
	
	query2.parse();

	mysqlpp::SimpleResult result2 = query2.execute(username, carbs,
		exercise, water, protein, sugar, sleep, fat, calories);

	// Check to see if the queries were successful
	if(result && result2) {
            cout <<"<h1>Query was successful</h1>\n";
	    cout <<"<button class = \"button\" onclick=\"document."
		"location.href='insertion.html';\">Make Another Entry</button>" << endl;

        } else {
            cerr << "<p>Query error: " << query.error() << endl;
			cout << "<button class = \"button\" onclick=\"document."
			"location.href='insertion.html';\">Try Again</button>" << endl;
			cout << "<button class = \"button\" onclick=\"document."
			"location.href='index.html';\">Return to Home</button>" << endl;
        }
        return(0);
	}  else {
        cerr << "<p>Connection failed: " << conn.error() <<endl;
		cout << "<button class = \"button\" onclick=\"document."
			"location.href='index.html';\">Return to Home</button>" << endl;
        return(1);
    }
	
	cout << "</body></html>" << endl;
}
