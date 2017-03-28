
int f(int n, int t, int f, int end);

int main()
{
    return !( 523 == f(1, 523, 654, 23) && 523 == f(-1, 523, 654, 23) && 523 == f(6, 523, 654, 23) );
}
