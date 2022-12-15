# HealthWebApp
The objective of this web application is to provide resources for logging and viewing daily health habits. This may be useful to
anyone interested in eating, sleeping, and exercising well (as a matter of lifestyle). More specifically, the user may make a daily
log, view all of their logs (ordered by date), or view the average of the entirety of their logs. I created 7 HTML files with embedded
CSS. There are also 5 CGI scripts written in C++. A makefile is provided for compiling the CGI scripts.

The landing page (welcome.html) gives two options: login (another webpage,
form2.html, with form with CGI script, password.cpp) or register (another webpage, register.html, with form with CGI script,
registration.cpp). Once admitted and entered to the homepage, the user is allowed three options: make a daily health log (another
webpage with form with CGI script), view past health logs (another webpage with form with CGI script), or view the average
values of past logs (another webpage with form with CGI script). I have included three database tables: 01789014Users (includes
data from registration, such as email, name, and address, and facilitates login), 01789014Health (includes data from daily health
logs, such as date, carbs, and hours of sleep, and facilitates viewing daily health logs), 01789014Stats (also includes data from
daily health logs, such as diet, exercise, etc., and facilitates viewing average of health logs (with help from AVG() function).
Please word document for mysql tables and png file for architecture diagram.
