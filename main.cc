////////////////////////////////////////////////////////////////////////////
/*                                                                        */
/* Prime, a package that calculates prime numbers using the Sieve of      */
/* Eratosthenes.                                                          */
/* Copyright (C) 2018 Philip Bowman.                                      */
/*                                                                        */
/* This program is free software: you can redistribute it and/or modify   */
/* it under the terms of the GNU General Public License as published by   */
/* the Free Software Foundation, either version 3 of the License, or      */
/* (at your option) any later version.                                    */
/*                                                                        */
/* This program is distributed in the hope that it will be useful,        */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of         */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          */
/* GNU General Public License for more details.                           */
/*                                                                        */
/* You should have received a copy of the GNU General Public License      */
/* along with this program.  If not, see <https://www.gnu.org/licenses/>. */
/*                                                                        */
////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>

#include <getopt.h>

using namespace std;

const char *PACKAGE="Prime";
const char *VERSION="v0.1";

enum Parameters {
  HELP=256,
  VERS,
  NUMBER
};

/* Sieve of Eratosthenes */
void sieve(int n) {
  bool *a=new bool[n+1];
  
  for(int i=2; i <= n; i++) {
    a[i]=true; // set all elements to true
  }
  
  for(int i=2; i <= sqrt(n); i++) {
    if(a[i] == true) {
      for(int j=i*i; j <= n; j += i) {
	a[j]=false; // set all composite numbers to false
      }
    }
  }
  
  for(int i=2; i <= n; i++) {
    if(a[i] == true) {
      cout << i << endl; // print primes to stdout
    }
  }
}

/* usage of program */
void usage(const char *program) {
  const char *usageopts=" [options] -n <number>";
  
  cerr << program <<": Usage: " << program << usageopts << endl;
}

/* help message */
void help(const char *program) {
  usage(program);
  cerr << endl;
  cerr << "Where options include:" << endl;
  cerr << "* '-h' | '-help' This help message." << endl;
  cerr << "* '-v' | '-version' Version information." << endl;
  cerr << "* '-n' | '-number' **Required** number for search limit." << endl;
  cerr << endl;
  exit(-1);
}

/* version message */
void version() {
  cerr << PACKAGE << " " << VERSION << endl;
  cerr << "Copyright (C) 2018 Philip Bowman." << endl;
  cerr << "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>" << endl;
  cerr << "This is free software: you are free to change and redistribute it." << endl;
  cerr << "There is NO WARRANTY, to the extent permitted by law." << endl;
  exit(-1);
}

int main(int argc,char* argv[]) {
  int n;
  
  int c;
  int optionIndex;
  bool syntax;

  syntax=false;

  while(true) {
    /* long options */
    static struct option longOptions[] = {
      {"help",0,0,HELP},
      {"version",0,0,VERS},
      {"number",1,0,NUMBER},
      {0,0,0,0}
    };
    
    c=getopt_long_only(argc,argv,"hvn:",longOptions,&optionIndex);
    
    if(c == -1) {
      break;
    }

    /* short options */
    switch(c) {
    case 'h':
    case HELP:
      help(argv[0]);
      break;
    case 'v':
    case VERS:
      version();
      break;
    case 'n':
    case NUMBER:
      n=atoi(optarg);
      
      if(n>1) {
	sieve(n);
      } else {
	
	cerr << argv[0] << ": error: input number needs to be an integer greater than 1." << endl;
	exit(-1);
      }
      
      break;
    default:
      syntax=true;
      break;
    }
  }

  /* syntax error message */
  if(syntax || argc == 1) {
    usage(argv[0]);
    cerr << endl << "Type '" << argv[0] << " -help' for a description of options." << endl;
    exit(-1);
  }

  return 0;
}
