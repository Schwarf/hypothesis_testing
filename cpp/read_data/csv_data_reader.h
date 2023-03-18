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
	void read_header(const std::string && line);
	void read_data_row(const std::string && line);
	std::vector<std::string> column_names_;
	std::vector<std::tuple<DataRows...>> data_;
	std::filesystem::path path_;
	bool has_header_;
};

template<typename... DataRows>
void CSVDataReader<DataRows...>::read_header(const std::string && line)
{
	std::istringstream header(line);
	std::string column_name;
	while (getline(header, column_name, ',')) {
		column_names_.push_back(column_name);
	}

}


template<typename... DataRows>
void CSVDataReader<DataRows...>::read_data_row(const std::string && line)
{
	std::istringstream header(line);
	std::string column_name;
	while (getline(header, column_name, ',')) {
		column_names_.push_back(column_name);
	}

}

#include "csv_data_reader.inl"

#endif //CSV_DATA_READER_H
