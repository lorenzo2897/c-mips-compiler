int f(int n, int begin)
{
	int acc = 0;
	int i = n;
	while(i) {
		acc = acc + begin;
		i = i - 1;
	}
    return acc;
}
