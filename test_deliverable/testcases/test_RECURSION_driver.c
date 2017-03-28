
int f(int n);

int main()
{
    return !( f(2) == 2 && f(3) == 3 && f(5) == 8 && f(10) == 89 );
}
