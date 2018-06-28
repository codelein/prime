#include <iostream>
#include <cmath>

using namespace std;

/* Sieve of Eratosthenes */
void sieve(int n) {
  if(n > 1) {
    bool *a=new bool(a+1);

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
    cerr << "Error: 'n' needs to be an integer greater than 1.";
    exit(1);
  }
}

int main() {
  int n;

  cout << "Number: ";
  cin >> n;  // user input
  
  sieve(n);

  return 0;
}
