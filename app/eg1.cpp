#include<tmwp>
#include<iostream>
#include<string.h>
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
cout<<"divyansh choudhary is here "<<endl;
//check for password and username in the file
//if it doesn't exist
//throw error username and password doesn't exist
//invalid username and invalid password
//if everthing is fine ,forward '1' from server side
//write the data in the file
if(username.compare("admin")==0 && password.compare("admin")==0)
{
response.write("1");
}
else
{
response.write("Invalid Username and Password");
}
response.close();
}



class Patient
{
public:
char name[200];
char gender[10];
char panNumber[200];
char aadharCardNumber[200];
char date[10];
bool isIndian;
char disease[200];
char doctorName[200];
char fatherName[200];
char MotherName[200];
char dateOfBirth[200];
char time[200];
bool isInsured;
char appointmentTime[200];
void setName(string name)
{
int i=0;
for(i=0;i<name.length();i++)
{
this->name[i]=name[i];
}
this->name[i]='\0';
}
char* getName()
{
return this->name;
}
void setDateOfBirth(string dateOfBirth)
{
int i=0;
for(i=0;i<dateOfBirth.length();i++)
{
this->dateOfBirth[i]=dateOfBirth[i];
}
this->dateOfBirth[i]='\0';


}
void setTime(string time)
{
int i=0;
for(i=0;i<time.length();i++)
{
this->time[i]=time[i];
}
this->time[i]='\0';

}
void setPanNumber(string panNumber)
{
int i=0;
for(i=0;i<panNumber.length();i++)
{
this->panNumber[i]=panNumber[i];
}
this->panNumber[i]='\0';

}
void setAadharCardNumber(string aadharCardNumber)
{
int i=0;
for(i=0;i<aadharCardNumber.length();i++)
{
this->aadharCardNumber[i]=aadharCardNumber[i];
}
this->aadharCardNumber[i]='\0';

}
void setGender(string gender)
{
int i=0;
for(i=0;i<gender.length();i++)
{
this->gender[i]=gender[i];
}
this->gender[i]='\0';

}
void setIsIndian(bool isIndian)
{
this->isIndian=isIndian;
}
void setdoctorName(string doctorName)
{
int i=0;
for(i=0;i<doctorName.length();i++)
{
this->doctorName[i]=doctorName[i];
}
this->doctorName[i]='\0';

}
void setFatherName(string fatherName)
{
int i=0;
for(i=0;i<fatherName.length();i++)
{
this->fatherName[i]=fatherName[i];
}
this->fatherName[i]='\0';

}
void setMotherName(string MotherName)
{
int i=0;
for(i=0;i<MotherName.length();i++)
{
this->MotherName[i]=MotherName[i];
}
this->MotherName[i]='\0';

}
void setDisease(string disease)
{
int i=0;
for(i=0;i<disease.length();i++)
{
this->disease[i]=disease[i];
}
this->disease[i]='\0';

}
bool getIsIndian()
{
return this->isIndian;
}
void setIsInsured(bool isInsured)
{
this->isInsured=isInsured;
}
bool getIsInsured()
{
return this->isInsured;
}
};







void addPatient(Request &request,Response &response)
{

string name=request.get("name");
string gender=request.get("gender");
string date=request.get("date");
string panCardNumber=request.get("panCardNumber");
string aadharCardNumber=request.get("aadharCardNumber");
string isIndian=request.get("isIndian");
string isInsured=request.get("isInsured");
string doctorName=request.get("doctorName");
string fatherName=request.get("fatherName");
string MotherName=request.get("MotherName");
string disease=request.get("disease");
string time=request.get("appointmentTime");
Patient patient;

if(isIndian.compare("2")==0)
{
patient.setIsIndian(false);
}
else
{
patient.setIsIndian(true);
}

if(isInsured.compare("2")==0)
{
patient.setIsInsured(false);
}
else
{
patient.setIsInsured(true);
}
if(gender.compare("1")==0)
{
patient.setGender("M");
}
else
{
patient.setGender("F");
}

patient.setName(name);
patient.setdoctorName(doctorName);
patient.setFatherName(fatherName);
patient.setMotherName(MotherName);
patient.setDisease(disease);
patient.setTime(time);
patient.setDateOfBirth(date);
patient.setPanNumber(panCardNumber);
patient.setAadharCardNumber(aadharCardNumber);



ofstream file_obj;
file_obj.open("Input.text", ios::app|ios::binary);
file_obj.write((char*)&patient, sizeof(patient));
file_obj.close();
response.write("1");
cout<<"response is closed "<<endl;
response.close();
}
void getPatient(Request &request,Response &response)
{
Patient p;
ifstream k("Input.text",ios::in|ios::binary);
if(k.fail())
{
response.write("2");
response.close();
return;
}
Patient p1;
k.read((char*)&p1,sizeof(p1));
response.write(p1.name);
response.write(",");
response.write(p1.fatherName);
response.write(",");
response.write(p1.MotherName);
response.write(",");
response.write(p1.doctorName);
response.write(",");
response.write(p1.disease);
response.write(",");
response.write(p1.time);
response.write(",");
response.write(p1.dateOfBirth);
response.write(",");
response.write(p1.gender);
response.write(",");
response.write("Yes");
response.write(",");
response.write("Yes");
response.write(",");
response.write(p1.panNumber);
response.write(",");
response.write(p1.aadharCardNumber);
while(1)
{
Patient p;
k.read((char*)&p,sizeof(p));
if(k.fail()) 
{
break;
}
response.write(",");
response.write(p.name);
response.write(",");
response.write(p.fatherName);
response.write(",");
response.write(p.MotherName);
response.write(",");
response.write(p.doctorName);
response.write(",");
response.write(p.disease);
response.write(",");
response.write(p.time);
response.write(",");
response.write(p.dateOfBirth);
response.write(",");
response.write(p.gender);
response.write(",");
response.write("Yes");
response.write(",");
response.write("Yes");
response.write(",");
response.write(p.panNumber);
response.write(",");
response.write(p.aadharCardNumber);
}
k.close();
response.close();
}
void deletePatient(Request &request,Response &response)
{
cout<<"Delete Patient method got called "<<endl;
ifstream k("Input.text",ios::in|ios::binary);
ofstream k1("Input.ccc",ios::app|ios::binary);
if(k.fail())
{
response.write("INVALID AADHARCARD NUMBER");
response.close();
return;
}
string aadharCardNumber=request.get("aadharCardNumber");
while(1)
{
Patient p;
k.read((char*)&p,sizeof(p));
if(k.fail()) break;
string s(p.aadharCardNumber);
if(s.compare(aadharCardNumber)!=0)
{
k1.write((char*)&p, sizeof(p));
}
}
k1.close();
k.close();
remove("Input.text");
ifstream k2("Input.ccc",ios::in|ios::binary);
ofstream k3("Input.text",ios::app|ios::binary);
while(1)
{
Patient p;
k2.read((char*)&p,sizeof(p));
if(k2.fail()) break;
k3.write((char*)&p, sizeof(p));
}
k2.close();
k3.close();
remove("Input.ccc");
response.write("1");
response.close();
}
void createAccount(Request &request,Response &response)
{
response.write("1");
response.close();
}
using namespace tmwp;
int main()
{
//Use 'admin' for username and password
TMWEBProjector server(8080);
//8080 is our port number
server.onRequest("/register",doSomething);
server.onRequest("/login",add);
server.onRequest("/addPatient",addPatient);
server.onRequest("/patient",getPatient);
server.onRequest("/deletePatient",deletePatient);
server.onRequest("/createAccount",createAccount);
server.start();
return 0;
}