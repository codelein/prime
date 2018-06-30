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
void sieve(int n,const char *program) {
  if(n>1) {
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
  } else {
    cerr << program << ": Error: input number needs to be an integer greater than 1" << endl;
    exit(1);
  }
}

/* usage of program */
void usage(const char *program,bool error) {
  if(error == false) {
  } else {
    cerr << "Usage: " << program << " [ -n | --number ]" << endl;
  }
}

int main(int argc,char* argv[]) {
  int n;
  
  int c;
  int optionIndex;
  bool syntax;

  syntax=false;

  /* long options */
  while(true) {
    static struct option longOptions[] = {
      {"help",1,0,HELP},
      {"number",1,0,NUMBER},
      {0,0,0,0}
    };
    
    c=getopt_long_only(argc,argv,"n:",longOptions,&optionIndex);
    
    if(c == -1) {
      break;
    } 

    /* short options */
    switch(c) {
    case 'n':
      n=stoi(optarg);
      break;
    case NUMBER:
      n=stoi(optarg);
      break;
    default:
      syntax=true;
      break;
    }
  }

  /* syntax error message */
  if(syntax == true || argc == 1) {
    usage(argv[0],true);
    cerr << endl << "Type '" << argv[0] << " -h' for a description of options." << endl;
    return 1;
  }
  
  sieve(n,argv[0]);

  return 0;
}
