# Web-server
 HTTP Web server in c++

I have developed  a web server in c++
with this webserver ,you can easily develop web applications
With this web server you can easily deploy your website 


This webserver offers certain functionalities/features. 

TMWEBProjector server(8080); There is a class of TMWEBProjector of which you have to create object
while creating object ,you have to pass a 'port Number' , on which the server will listen/handle the request (in background  socket will be bounded by this port number)

TMWebProjector has onRequest method in it's class
with onRequest method ,you can specify for particular URL 
for which particular resource should run on the server side or serve to the client
side 

while writing  functionality in our cpp file
the function should contain two parameters ,First one Request type and second
is Response Type .The functionality cannot return anything.
return type of the function is void
for example 
We have called onRequest() method of  TMWEBProjector class,where we will pass two 
arguments first one is the URL ie->"/register",and 
second thing is the function address/name that is doSomething
while defining the doSomething function ,we can give only two parameters
the return type of doSomething function will be void


Request class provides following methods/functionalities->
1) It contains forward method
with the help of forward method ,you can further forward request
2) It contains setInt() method
3) It contains setFloat() method
4) It contains setString() method


with above methods ,we can store the value,these value can be further access by the  forwarded request

5) It contains get() method . 

Return type of get Method is string whatever data comes from client side with request, you can easily fetch it using get() method available in the request class
suppose data come in the form of JSON format,which consists  {"username":"","Password":""}
and you want to verify the username and password in the server side
On the server side,you have to call get() method of Request class,while calling
the get method,you have to pass one argument ,whichever property value/data you want
to access which comes from client side


Response class provides following methods/functionalities->
1) It contains write method,with the help of write method ,you can send the response to the client side() with help of write method ,you can even send a html page
2) Close method available.


Web server works behind the scenes

what happens when a request comes from client side ?

how does the server start ?

TMWEBProjector server(8080) here,first we specified the port Number there is a start method present in the TMWEBProjector class
server.start()-> by this our server will start ,and will goes in listening mode on specified(by user) port Number, 


What happens in the background of the start() method ?

with the help of socket programming a socket will be created 

Things are required to make socket

1)Internet Family

we will be using IPV4 as Internet Family
AF_NET represents the value of IPV4

2) Communication Semantics

we will be passing number for communication semantics
that number will be represented by SOCK_STREAM

3) Protocol

In our case protocol will be TCP/IP
socket function will return anumber ,we will call it socketDescriptor
whatever work we will do,it will be done using socketDescriptor


We will bind the socket (with the help of socket descriptor) to an IP and port number with bind function,we are binding socket with IP and Port Number
Bind function will return a number .

After binding ,we are putting the socket in the listening mode ,here  we are specifying, how many request can come at a time.
after that ,there is infinite loop where accept method is being called. Due to accept method ,our socket will go in wait mode(waiting for the request to arrive)
whenever a new request will come from client side,to accept method,that request will be diverted and accept method will return us a new socket descriptor

first Response type object will be made,while making it,we will be passing 'SocketDescirptor'.With this socketDescriptor  response class object will able to send response to the client side(browser).

Now Request arrived from client side, It's parsing will be done,using requestParser method()
will be called ,In requestParser method , client Side request (method(GET/POST)) type , will be known
whether it's GET type request or POST type request ,decoding of data will be done
first ,then that data will parsed ,it's property and values will be stored in the map

Request type object will be made,
all these following properties of request class object will be set 
in requestParser method

1)resource,2)method,3)isClientSideTechnology ,4)mime Type,5)map

after requestParsing  
It will be checked whether it is client side resource or server side resource.
if it is client side resource ,then data in bytes will be sent to the server side
if it's server side resource ,then it will be checked  whether the request url,
is mapped with (functionality )server side resource,if 'yes',then server side
(resource) functionality will be executed on server end.
