
int f(int n, int t, int f);

int main()
{
    return !( 523 == f(1, 523, 654) && 523 == f(-1, 523, 654) && 523 == f(6, 523, 654) );
}
