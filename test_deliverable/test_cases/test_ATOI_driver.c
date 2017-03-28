
int f(const char* str);

int main()
{
    return !( 10==f("10") && -5==f("-5") );
}
