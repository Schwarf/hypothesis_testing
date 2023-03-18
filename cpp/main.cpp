#include <iostream>
#include "read_data/csv_data_reader.h"

int main()
{
	MyTemplate<int> myObj(42);
	myObj.printVal();
	std::string path{"/media/linux_data/projects/cpp/hypothesis_testing/data/body_fat.csv"};
	auto reader = CSVDataReader<int, double, std::string>(path);

	return 0;

}
