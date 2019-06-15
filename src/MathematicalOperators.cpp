#ifdef _WIN32
__declspec(noinline) int db_plus(int a, int b){
  return a + b;
}
__declspec(noinline) int db_minus(int a, int b){
  return a - b;
}
__declspec(noinline) int db_times(int a, int b){
  return a * b;
}
__declspec(noinline) int db_divided(int a, int b){
  return a / b;
}
__declspec(noinline) double db_minus(double a, double b){
  return a - b;
}
__declspec(noinline) double db_times(double a, double b){
  return a * b;
}
__declspec(noinline) double db_divided(double a, double b){
  return a / b;
}
__declspec(noinline) double db_times(int a, double b){
  return a * b;
}
__declspec(noinline) double db_times(double a, int b){
  return a * b;
}
#elif defined(__unix__) || defined(__APPLE__)

int __attribute__ ((noinline)) db_plus(int a, int b){
  return a + b;
}
int __attribute__ ((noinline)) db_minus(int a, int b){
  return a - b;
}
int __attribute__ ((noinline)) db_times(int a, int b){
  return a * b;
}
int __attribute__ ((noinline)) db_divided(int a, int b){
  return a / b;
}
double __attribute__ ((noinline)) db_minus(double a, double b){
  return a - b;
}
double __attribute__ ((noinline)) db_times(double a, double b){
  return a * b;
}
double __attribute__ ((noinline)) db_divided(double a, double b){
  return a / b;
}
double __attribute__ ((noinline)) db_times(int a, double b){
  return a * b;
}
double __attribute__ ((noinline)) db_times(double a, int b){
  return a * b;
}
#endif
