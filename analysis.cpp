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
//
void Analysis::write(const long data) {
   outputFile << data << "\n";
}

//
//	class: Analysis  
//	method: analyse(input,output)  
//      
//	description: read input file containing whole numbers
//	compute sum and average of numbers read  
//	write statistics to output file
//

int Analysis::analyse(const char* input, const char* output) {

enum RESCODE resultCode = SUCCESS; 	// default result code 

// open input file
resultCode = openInputFile(input) ? SUCCESS: INPUTERROR;

// open output file
if (resultCode == SUCCESS) {
  resultCode = openOutputFile(output) ? SUCCESS: OUTPUTERROR;
}

// read input file

int count=0;				// initialise linecount
long num, sum=0;			// initialise number and sum 
string datastring;			// scan buffer

while (getline(inputFile, datastring) && (resultCode == SUCCESS)) {
  int scanres = (sscanf(datastring.c_str(), "%ld", &num));

  // check for scan failure
   if (scanres < 1) 
    resultCode = INVALIDINPUT;

  // check for overflow
  if (overflow(num, sum)) 
    resultCode = RANGEERROR;  

  // accumulate totals	
  sum += num;
  count++;
}

if (resultCode == SUCCESS) {
   // compute average
   float avg = float(sum)/count;
 
   // output count sum and average
   write(count);
   write(sum);
   write(avg);

   // check for empty file
   if (count == 0)
     resultCode = EMPTYFILE;
}

// close files
closeFiles();

return resultCode;
}



