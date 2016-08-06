// Sequential Dot-Product
// only as preview, no Makefile

int main(int argc, char** argv)
{
	double sum;
	double a [256], b [256];
	int n;
	n = 256;
	for (i = 0; i < n; i++) {
		a [i] = i * 0.5;
		b [i] = i * 2.0;
	}
	sum = 0;
	for (i = 1; i < n; i++ ) {
		sum = sum + a[i]*b[i];
	}
	printf ("sum = %f", sum);
	return 0;
}
