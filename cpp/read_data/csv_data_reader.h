//
// Created by andreas on 18.03.23.
//

#ifndef CSV_DATA_READER_H
#define CSV_DATA_READER_H
#include <string>
#include <filesystem>
#include <tuple>
#include <vector>
#include <fstream>
#include <sstream>

template <typename ...DataRows >
class CSVDataReader
{
public:
	explicit CSVDataReader(std::string & path, bool head_header =true);
	void read();
	std::vector<std::tuple<DataRows...>> get_data() const;
	std::vector<std::string> get_header() const;

private:
	std::vector<std::string> column_names_;
	std::vector<std::tuple<DataRows...>> data_;
	std::filesystem::path path_;
	bool has_header_;
};

#include "csv_data_reader.inl"

#endif //CSV_DATA_READER_H
