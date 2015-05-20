#define VAR_INTEGER 0
#define VAR_FRACTION 1
#define VAR_STRING 2
#define VAR_BOOLE 3
#define VAR_NULL 4
#define VAR_UNDEFINED 5
#define VAR_NAN 6
#define VAR_NINF 7
#define VAR_PINF 8

class var {
private:
	/*
	var a = true;
	var a = 5;
	var a = 5.5;
	var a = "5.5";
	var a = [5,5];
	var a = {a: 5, b: "5"};
	var a = null;
	var a = undefined;
	*/
	void *data;
	int type;
public:
	var();
	var(var& rhs);
	//var(const bool& rhs);
	var(const long long& rhs);
	//var(const long double& rhs);
	var(const std::string& rhs);
	var(const std::list<bool>& rhs);
	var(const std::list<long long>& rhs);
	var(const std::list<long double>& rhs);
	var(const std::list<std::string>& rhs);

	~var();

	const void *__getData() const { return data; }
	int __getType() const { return type; }
	void __setType(int type) { this->type = type; }
	void deleteData();

	var& operator=(const long long&);
	var operator+(const long long&);
	var operator-(const long long&);
	var operator*(const long long&);
	var operator/(const long long&);
	var operator%(const long long&);
	var operator^(const long long&);
	var operator&(const long long&);
	var operator|(const long long&);

	friend std::ostream& operator<<(std::ostream&, var&);
};

var::var() : type(VAR_UNDEFINED) {}

var::var(var& rhs) : type(VAR_UNDEFINED)
{
	deleteData();
	type = rhs.__getType();
	switch (type)
	{
	case VAR_INTEGER:
		data = new long long(*(long long *)(rhs.__getData()));
		break;
	default:
		break;
	}
}

var::var(const long long& rhs)
{
	deleteData();
	type = VAR_INTEGER;
	data = new long long(rhs);
}

var::~var()
{
	deleteData();
}

void var::deleteData()
{
	if (type != VAR_UNDEFINED &&
		type != VAR_NULL &&
		type != VAR_PINF &&
		type != VAR_NINF
		){
		type = VAR_UNDEFINED;
		delete data;
	}
}

var& var::operator=(const long long& rhs)
{
	deleteData();
	type = VAR_INTEGER;
	data = new long long(rhs);
	return *this;
}

var var::operator+(const long long& rhs)
{
	var out;
	switch (type)
	{
	case VAR_INTEGER:
		out = (*(long long *)data) + rhs;
		break;
	default:
		break;
	}
	return out;
}

var var::operator-(const long long& rhs)
{
	var out;
	switch (type)
	{
	case VAR_INTEGER:
		out = (*(long long *)data) - rhs;
		break;
	default:
		break;
	}
	return out;
}

var var::operator*(const long long& rhs)
{
	var out;
	switch (type)
	{
	case VAR_INTEGER:
		out = (*(long long *)data) * rhs;
		break;
	default:
		break;
	}
	return out;
}

var var::operator/(const long long& rhs)
{
	var out;
	switch (type)
	{
	case VAR_INTEGER:
		if (rhs == 0)
		{
			deleteData();
			out.__setType((*(long long *)data) < 0 ? VAR_NINF : VAR_PINF);
		}
		else
		{
			out = (*(long long *)data) / rhs;
		}
		break;
	default:
		break;
	}
	return out;
}

var var::operator%(const long long& rhs)
{
	var out;
	switch (type)
	{
	case VAR_INTEGER:
		if (rhs == 0)
		{
			deleteData();
			out.__setType(VAR_NAN);
		}
		else
		{
			out = (*(long long *)data) % rhs;
		}
		break;
	default:
		break;
	}
	return out;
}

var var::operator^(const long long& rhs)
{
	var out;
	switch (type)
	{
	case VAR_INTEGER:
		out = (*(long long *)data) ^ rhs;
		break;
	default:
		break;
	}
	return out;
}

var var::operator&(const long long& rhs)
{
	var out;
	switch (type)
	{
	case VAR_INTEGER:
		out = (*(long long *)data) & rhs;
		break;
	default:
		break;
	}
	return out;
}

var var::operator|(const long long& rhs)
{
	var out;
	switch (type)
	{
	case VAR_INTEGER:
		out = (*(long long *)data) | rhs;
		break;
	default:
		break;
	}
	return out;
}

std::ostream& operator<<(std::ostream& os, var& rhs)
{
	switch (rhs.__getType())
	{
	case VAR_INTEGER:
		os << *(long long *)rhs.__getData();
		break;
	case VAR_NAN:
		os << "Nan";
		break;
	case VAR_UNDEFINED:
		os << "undefined";
		break;
	case VAR_NULL:
		os << "null";
		break;
	case VAR_PINF:
		os << "Infinity";
		break;
	case VAR_NINF:
		os << "-Infinity";
		break;
	default:
		break;
	}
	return os;
}