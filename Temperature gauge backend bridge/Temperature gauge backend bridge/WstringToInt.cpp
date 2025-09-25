int atoi(const wchar_t* _String)
{
	int result = 0;
	while (*_String)
	{
		result = 10 * result + *_String++ - '0';
	}
	return result;
}