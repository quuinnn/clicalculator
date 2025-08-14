/*
BSD 3-Clause License

Copyright (c) 2025, quinn

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <cstdlib>
#include <iostream>

// Function declarations
void help(const std::string& PROGRAM_NAME); // & means pass by referance not by value
double math(char op, char*argv[], int argc);
void requiredTwoArgs(const std::string& PROGRAM_NAME);

bool isValidNumber(const char* str) {
    char* end; // Declare a pointer to track where the conversion stops in the string
    std::strtod(str, &end); // Converts string to double
    return *end == '\0'; // Check conversion success
}

int main(int argc, char *argv[]){ // char *argv[] == pointers to strings, argc is the count of argv
  std::cout << "Welcome to my based sigma program.\n";

  const std::string PROGRAM_NAME = argv[0]; // Taking advantage of arg[0] being the binary name make it more modular

  // To avoid SIGABRT, checks argc before running the program

  if(argc < 2){
    std::cout << "Please enter at least one arguement\n";
    help(PROGRAM_NAME);
    return -1; // Error status
  }
  
  std::string arg1(argv[1]); // Converts the first arg to standard string, makes it easier to work with in C++
  
  if(arg1 == "--help"){
    help(PROGRAM_NAME);
  }

  else if(arg1 == "-m" || arg1 == "--multiply"){
    if(argc < 4){
      requiredTwoArgs(PROGRAM_NAME);
      return -1; // Error status
    }

    char op = '*'; // Operator is a reserved keyword in C++

    double result = math(op, argv, argc);
    std::cout << "Your result is: " << result << '\n';
  }

  else if(arg1 == "-a" || arg1 == "--add"){
    if(argc < 4){
      requiredTwoArgs(PROGRAM_NAME);
      return -1; // Error status
    }

    char op = '+'; // Operator is a reserved keyword in C++

    double result = math(op, argv, argc);
    std::cout << "Your result is: " << result << '\n';
  }

  else if(arg1 == "-s" || arg1 == "--subtract"){
    if(argc < 4){
      requiredTwoArgs(PROGRAM_NAME);
      return -1; // Error status
    }

    char op = '-'; // Operator is a reserved keyword in C++

    double result = math(op, argv, argc);
    std::cout << "Your result is: " << result << '\n';
  }

  else if(arg1 == "-d" || arg1 == "--divide"){
    if(argc < 4){
      requiredTwoArgs(PROGRAM_NAME);
      return -1; // Error status
    }

    char op = '/'; // Operator is a reserved keyword in C++

    double result = math(op, argv, argc);
    std::cout << "Your result is: " << result << '\n';
  }

  else {
    help(PROGRAM_NAME);
  }

  return 0;
}

// The main function doing all the work
double math(char op, char*argv[], int argc){
  if(!isValidNumber(argv[2])){
    std::cerr << "Invalid input: " << argv[2] << " is not a number, silly!\n";
    exit(EXIT_FAILURE); // Force quit program
  }

  double result = std::atof(argv[2]); // Due to the way I changed the for loop, result has to indiscriminately be 
                                      // argv[2] 
  std::cout << "Your inputs: " << argv[2]; // Prints the initial input

  for(int i = 3; i < argc; i++){        // The first 3 arguements are already being used
    double number = std::atof(argv[i]); // Ascii to floating point

    // Checks if it's not the last input before executing
    if(i < argc){
      std::cout << ' ' << op << ' '; // Prints the operator inbetween the cout stuff on top and bottom
    }

    std::cout << argv[i]; // Prints the remaining inputs

    switch(op){
      case '*':
        result *= number;
        break;
      case '+':
        result += number;
        break;
      case '-':
        result -= number;
        break;
      case '/':
        if(number == 0 or result == 0){
          std::cerr << "\nERROR: Cannot divide number by 0, program exitting...\n";
          exit(EXIT_FAILURE); // Force quit program
        }
        result /= number;
        break;
    }
  }
  std::cout << '\n'; // Prints a newline because cout argv[i] doesn't print one at the end
  return result;
}

void requiredTwoArgs(const std::string& PROGRAM_NAME){ 
  std::cout << PROGRAM_NAME << ": excepted at least 2 arguements\n";
  std::cout << "Try '" << PROGRAM_NAME << " --help' for more information\n";
}

void help(const std::string& PROGRAM_NAME){
  std::cout << "Usage: " << PROGRAM_NAME << " [OPTION] num1 num2 num ...\n";
  std::cout << "      -m, --multiply  multiply 2 or more numbers together\n";
  std::cout << "      -a, --add  add 2 or more numbers together\n";
  std::cout << "      -s, --subtract  subtract 2 or more numbers against eachother\n";
  std::cout << "      -d, --divide  divide 2 or more numbers against eachother\n";
  std::cout << "      --help  print this screen\n";
} 
