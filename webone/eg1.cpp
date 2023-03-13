#include<tmwp>
#include<iostream>
using namespace std;
void doSomething(Request &request,Response &response)
{
cout<<"Method doSomething got called"<<endl;
}
void add(Request &request,Response &response)
{
string username=request.get("username");
string password=request.get("password");
cout<<"Username value is "<<username<<endl;
cout<<"Password value is "<<password<<endl;
cout<<"LoginMethod got called"<<endl;
request.forward("/login.html");
}
using namespace tmwp;
int main()
{
TMWEBProjector server(8080);
server.onRequest("/register",doSomething);
server.onRequest("/login",add);
//server.onRequest("/Logout",Logout);

server.start();
return 0;
}