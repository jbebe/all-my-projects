#include <iostream>
#include <type_traits>

template <typename T>
struct is_char_origin {
	static constexpr bool value = (
		   std::is_same<typename std::remove_cv<T>::type, char>::value
		|| std::is_same<typename std::remove_cv<T>::type, signed char>::value
		|| std::is_same<typename std::remove_cv<T>::type, unsigned char>::value
		|| std::is_same<typename std::remove_cv<T>::type, wchar_t>::value
		|| std::is_same<typename std::remove_cv<T>::type, char16_t>::value
		|| std::is_same<typename std::remove_cv<T>::type, char32_t>::value
	);
};

template <typename T>
typename std::enable_if<
	(std::is_integral<T>::value
		&& !is_char_origin<T>::value)
	|| std::is_floating_point<T>::value, void>::type
print(T num){
	std::cout << num << std::endl;
}

template <typename T>
typename std::enable_if<is_char_origin<T>::value, void>::type
print(T num){
	std::cout << "'" << num << "'" << std::endl;
}

template <typename T>
typename std::enable_if<
	(std::is_pointer<T>::value
		&& is_char_origin<typename std::remove_pointer<T>::type>::value)
	|| std::is_same<T, std::string>::value, void>::type
print(T num){
	std::cout << "\"" << num << "\"" << std::endl;
}

int main() {
	// egész számokra
	print(5);
	print(5l);
	print(5u);
	print(5lu);
	print(5ll);
	print(5llu);
	print(5.5);
	print(5.5f);

	// karakterekre
	print('5');
	print(static_cast<wchar_t>(5));

	// sztringekre
	const char a[] = "Hello";
	const char *ptr = a;
	print(static_cast<const char *>(ptr));
	print(a);
	print(std::string{"Hello"});
	return 0;
}
