//
// Created by andreas on 18.03.23.
//

#ifndef CSV_DATA_READER_H
#define CSV_DATA_READER_H
#include <string>
#include <filesystem>
#include <tuple>
#include <vector>
template <typename ...DataRows >
class CSVDataReader
{
public:
	explicit CSVDataReader(std::string & path);
	void read();
private:
	std::vector<std::string> column_names_;
	std::vector<std::tuple<DataRows...>> data_;
};


#endif //CSV_DATA_READER_H
