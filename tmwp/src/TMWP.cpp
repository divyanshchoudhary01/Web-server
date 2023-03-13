#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<bits/stdc++.h>
#include<tmwp>
using namespace tmwp;
using namespace std;
Response::Response(int clientSocketDescriptor)
{
this->clientSocketDescriptor=clientSocketDescriptor;
this->isClosed=false;
}
Response::Response()
{
this->isClosed=false;
}
void Response::close()
{
if(this->isClosed) return;
this->isClosed=true;
closesocket(this->clientSocketDescriptor);
this->headerCreated=false;
}
void Response::createHeader()
{
//changes needs to be done here
char header[51];
char responseBuffer[1000];
this->headerCreated=true;
strcpy(header,"HTTP/1.1 200 OK\nContent-Type:text/html\n\n");
send(this->clientSocketDescriptor,header,strlen(header),0);
}
void Response::write(const char *str)
{
if(str==NULL) return;
int len=strlen(str);
if(len==0) return;
if(!this->headerCreated) createHeader();
send(this->clientSocketDescriptor,str,len,0);
}
void Request::forward(string forwardRequest)
{
this->forwardRequest=forwardRequest;
}





void parseString(string s,map<string,string> &m1)
{
bool letgetEqual=true;
vector<string> v;
int count=0;
while(1)
{
if(s.length()==0) break;
if(letgetEqual==true)
{
int found1=s.find("=");
string n=s.substr(0,found1);
v.push_back(n);
count++;
s.erase(0,found1+1);
letgetEqual=false;
}
else if(letgetEqual==false)
{
int found1=s.find("&");
if(found1==-1)
{
string n=s.substr(0,s.length());
v.push_back(n);
count++;
if(count==2)
{
m1.insert(pair<string,string>(v[0],v[1]));
count=0;
v.clear();



}
s.erase(0);
letgetEqual=true;
continue;
}
string n=s.substr(0,found1);
v.push_back(n);
count++;
s.erase(0,found1+1);
letgetEqual=true;
}
if(count==2)
{
m1.insert(pair<string,string>(v[0],v[1]));
count=0;
v.clear();
}
}
if(count==1)
{
m1.insert(pair<string,string>(v[0]," "));
}
}
int HexadecimalToDecimal(string hex) 
{
int hexLength = hex.length();
double dec = 0;
for (int i = 0; i < hexLength; ++i)
{
char b = hex[i];
if (b >= 48 && b <= 57) b -= 48;
else if (b >= 65 && b <= 70) b -= 55;
dec += b * pow(16, ((hexLength - i) - 1));
}
return (int)dec;
}
static string DecodeURL(string data) 
{
string result;
int dataLen=data.length();
for(int i = 0; i < dataLen; ++i)
{
if(data[i]=='%')
{
result +=(char)HexadecimalToDecimal(data.substr(i + 1, 2));
i+=2;
}
else
{
result+=data[i];
}
}
return result;
}
void Error404(int clientSocketDescriptor)
{
char header[201];
char response[501];
strcpy(response,"<!DOCTYPE HTML>");
strcat(response,"<html lang='en'>");
strcat(response,"<head>");
strcat(response,"<meta charset='utf-8'>");
strcat(response,"<title>Error 404</title>");
strcat(response,"</head>");
strcat(response,"<body>");
strcat(response,"<h1 style='color:red'>404 File Not Found</h1>");
strcat(response,"</body>");
strcat(response,"</html>");
sprintf(header,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\n\n",strlen(response));
send(clientSocketDescriptor,header,strlen(header),0);
send(clientSocketDescriptor,response,strlen(response)+1,0);
}
void Request:: setMap(map<string,string> &m)
{
this->m=m;
}
map<string,string> Request:: getMap()
{
return this->m;
}
void Request:: setIsClientSideTechnologyResource(bool isClientSideTechnologyResource)
{
this->isClientSideTechnologyResource=isClientSideTechnologyResource;
}
bool Request:: getIsClientSideTechnologyResource()
{
return this->isClientSideTechnologyResource;
}
void Request:: setMimeType(string mimeType)
{
this->mimeType=mimeType;
}
string Request:: getMimeType()
{
return this->mimeType;
}
void Request:: setMethod(string method)
{
this->method=method;
}
string Request:: getMethod()
{
return this->method;
}
void Request:: setResource(string resource)
{
this->resource=resource;
}
string Request:: getResource()
{
return this->resource;
}

void Request:: setData(string data)
{
this->data=data;
}
string Request:: get(string data)
{
auto itr=this->m.find(data);
if(itr!=m.end()) return (itr)->second;
return "";
} 


string Response:: getWrite()
{
return k;
}


int extentionEquals(char *left,const char *right)
{
char a,b;
while(*left && *right)
{
a=*left;
b=*right;
if(a>=65 && a<=90) a+=32;
if(b>=65 && b<=90) b+=32;
if(a!=b) return 0;
left++;
right++;
}
return *left==*right;
}
char * getMIMEType(char * resource)
{
char *mimeType;
mimeType=NULL;
int len=strlen(resource);
if(len < 4)
{
return mimeType;
}
int lastIndexOfDot=len-1;
while(lastIndexOfDot >0 && resource[lastIndexOfDot]!='.') lastIndexOfDot--;
if(lastIndexOfDot==0) return mimeType;
if(extentionEquals(resource+lastIndexOfDot+1,"html"))
{
mimeType=(char *)malloc(sizeof(char)*10);
strcpy(mimeType,"text/html");
}
if(extentionEquals(resource+lastIndexOfDot+1,"png"))
{
mimeType=(char *)malloc(sizeof(char)*10);
strcpy(mimeType,"image/png");
}
if(extentionEquals(resource+lastIndexOfDot+1,"css"))
{
mimeType=(char *)malloc(sizeof(char)*9);
strcpy(mimeType,"text/css");
}
if(extentionEquals(resource+lastIndexOfDot+1,"js"))
{
mimeType=(char *)malloc(sizeof(char)*16);
strcpy(mimeType,"text/javascript");
}
if(extentionEquals(resource+lastIndexOfDot+1,"ico"))
{
mimeType=(char *)malloc(sizeof(char)*13);
strcpy(mimeType,"image/x-icon");
}
if(extentionEquals(resource+lastIndexOfDot+1,"jpeg") || extentionEquals(resource+lastIndexOfDot+1,"jpg"))
{
mimeType=(char *)malloc(sizeof(char)*11);
strcpy(mimeType,"image/jpeg");
}
return mimeType;
}
char isClientSideResource(char * resource)
{
int i=0;
for(i=0;resource[i]!='\0' && resource[i]!='.';i++);
if(resource[i]=='\0') return 'N';
return 'Y';
}
Request parseRequest(char *bytes,Request &request1,Response &response1)
{
char method[11];
char resource[1001];
int i,j;
for(i=0;bytes[i]!=' ';i++) method[i]=bytes[i];
method[i]='\0';
i+=2; //for crossing (/) slash
char **data=NULL;
int dataCount=0;
string finalData="";
map<string,string> m1;
if(strcmp(method,"GET")==0)
{
for(j=0;bytes[i]!=' ';j++,i++)
{
if(bytes[i]=='?') break;
resource[j]=bytes[i];
}
resource[j]='\0';
if(bytes[i]=='?')
{
i++;
while(bytes[i]!=' ')
{
finalData=finalData+bytes[i];
i++;
}
} // if(bytes[i]=='?')
if(finalData.length()!=0) finalData=DecodeURL(finalData);
if(finalData.length()!=0) parseString(finalData,m1);
}
request1.setMap(m1);
request1.setMethod(method);
if(resource[0]=='\0')
{
request1.setResource("");
if(isClientSideResource(resource)=='Y')
{
request1.setIsClientSideTechnologyResource(true);
}
else
{
request1.setIsClientSideTechnologyResource(false);
}
request1.setMimeType("");
}
else
{
request1.setResource(resource);
if(isClientSideResource(resource)=='Y')
{
request1.setIsClientSideTechnologyResource(true);
}
else
{
request1.setIsClientSideTechnologyResource(false);
}
const char *mim=getMIMEType(resource);
if(mim==NULL) request1.setMimeType("");
else request1.setMimeType(string(mim));
}
return request1;
}
TMWEBProjector::TMWEBProjector(int portNumber)
{
this->portNumber=portNumber;
this->url=NULL;
this->ptrOnRequest=NULL;
}
TMWEBProjector::~TMWEBProjector()
{
if(this->url) delete [] this->url;
}
void TMWEBProjector::onRequest(string url,void (*ptrOnRequest)(Request  &request,Response &response))
{
this->m.insert(pair<string,void(*)(Request &,Response &)>(url,ptrOnRequest));
}

void  TMWEBProjector::start()
{
WORD ver;
WSADATA wsaData;
int serverSocketDescriptor;
int clientSocketDescriptor;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
FILE *f;
int bytes,remBytes;
int len;
int i;
int successBytes;
int bytesExtracted;
char requestBuffer[8192];
char responseBuffer[1024];
char g;
int rc;
ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(this->portNumber);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
//Binding server to port
successBytes=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));

//Server is in listening mode
listen(serverSocketDescriptor,10);
while(1)
{
printf("TMWebProjector is ready accept on PORT number %d \n",this->portNumber);
//Server is ready to accept request
len=sizeof(clientSocketInformation);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);
//Receiving REQUEST from webBrowser
bytes=recv(clientSocketDescriptor,requestBuffer,8192,0);
if(bytes<0)
{
printf("Bytes value is %d\n",bytes);
}
if(bytes==0)
{
printf("Bytes value is %d\n",bytes);
}
else
{
requestBuffer[bytes]='\0';
Request request1;
Response response1(clientSocketDescriptor);
parseRequest(requestBuffer,request1,response1);
while(1) //infinite loop to enable the forwarding feature
{
if(request1.getIsClientSideTechnologyResource())
{
const char* ccx = request1.getResource().c_str();
char resource[1000];
string resource1=request1.getResource();
int e=0;
for(e=0;e<resource1.length();e++)
{
resource[e]=resource1[e];
}
resource[e]='\0';
f=fopen(ccx,"rb");
if(f==NULL)
{
char header[201];
char response[501];
sprintf(response,"<!DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Error 404</title></head><body><h1 style='color:black'>Resource not found: %s</h1></body></html>",resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\n\n",strlen(response));
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
send(clientSocketDescriptor,response,strlen(response)+1,0);
//Error404(clientSocketDescriptor);
break;
}
else
{
fseek(f,0,2);
int length=ftell(f);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %d\nKeep-Alive: timeout=5, max=1000\n\n",length);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
fseek(f,0,0);
i=0;
while(i<length)
{
rc=length-i;
if(rc>1024) rc=1024;
fread(&responseBuffer,rc,1,f);
send(clientSocketDescriptor,responseBuffer,rc,0);
i+=rc;
}
fclose(f);
closesocket(clientSocketDescriptor);
break;
}//else part when file does exist
//} //else part

}//if client side technology




else
{
//what to when it's server side resource
map<string,void (*)(Request &,Response &)>::iterator itr;
itr=this->m.find("/"+request1.getResource());
char response[501];
if(itr!=this->m.end())
{
char header[201];
this->ptrOnRequest=(*itr).second;
this->ptrOnRequest(request1,response1);
if(request1.forwardRequest.length()>0)
{
request1.setResource(request1.forwardRequest);
const char* cc= request1.getResource().c_str();
char *c1=(char *)cc;
if(isClientSideResource(c1)=='Y')
{
request1.setIsClientSideTechnologyResource(true);
}
else
{
request1.setIsClientSideTechnologyResource(false);
}
const char *mim=getMIMEType(c1);
if(mim==NULL) request1.setMimeType("");
else request1.setMimeType(string(mim));
continue;
}
break;
}
else if(request1.getResource()=="")
{//1
printf("5");
f=fopen("index.html","rb");
if(f==NULL)
{
printf("6");
f=fopen("index.htm","r");
}
if(f==NULL)
{
Error404(clientSocketDescriptor);
break; //to break from the forward loop
}
else
{
fseek(f,0,2);
int length=ftell(f);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %d\nKeep-Alive: timeout=5, max=1000\n\n",length);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
fseek(f,0,0);
i=0;
while(i<length)
{
rc=length-i;
if(rc>1024) rc=1024;
fread(&responseBuffer,rc,1,f);
send(clientSocketDescriptor,responseBuffer,rc,0);
i+=rc;
}
fclose(f);
closesocket(clientSocketDescriptor);
break; //to break from the forward loop
} //else part ends
} //else if part 1
else
{

cout<<"request resource value is "<<request1.getResource()<<endl;
const char* requestResource=request1.getResource().c_str();
sprintf(response,"<!DOCTYPE HTML><html lang='en><head><meta charset='utf-8'><title>Method Processed</title></head><body><h1 style='color:black'>Server Side Resource not found: %s</h1></body></html>",requestResource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\n\n",strlen(response));
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
send(clientSocketDescriptor,response,strlen(response)+1,0);
closesocket(clientSocketDescriptor);
break;
}











}



} //forwarding loop ends here


}//else part when there is bytes in the request

}//while loop

closesocket(serverSocketDescriptor);
WSACleanup();
return ;
}