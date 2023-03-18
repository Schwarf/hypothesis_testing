#include <sstream>
#include <tuple>
#include <type_traits>
#include "read_data/csv_data_reader.h"

template <typename... Types>
class TupleReader
{
public:
	TupleReader(std::tuple<Types...> &tuple)
		: tuple_(tuple)
	{}
	void read(const std::string &str)
	{
		std::istringstream iss(str);
		readHelper(iss, tuple_, std::make_index_sequence<sizeof...(Types)>());
	}
	std::tuple<Types...> get_tuple() const
	{
		return tuple_;
	}

private:
	template <std::size_t... Is>
	void readHelper(std::istringstream& iss, std::tuple<Types...>& tuple, std::index_sequence<Is...>) {
		(..., readOne(iss, std::get<Is>(tuple)));
	}
	template <typename T>
	void readOne(std::istringstream& iss, T& value) {
		iss >> value;
		iss.ignore(1, ',');
	}
	std::tuple<Types...>& tuple_;
};


#include <iostream>
#include <string>

int main() {
	std::string path{"/media/linux_data/projects/cpp/hypothesis_testing/data/FuelsCosts.csv"};
	auto d = CSVDataReader<int, double, std::string>(path);
	d.read();
	auto data = d.get_data();

	std::tuple<int, double, std::string> myTuple;
	TupleReader<int, double, std::string> reader(myTuple);
	std::string input = "42,3.14,hello,";
	reader.read(input);
	auto t = reader.get_tuple();
	std::cout << std::get<0>(t) << " " << std::get<1>(t) << " " << std::get<2>(t) << std::endl;
	return 0;
}