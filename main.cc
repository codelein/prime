#include <iostream>
#include <cmath>

using namespace std;

void sieve(int n) {
  if(n > 1) {
    bool a[n+1];

    for(int i=2; i <= n; i++) {
      a[i]=true;
    }
    
    for(int i=2; i <= sqrt(n); i++) {
      if(a[i] == true) {
	for(int j=i*i; j <= n; j += i) {
	  a[j]=false;
	}
      }
    }
    
    for(int i=2; i <= n; i++) {
      if(a[i] == true) {
	cout << i << endl;
      }
    }

  } else {
    cerr << "Error: \"n\" needs to be an integer greater than 1.";
    exit(1);
  }
}

int main() {
  int n;
  
  n=100; // Try changing n.
  
  sieve(n);

  return 0;
}
