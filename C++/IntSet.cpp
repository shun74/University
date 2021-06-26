#include <iostream> 
using namespace std; 

static const int maxsize = 100; 

class Intset { // set of ints 
  int count; 
  int arr[maxsize]; 
  void add1(int x); // internal use only 
public: 
  Intset(); 
  int size() const; 
  bool is_in(const int i) const; 
  Intset operator+(const Intset& s) const; 
  Intset operator-(const Intset& s) const; 
  Intset operator*(const Intset& s) const; 
  class Overflow { }; 
  friend ostream& operator<<(ostream& o, Intset& s); 
  friend istream& operator>>(istream& i, Intset& s); 
};

Intset::Intset() { count = 0; } 
void Intset::add1(int x) { 
  if(count >= maxsize) throw Overflow(); 
  arr[count++] = x; 
} 
int Intset::size() const { return count; } 
bool Intset::is_in(const int i) const { 
  for(int k = 0; k < count; ++k) 
    if(arr[k] == i) return true; 
  return false; 
} 
Intset Intset::operator+(const Intset& s) const { 
  Intset r = s; 
  for(int k = 0; k < count; ++k) 
    if(!s.is_in(arr[k])) r.add1(arr[k]); 
  return r; 
} 
Intset Intset::operator-(const Intset& s) const { 
  Intset r; 
  for(int k = 0; k < count; ++k) 
    if(!s.is_in(arr[k])) r.add1(arr[k]); 
  return r; 
} 
Intset Intset::operator*(const Intset &s) const { 
  Intset r; 
  for(int k = 0; k < count; ++k) 
    if(s.is_in(arr[k])) r.add1(arr[k]); 
  return r; 
} 
ostream& operator<<(ostream& o, Intset& r) { 
  o << "{ "; 
  for(int k = 0; k < r.count; ++k) o << r.arr[k] << ' ';
  o << '}'; 
  return o; 
} 
istream& operator>>(istream& i, Intset& r) { 
  r.count = 0; 
  while(i.peek() != '\n') { 
    int x; i >> x; r.add1(x); 
  } 
  i.get(); return i; 
}


int main(void) { 
  Intset r, x; 
  while(true) { 
    char c; cout << "? "; cin >> c; 
    switch(c) { 
    case 'q': return 0; 
    case '=': cin>>x; r = x; break; 
    case '+': cin>>x; r = r + x; break; 
    case '-': cin>>x; r = r - x; break; 
    case '*': cin>>x; r = r * x; break; 
    default: continue; 
    } 
    cout << r << '\n'; 
  } 
}