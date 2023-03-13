#include<windows.h>
#include<stdio.h>
#include<stdlib.h>

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



typedef struct _request
{
char *resource;
char *method;
char isClientSideTechnologyResource;
char *mimeType;
}REQUEST;

//____________for incase sensitive comparision
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
printf("Resource : %s \n",resource);
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
printf("getMIMEType : (%s)\n",mimeType);
return mimeType;
}
char isClientSideResource(char * resource)
{
return 'Y';
}

//_______Extracting information from request
REQUEST * parseRequest(char *requestBuffer)
{
char method[11];
char resource[1001];
REQUEST *request;
request=(REQUEST *)malloc(sizeof(REQUEST));
int i,j;
for(i=0;requestBuffer[i]!=' ';i++) method[i]=requestBuffer[i];
method[i]='\0';
printf("method : %s\n",method);
request->method=(char *)malloc((sizeof(char)*strlen(method))+1);
strcpy(request->method,method);
i+=2; //for crossing (/) slash

for(j=0;requestBuffer[i]!=' ';j++,i++) resource[j]=requestBuffer[i];

resource[j]='\0';
printf("resource : (%s)\n",resource);

if(resource[0]=='\0')
{
request->resource=NULL;
request->isClientSideTechnologyResource=isClientSideResource(resource);
request->mimeType=NULL;
}
else
{
request->resource=(char *)malloc((sizeof(char) * strlen(resource))+1);
strcpy(request->resource,resource);
request->isClientSideTechnologyResource=isClientSideResource(resource);
request->mimeType=getMIMEType(resource);
}
return request;
}
void  start()
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
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
//____Binding server to port
successBytes=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));

//_____Server is in listening mode
listen(serverSocketDescriptor,10);
while(1)
{
printf("TMWebProjector is ready accept on PORT number 5050\n");
//______Server is ready to accept request
len=sizeof(clientSocketInformation);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);
//________Receiving REQUEST from webBrowser
bytes=recv(clientSocketDescriptor,requestBuffer,8192,0);
if(bytes<0)
{
}
if(bytes==0)
{
}
else
{
requestBuffer[bytes]='\0';
REQUEST *request=parseRequest(requestBuffer);
if(request->isClientSideTechnologyResource=='Y')
{
if(request->resource==NULL)
{
f=fopen("index.html","rb");
if(f==NULL)
{
f=fopen("index.htm","r");
}
if(f==NULL)
{
Error404(clientSocketDescriptor);
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
}
}
else
{
f=fopen(request->resource,"rb");
if(f==NULL)
{
char header[201];
char response[501];
sprintf(response,"<!DOCTYPE HTML><html lang='en<head><meta charset='utf-8'><title>Error 404</title></head><body><h1 style='color:black'>Resource not found: %s</h1></body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\n\n",strlen(response));
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
send(clientSocketDescriptor,response,strlen(response)+1,0);
//Error404(clientSocketDescriptor);
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
}//else part when file does exist

}//else when there is a resource

}//if client side technology





}//else part when there is bytes in the request

}//while loop

closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}