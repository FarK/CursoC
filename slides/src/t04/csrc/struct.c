struct person {
	char name[256];
	char surname[256];
	unsigned char age;
	unsigned int phone;
};

int main()
{
	struct person p = {"Man", "Bat", 35, 69813244};

	printf("%s%s\n", p.surname, p.name);

	return 0;
}
