make getpost: getpost.cpp getpost.h
	g++ -c getpost.cpp
make selection: getpost.o
	g++ -o selection.cgi selection.cpp getpost.o -lmysqlpp
make insertion: getpost.o
	g++ -o insertion.cgi insertion.cpp getpost.o -lmysqlpp
make password: getpost.o
	g++ -o password.cgi password.cpp getpost.o -lmysqlpp
make stats: getpost.o
	g++ -o stats.cgi stats.cpp getpost.o -lmysqlpp
make registration: getpost.o
	g++ -o registration.cgi registration.cpp getpost.o -lmysqlpp
clean:
	rm *.o