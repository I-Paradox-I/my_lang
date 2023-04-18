// test if-else
int ifElse() {
  int a;
  a = 5;
  if (!a) {
    a = 25;
  } else {
    a = a * 2;
  }
  return (a+2);
}


int main() {
  return (ifElse());
}
