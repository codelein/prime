#include <iostream>
#include <string>
#include <cmath>

#include <getopt.h>

using namespace std;

enum Parameters {
  HELP=256,
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
void usage(const char *program,bool error) {
  const char *usageopts=" [-h] [-help] [-n NUMBER] [-number NUMBER]";

  if(!error) {
    cout << "Usage: " << program << usageopts << endl;
  } else {
    cerr << program <<": Usage: " << program << usageopts << endl;
  }
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
      {"number",1,0,NUMBER},
      {0,0,0,0}
    };
    
    c=getopt_long_only(argc,argv,"n:",longOptions,&optionIndex);
    
    if(c == -1) {
      break;
    } 

    /* short options */
    switch(c) {
    case 'h':
    case HELP:
      break;
    case 'n':
    case NUMBER:
      n=stoi(optarg);
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
    usage(argv[0],true);
    cerr << endl << "Type '" << argv[0] << " -help' for a description of options." << endl;
    exit(-1);
  }

  return 0;
}
