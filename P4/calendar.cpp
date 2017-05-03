// Author: Sean Davis
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "calendar.h"
#include "day.h"

using namespace std;

Calendar::Calendar(): days(NULL), size(30), count(0)
{
    days = new Day[30];
} // create()

void Calendar::dateSearch() const 
{
  int day = -1, month = -1, year = -1;
  getDate(&day, &month, &year);
  Day dayTemp(day, month, year);
  
  for(int i = 0; i < count; i++)
    if(days[i].equal(&dayTemp))
    {
      days[i].print();
      return;
      
    } // if found matching date
  
  cout << "That date was not found.\n";
}  // dateSearch()


Calendar::~Calendar()
{   
  if (days)
    delete [] days;
}  // destroy()


void Calendar::getDate(int *day, int *month, int *year) const
{
  while(true)
  {
    char line[80], line2[80], *ptr;
    cout << "\nPlease enter the month, day, and year (mm/dd/yyyy) >> ";
    
    if (! fgets(line, 80, stdin))
      cout << " is not a valid date.\nPlease try again.\n";
    else // User entered something
    {
      strtok(line, "\n");
      strcpy(line2, line);
      ptr = strtok(line, "/");
      
      if(ptr)
      {
        *month = atoi(ptr);
        ptr = strtok(NULL, "/");
        
        if(ptr)
        {
          *day = atoi(ptr);
          ptr = strtok(NULL, "\n");
          
          if(ptr)
            *year = atoi(ptr);
        } // if something before a second /
      } // if something before the first /
      
      if(*day >= 1 && *day <= 31 && *month >= 1 && *month <= 12 
         && *year >= 1000 && *year <= 2017)
         break;
      
      cout << line2 << " is not a valid date.\nPlease try again.\n";
    } // else use entered something
  } // while invalid date
}  // getDate()

void Calendar::readFile()
{
  ifstream inf("appts.csv");
  char line[80];
  int day, month, year, pos;
  inf.getline(line, 80);  // get rid of label line;
  
  while(inf.getline(line, 80))
  {
    month = atoi(strtok(line, "/"));
    day = atoi(strtok(NULL, "/"));
    year = atoi(strtok(NULL, ","));
    Day dayTemp(day, month, year);
    
    for(pos = 0; 
      pos < count && !dayTemp.equal(&days[pos]); pos++);
    
    if(pos == count) // not found
    {
      if(count == size)
        resize();
      
      for(pos = count - 1; 
        pos >= 0 && dayTemp.lessThan(&days[pos]); pos--)
          days[pos + 1] = days[pos];
      
      days[++pos] = dayTemp;  // copy the new day into pos + 1
      count++;
      
    } // if not found
    
    days[pos].read();
    
  } // while more lines in the file
  
  inf.close();
}  // readFile()

void Calendar::resize()
{
  Day *temp = new Day[size * 2];
  
  for(int i = 0; i < count; i++)
    temp[i] = days[i];
  
  delete [] days;
  days = temp;
  size *= 2;
}  // resize()


void Calendar::subjectSearch() const
{
  char subject[80];
  cout << "Please enter the subject >> ";
  fgets(subject, 80, stdin);
  
  if(strlen(subject) > 0)
    subject[strlen(subject) - 1] = '\0';  // eliminate the '\n'
  
  cout << "Date                          Start End   Subject      Location\n";
  
  for(int i = 0; i < count; i++)
    days[i].subjectSearch(subject);
  
  cout << "\n";
}  // subjectSearch()

void replaceNULL(char* newStr)
{
    int i = strlen(newStr);
    
    newStr[i - 1] = '\0';
    
} //replaces \n with \0

void Calendar::addAppointment()
{
    char subject1[30], location1[30], starTime[6], endTime[6], newStr[80];
    int day = -1, month = -1, year = -1;
    
    getDate(&day, &month, &year);
    Day newDay(day, month, year);
    
    cout << "Subject >> ";
    fgets(subject1, 30, stdin);
    replaceNULL(subject1);
    cout << "Location >> ";
    fgets(location1, 30, stdin);
    replaceNULL(location1);
    
    cout << "Start time (hh:mm) >> ";
    cin >> starTime;
    cout << "End time (hh:mm) >> ";
    cin >> endTime;
    
    strcpy(newStr, "0:");
    strcat(newStr, subject1);
    strcat(newStr, ",");
    strcat(newStr, starTime);
    strcat(newStr, ":00 FM,");
    strcat(newStr, endTime);
    strcat(newStr, ":00 FM,");
    strcat(newStr, location1);
    
    int pos = atoi(strtok(newStr, ":"));
    
    for(pos = 0; 
      pos < count && !newDay.equal(&days[pos]); pos++);
    
    if(pos == count) // not found
    {
      if(count == size)
        resize();
      
      for(pos = count - 1; 
        pos >= 0 && newDay.lessThan(&days[pos]); pos--)
          days[pos + 1] = days[pos];
      
      days[++pos] = newDay;  // copy the new day into pos + 1
      count++;
      
    } // if not found
    
    days[pos].read();
    
}//