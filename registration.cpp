// Copyright 2022 Caden Nelson
/*
 * This CGI script gets the post from register.html. It then makes a connection
 * with the 278 database in order to insert the data. HTML with embedded CSS is
 * included as output.
 * Author: Caden Nelson
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
	// Output HTML
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
	// Outputs the body of the html page
    cout << "<body>" << endl;
    cout << "<div class=\"header\">" << endl;
	cout << "<h1>Registration Form</h1>" << endl;
    cout << "</div>" << endl;
    cout << "<img src=\"table.jpg\">" << endl;
	cout << "<body>" << endl;
    cout << "<h2>Please input your info into the boxes below</h2>" << endl;
	cout << "<p>" << endl;

	// Declares the variables
    std::string username;
    std::string password;
	std::string firstname;
	std::string lastname;
	std::string email;
	std::string address;
	std::string city;
	std::string state;
	std::string zip;
	std::string country;

	// Initialize variables with data from the form
    if (Get.find("username")!=Get.end() && Get.find("password")!=Get.end() &&
		Get.find("firstname")!=Get.end() && Get.find("lastname")!=Get.end() &&
		Get.find("email")!=Get.end() && Get.find("address")!=Get.end() &&
		Get.find("city")!=Get.end() && Get.find("state")!=Get.end() &&
		Get.find("zip")!=Get.end() && Get.find("country")!=Get.end()) {
        username = Get["username"];
        password = Get["password"];
		firstname = Get["firstname"];
		lastname = Get["lastname"];
		email = Get["email"];
		address = Get["address"];
		city = Get["city"];
		state = Get["state"];
		zip = Get["zip"];
		country = Get["country"];
    } else {
        cout << "<h1>Fill out the from and press submit!</h1>"<<endl;
    }
	
    // Connect to database with: database, server, userID, password
    mysqlpp::Connection conn(false);  // Exceptions suppressed to keep code
	// simple
    if(conn.connect("cse278", "localhost", "cse278", "MonSepM1am1")) {

        // Create a query
        mysqlpp::Query query = conn.query();
				
		query << "INSERT into 01789014Users (username, password, firstname,"
		" lastname, email, address, city, state, zip, country) VALUES"
		"('"+username+"', '"+password+"', '"+firstname+"', '"+lastname+"',"
		" '"+email+"', '"+address+"', '"+city+"', '"+state+"', '"+zip+"', "
		"'"+country+"');";
		
        query.parse();  // check to ensure it is correct

        // Run the query -- note INSERT does not return results so we
		// are using SimpleResult
        mysqlpp::SimpleResult result = query.execute();
        //mysqlpp::SimpleResult result = query.execute(username, password);

        // Always check for errors
        if(result) {
            cout <<"<p>Query success...\n";
			cout << "<button class = \"button\" onclick=\"document."
			"location.href='form2.html';\">Login</button>" << endl;
        } else {
			// If query error, gives option to try again
            cerr << "<p>Query error: " << query.error() << endl;
	    cout << "<button class = \"button\" onclick=\"document.location"
		".href='register.html';\"Try Again</button>" << endl;
			cout << "<p>Already have an account?</p>" << endl;
			cout << "<button class = \"button\" onclick=\"document."
			"location.href='form2.html';\">Login</button>" << endl;
        }
        return(0);
    } else {
		// If connection with database failed, gives option to try again
        cerr << "<p>Connection failed: " << conn.error() <<endl;
	cout << "<button class = \"button\" onclick=\"document.location.href='re"
		"gister.html';\"Try Again</button>" << endl;
		cout << "<p>Already have an account?</p>" << endl;
			cout << "<button class = \"button\" onclick=\"document."
			"location.href='form2.html';\">Login</button>" << endl;
        return(1);
    }
	
	// Finish the HTML output
	cout << "</body></html>" << endl;
}
