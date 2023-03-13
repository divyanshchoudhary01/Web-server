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

//____________getMIMEType for particular resource file extention
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
/*if(extentionEquals(resource+lastIndexOfDot+1,"png"))
{
mimeType=(char *)malloc(sizeof(char)*10);
strcpy(mimeType,"image/png");
}*/

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
/*if(extentionEquals(resource+lastIndexOfDot+1,"ico"))
{
mimeType=(char *)malloc(sizeof(char)*13);
strcpy(mimeType,"image/x-icon");
}*/
/*if(extentionEquals(resource+lastIndexOfDot+1,"jpeg") || extentionEquals(resource+lastIndexOfDot+1,"jpg"))
{
mimeType=(char *)malloc(sizeof(char)*11);
strcpy(mimeType,"image/jpeg");
}*/

printf("getMIMEType : (%s)\n",mimeType);

return mimeType;
}

//______________yet to be discussed
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
int main()
{
FILE *f;
int len;
char g;
int i;
char requestbuffer[8192];//__________1024*8+1=    8192+1=8193 (1024 )
char responseBuffer[1025]; //____________1024 bytes in a CHUNK and 1 Byte for '\0'
char responseLength[24];
int serverSocketDescriptor;
int clientSocketDescriptor;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
WSADATA wsaData;
WORD ver;
ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
bind(serverSocketDescriptor,(struct sockaddr*)&serverSocketInformation,sizeof(serverSocketInformation));
listen(serverSocketDescriptor,10);
printf("TMWebProjector is ready accept on PORT number 5050\n");
len=sizeof(clientSocketInformation);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr*)&clientSocketInformation,&len);
int bytes;
bytes=recv(clientSocketDescriptor,requestbuffer,8192,0);
printf("%s",requestbuffer);
if(bytes<0)
{
}
if(bytes==0)
{
}
else
{
requestbuffer[bytes]='\0';
REQUEST *request=parseRequest(requestbuffer);
if(request->isClientSideTechnologyResource=='Y')
{
if(request->resource==NULL)
{
f=fopen("index.html","r");
if(f==NULL)
{
printf("Divyansh");
f=fopen("index.htm","r");
}
if(f==NULL)
{
strcpy(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-length:163\n\n<DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Tm web projector</title></head><body><h2 style='color:red'>Resource/not found</h2></body></html>");
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
}
else
{
fseek(f,0,2);
int length=ftell(f);
fseek(f,0,0);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: %d\nKeep-Alive: timeout=5, max=1000\n\n",length);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
i=0;
while(1)
{
g=getc(f);
if(feof(f))
{
printf("Divyansh1");
responseBuffer[i]='\0';
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
break;
}
responseBuffer[i++]=g;
if(i==1024)
{
printf("Divyansh2");
responseBuffer[i]='\0';
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
i=0;
}
}
fclose(f);
}
}
else
{
}
}
}
//send(clientSocketDescriptor,response,strlen(response)+1,0);
closesocket(clientSocketDescriptor);
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}