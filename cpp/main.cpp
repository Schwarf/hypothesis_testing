#include <sstream>
#include <iostream>
#include "read_data/csv_data_reader.h"
#include "statistics/tuple_summer.h"



int main()
{

	std::string path{"/media/linux_data/projects/cpp/hypothesis_testing/data/billig.csv"};
	constexpr size_t count_index = 0;
	constexpr size_t fuel_index = 1;
	auto d = CSVDataReader<int, int, int, double>(path);
	d.read();
	auto data = d.get_data();
	auto headers = d.get_header();
	std::vector<size_t> indices_to_sum{count_index, fuel_index};
	auto summer = TupleSummer(data, indices_to_sum);
	auto sum = summer.get_sum();
	std::cout << std::get<3>(sum) << std::endl;
}