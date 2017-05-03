// Author: Sean Davis

#include <iostream>
#include <iomanip>
#include <string.h>
#include "appt.h"
#include "time.h"

using namespace std;

Appointment::Appointment(): subject(NULL), location(NULL)
{
    
}//Appointment standard constructor

Appointment::Appointment(const Appointment &rhs): startTime(rhs.startTime),
        endTime(rhs.endTime)
{
    
    if(rhs.subject)
    {
      subject = new char[strlen(rhs.subject) + 1];
      strcpy(subject, rhs.subject);
      
    }//copies subject 
    
    if(rhs.location)
    {
      location = new char[strlen(rhs.location) + 1];  
      strcpy(location, rhs.location);
      
    }//copies location

}//Appointment copy constructor


Appointment::~Appointment()
{
    
    if (subject)
      delete [] subject;
      
    if (location)  
      delete [] location;
      
}  // Appointment destructor


bool Appointment::equal(const char *subject2)const
{
  return strstr(subject, subject2) != NULL;
}  // equal()


bool Appointment::lessThan(const Appointment *appointment2) const
{
  return startTime.lessThan(&appointment2->startTime); 
}  // lessThan()


void Appointment::print() const
{
  startTime.print();
  endTime.print();
  cout << left << setw(13) << subject << location << right << endl;
} // print()


/*int Appointment::getCount()
{
    return count;
} //gets count*/

void Appointment::read()
{
  char *ptr;
  ptr = strtok(NULL, ",");
  subject = new char[strlen(ptr) + 1];
  strcpy(subject, ptr);
  startTime.read();
  endTime.read();
  ptr = strtok(NULL, "\n");
  location = new char[strlen(ptr) + 1];
  strcpy(location, ptr);
} // read()

