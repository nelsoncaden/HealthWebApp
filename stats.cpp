// Copyright 2022 Caden Nelson
/* This CGI script selects data from Stats table in database and displays
 * it on the html page. There will only be one HTML row for this table
 * besides the header row.
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
	// Establish get map
    map<string,string> Get;
    initializePost(Get);
	// Outputs the html
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
	cout << "td, th {" << endl;
	cout << "border: 1px solid #000;" << endl;
	cout << "padding: 8px;" << endl;
	cout << "}" << endl;
	cout << "th {" << endl;
    cout << "padding: 15px;" << endl;
    cout << "text-align: left;" << endl;
    cout << "background-color: #001030;" << endl;
    cout << "color: white;" << endl;
	cout << "}" << endl;
	// Outputs the rest of the HTML
    cout << "</style>" << endl;
    cout << "<div class=\"header\">" << endl;
	cout << "<h1>Let's see some stats about your health!</h1>" << endl;
	cout << "</div>" << endl;
	cout << "<img src=\"biker.jpg\">" << endl;
	
	std::string username;

	// Finds username value and saves it to username variable
    if (Get.find("username")!=Get.end()) {
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
		
	query << "SELECT CAST(AVG(carbs) AS UNSIGNED), CAST(AVG(exercise) "
	"AS UNSIGNED), CAST(AVG(water) AS UNSIGNED), CAST(AVG(protein) AS "
	"UNSIGNED), CAST(AVG(sugar) AS UNSIGNED), CAST(AVG(sleep) AS UNSIGNED),"
	"CAST(AVG(fat) AS UNSIGNED), CAST(AVG(calories) AS UNSIGNED) FROM 017890"
	"14Stats WHERE username = '"+username+"';";
		
        query.parse();  // check to ensure it is correct

        // Run the query -- note INSERT does not return results so we
		// are using SimpleResult
        mysqlpp::StoreQueryResult result = query.store();
        //mysqlpp::SimpleResult result = query.execute(username, password);
	
        // Always check for errors
        if(result) {
			// Outputs header row
            cout <<"<p>Query success...\n";
			cout <<"<h1>Average of the Logs is Visible Below</h1>" << endl;
			cout << "<table>" << endl;
			cout << "<tr>" << endl;
			cout << "<th>Carbs</th>" << endl;
			cout << "<th>Exercise</th>" << endl;
			cout << "<th>Water</th>" << endl;
			cout << "<th>Protein</th>" << endl;
			cout << "<th>Sugar</th>" << endl;
			cout << "<th>Sleep</th>" << endl;
			cout << "<th>Fat</th>" << endl;
			cout << "<th>Calories</th>" << endl;
			cout << "</tr>" << endl;
			cout << "<tr>" << endl;
			// Initializes variables with data from stats database
			int carbs = result[0]["CAST(AVG(carbs) AS UNSIGNED)"];
			int exercise = result[0]["CAST(AVG(exercise) AS UNSIGNED)"];
			int water = result[0]["CAST(AVG(water) AS UNSIGNED)"];
			int protein = result[0]["CAST(AVG(protein) AS UNSIGNED)"];
			int sugar = result[0]["CAST(AVG(sugar) AS UNSIGNED)"];
			int sleep = result[0]["CAST(AVG(sleep) AS UNSIGNED)"];
			int fat = result[0]["CAST(AVG(fat) AS UNSIGNED)"];
			int calories = result[0]["CAST(AVG(calories) AS UNSIGNED)"];
			// Outputs other row
			cout << "<td> " << carbs << " grams</td>" << endl;
			cout << "<td> " << exercise << " minutes</td>" << endl;
			cout << "<td> " << water << " cups</td>" << endl;
			cout << "<td> " << protein << " grams</td>" << endl;
			cout << "<td> " << sugar << " grams</td>" << endl;
			cout << "<td> " << sleep << " hours</td>" << endl;
			cout << "<td> " << fat << " grams</td>" << endl;
			cout << "<td> " << calories << "</td>" << endl;
			cout << "</tr>" << endl;
			cout << "</table>" << endl;
			cout << "<button class =\"button\" onclick=\"document.location.href"
				"='index.html';\">Return to Home</button>" << endl;
        } else {
			// If query error, gives option to try again
            cerr << "<p>Query error: " << query.error() << endl;
		cout << "<p>Query error: " << query.error() << endl;
			cout << "<button class =\"button\" onclick=\"document.location.hr"
	"ef='index.html';\">Return to Home</button>" << endl;
        }
        return(0);
    } else {
		// If connection failed, gives option to try again
        cerr << "<p>Connection failed: " << conn.error() <<endl;
		cout << "<button class =\"button\" onclick=\"document.location.hr"
	"ef='index.html';\">Return to Home</button>" << endl;
        return(1);
    }
	// Outputs the final HTML
	cout << "<button class =\"button\" onclick=\"document.location.hr"
	"ef='index.html';\">Return to Home</button>" << endl;
	cout << "</html>" << endl;
}
