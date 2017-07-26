#include <iostream> 
#include <fstream>
#include "analysis.h"
#include <string.h>

//
//	class Analysis
//

using namespace std;

ifstream inputFile;			// input file stream
ofstream outputFile;			// output file stream

//
//	class: Analysis  
//	method:openInputFile  
//      
//	description: open input file
//	return: T=success F=failure
//
bool Analysis::openInputFile(const char* input) {
  inputFile.open(input);
  return inputFile.is_open();
}

//
//	class: Analysis  
//	method:openOutputFile  
//      
//	description: open output file
//	return: T=success F=failure
//
bool Analysis::openOutputFile(const char* output) {
  outputFile.open(output);
  return outputFile.is_open();
}

//
//	class: Analysis  
//	method:closeFiles  
//      
//	description: close files
//	return: none
//
void Analysis::closeFiles() {
  inputFile.close();
  outputFile.close();
}

//
//	class: Analysis  
//	method:write   
//      
//	description: write data item
//	return: none
//
void Analysis::write(const long data) {
   outputFile << data << "\n";
}

//
//	class: Analysis  
//	method:overflow(x, y)   
//      
//	description: test for overflow of x+y
//	return: T=overflow F=no overflow
//
bool Analysis::overflow(const long x, const long y) {
  return (((x > 0) && (y > LLONG_MAX - x)) ||
          ((x < 0) && (y < LLONG_MIN - x)));
}


//
//	class: Analysis  
//	method: analyse(input,output)  
//      
//	description: read input file containing whole numbers
//	compute sum and average of numbers read  
//	write statistics to output file
//	return: 0=success negative=failure
//

int Analysis::analyse(const char* input, const char* output) {

int resultCode; 	// result code : 0 for success -ve for error

// open input file
resultCode = openInputFile(input) ? SUCCESS: INPUTERROR;

// open output file
if (resultCode == SUCCESS) {
  resultCode = openOutputFile(output) ? SUCCESS: OUTPUTERROR;
}

// read input file
// check for bad data or overflow
// compute sum and linecount

int count=0;				// initialise linecount
long num, sum=0;			// initialise number and sum 
string datastring;			// scan buffer

while (getline(inputFile, datastring) && (resultCode == SUCCESS)) {
  int scanres = (sscanf(datastring.c_str(), "%ld", &num));

  // check for scan failure
  // disallow blank or corrupt lines 
   if (scanres != 1) 
    resultCode = INVALIDINPUT;
  else
  // check for overflow
    if (overflow(num, sum)) 
      resultCode = RANGEERROR;  

  // accumulate total values and linecount	
  sum += num;
  count++;
}

// compute average
// output linecount sum and ave 
// 

if (resultCode == SUCCESS) {

   // check for empty file
   if (count == 0)
     resultCode = EMPTYFILE;
   else {
   // output count sum and average
   write(count);
   write(sum);
   write(float(sum)/count);
   }
}

// close files
closeFiles();

return resultCode;

}



