
int f(int n, int begin);

int main()
{
    return !( 4 == f(2, 2) && 63 == f(7, 9) && 5 == f(5, 1) );
}
