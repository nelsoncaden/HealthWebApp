// Copyright 2022 Caden Nelson
/*
 * This CGI script gets the post from form2.html. It then makes a connection
 * with the 278 database in order to check the username and password. If suc
 * cessful a button leading to the homepage of the website will be offered.
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

    // Initializes the get method
    map<string,string> Get;
    initializePost(Get);
    // Outputs the HTML
	cout << "Content-type: text/html" << endl << endl;
    cout << "<html>" << endl;
    // Outputs the embedded CSS
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
    // Outputs the login header and image html
    cout << "<div class = \"header\">" << endl;
    cout << "<h1>Login</h1>" << endl;
	cout << "</div>" << endl;
    cout << "<body>" << endl;
    cout << "<img src=\"sleep.jpg\">" << endl;

    std::string username;
    std::string password;

    // Declares username and password variables from database
    if (Get.find("username")!=Get.end() && Get.find("password")!=Get.end()) {
        username = Get["username"];
        password = Get["password"];
    } else {
        cout << "<p>Fill out the from and press submit"<<endl;
    }
	
    // Connect to database with: database, server, userID, password
    mysqlpp::Connection conn(false); // Exceptions suppressed to keep code
    // simple
    if(conn.connect("cse278", "localhost", "cse278", "MonSepM1am1")) {

        // Create a query
        mysqlpp::Query query = conn.query();
		
		query << "SELECT password, username FROM 01789014Users;";
		
        query.parse();  // check to ensure it is correct

        // Run the query -- note INSERT does not return results so we are using
        // SimpleResult
        mysqlpp::StoreQueryResult result = query.store();
        //mysqlpp::SimpleResult result = query.execute(username, password);

        // Always check for errors
        if(result) {
            cout <<"<p>Query success...\n";
            // Confirms username matches
			bool in = false;
            // Confirms the username and password are correct
			for(int i = 0; i < result.num_rows(); i++) {
				std::string user = result[i]["username"].c_str();
				std::string pass = result[i]["password"].c_str();
				if (username == user && password == pass) {
					in = true;
					cout << "Correct username and password\n";
					cout << "<button class = \"button\" onclick=\"document."
					"location.href='index.html';\">Enter "
                    "site</button>" << endl;
				} 
			}
			if (in == false) {
					cout << "<p>Incorrect credentials..." << endl;
					cout << "<button class = \"button\" onclick=\"document.loc"
					"ation.href='form2.html';\">Try again</button>" << endl;
			}
        } else {
            // If query was unsuccessful, gives option to try again
            cerr << "<p>Query error: " << query.error() << endl;
            cout << "<button class = \"button\" onclick=\"document.loc"
			"ation.href='form2.html';\">Oops! Try again</button>" << endl;
        }
        return(0);
    } else {
        // If could not connect to database, gives option to try again
        cerr << "<p>Connection failed: " << conn.error() <<endl;
        cout << "<button class = \"button\" onclick=\"document.loc"
		"ation.href='form2.html';\">Oops! Try again</button>" << endl;
        return(1);
    }
	// Outputs final HTML
	cout << "</body></html>" << endl;
}
