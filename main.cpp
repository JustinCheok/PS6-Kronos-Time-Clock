/*

	Copyright[2021]
	Justin Cheok
	4/19/21

*/

#include <iostream>
#include <string>
#include <fstream>
#include <regex>

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/regex.hpp>

using namespace std;  // Maybe take out

using std::cout;
using std::cin;
using std::endl;
using std::string;

using boost::gregorian::date;
using boost::gregorian::from_simple_string;
using boost::gregorian::date_period;
using boost::gregorian::date_duration;

using boost::posix_time::ptime;
using boost::posix_time::time_duration;


date from_string(const std::string&);

int main(int argc, char *argv[]) {
fstream logFile;
logFile.open(argv[1]);

// Lines Scanned
int number_of_lines = 0;
string line;  // Count number of lines in file

// Device Boot Count
string bootup = "[(]log.c.[1][6]{2}[)]";
int matchBootupNum = 0;

string completion = "oejs.AbstractCo[n]{2}ector[:]Started";
int matchCompletionNum = 0;

// logFile open success?
if(!logFile.is_open()) {
  std::cout << "Failed to open file: " << std::endl;
  return 0;
} else {
  std::cout << "Sucess to open file: " << argv[1] << std::endl;
}


while(getline(logFile, line)) {
  ++number_of_lines;  // Gets number of lines in the file

// Device boot count: initiated
regex RBootup(bootup);
bool matchBootup = regex_search(line, RBootup);
if(matchBootup) {
  ++matchBootupNum;
}
// Device boot count... completed:
regex RCompletion(completion);
bool matchCompletion = regex_search(line, RCompletion);
if(matchCompletion) {
  ++matchCompletionNum;
}
}
logFile.close();

string deviceFileName = argv[1];
string rpt = ".rpt";
string outputFileX = deviceFileName + rpt;
ofstream outputFile(outputFileX);

outputFile << "Device Boot Report\n\n";
outputFile << "InTouch log file: " << argv[1] << std::endl;
outputFile << "Lines Scanned: " << number_of_lines << std::endl;
outputFile << "\n";
outputFile << "Device boot count: initiated = " << matchBootupNum
<< " completed: " << matchCompletionNum << std::endl;
outputFile << "\n\n";

// Second Half === Device boot===
number_of_lines = 0;

// === Device boot === INFO

// (log.c.166) server started
// string bootStart
string bootStart = "[(]log.c.[1][6]{2}[)] server started";
int matchBootStartNum = 0;

// oejs.AbstractConnector:Started SelectChannelConnector@0.0.0.0:9080
string completionBootup =
"oejs.AbstractConnector:Started SelectChannelConnector@0.0.0.0:9080";
int matchCompletionBootupNum = 0;

logFile.open(argv[1]);

if(!logFile.is_open()) {
  std::cout << "Failed to open file: " << std::endl;
  return 0;
} else {
  std::cout << "Sucess to open file second time: "
  << argv[1] << "\n" << std::endl;
}

int starting = 0;

string temp, hour1, minutes1, seconds1, hour2, minutes2, seconds2;
date d1, d2;

while(getline(logFile, line)) {
streampos oldpos = logFile.tellg();
++number_of_lines;  // Gets number of lines in the file
string date1, date2;

// Device boot count: initiated
regex RBootStart(bootStart);
bool matchBootStart = regex_search(line, RBootStart);
if(matchBootStart == true) {
  string time = line.substr(11, 8);
  hour1 = time.substr(0, 2);
  minutes1 = time.substr(3, 2);
  seconds1 = time.substr(6, 2);
  d1 = from_simple_string(line.substr(0, 19));
if(starting == 0) {
  outputFile << "=== Device boot ===" << std::endl;
  string date1 = line.substr(0, 10);
  string time = line.substr(11, 8);
  outputFile << number_of_lines << "(" << argv[1] << "): "
  << date1 << " " << time  << " Boot Start" << std::endl;
  starting = 1;
} else {
  outputFile << "**** Incomplete boot **** " << std::endl;
  outputFile << "\n\n";
  outputFile << "=== Device boot ===" << std::endl;
  string date1 = line.substr(0, 10);
  string time = line.substr(11, 8);
  outputFile << number_of_lines << "(" << argv[1] << "): "
  << date1 << " " << time  << " Boot Start" << std::endl;
}
  ++matchBootStartNum;
}
// Device boot
regex RCompletionBootup(completionBootup);
bool matchCompletionBootup = regex_search(line, RCompletionBootup);
if(matchCompletionBootup == true) {
  string time = line.substr(11, 8);
  hour2 = time.substr(0, 2);
  minutes2 = time.substr(3, 2);
  seconds2 = time.substr(6, 2);
  date d2 = from_simple_string(line.substr(0, 19));
if(starting == 1) {
  ++matchCompletionBootupNum;
  string date2 = line.substr(0, 10);
  string time = line.substr(11, 8);
  int convHour1 = std::stoi(hour1);
  int convHour2 = std::stoi(hour2);
  int convMinutes1 = std::stoi(minutes1);
  int convMinutes2 = std::stoi(minutes2);
  int convSeconds1 = std::stoi(seconds1);
  int convSeconds2 = std::stoi(seconds2);
  ptime t1(d1, time_duration(convHour1, convMinutes1, convSeconds1, 0));
  ptime t2(d2, time_duration(convHour2, convMinutes2, convSeconds2, 0));
  time_duration td = t2 - t1;
  outputFile << number_of_lines << "(" << argv[1] << "): " << date2 << " "
  << time << " Boot Completed" << std::endl;
  outputFile << "   Boot time: " << td.total_milliseconds()
  << "ms" << std::endl;
  outputFile << "\n\n";
  starting = 0;
} else {
  outputFile << "**** Incomplete boot **** " << std::endl;
  outputFile << "\n";
}
}
}
outputFile.close();
cout << "DONE\n";
return 0;
}
