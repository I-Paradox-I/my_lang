int a;
double test(int x, double y){return x+y;}
int main(){
    int b ;
	a=10;
    b = 20;
    test(test(10,20),20);
	return 0;
}
