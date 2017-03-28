
int glob_myc;
int glob_gcc;

int f(int n);

int main()
{
	glob_gcc = 867;
	int result = f(432);

    return !( result == 867 && glob_myc == 432 );
}
