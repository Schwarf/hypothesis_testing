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

	template<size_t... size>
	void read_data_row(const std::string && line){
		std::istringstream data_row(line);
		std::tuple<DataRows...> data;
		read_helper(data_row, data, std::make_index_sequence<sizeof...(DataRows)>());
		data_.push_back(data);
	}
	template<size_t... size>
	void read_helper(std::istringstream& iss, std::tuple<DataRows...> & data,  std::index_sequence<size...>)
	{
		(..., read_one_element(iss, std::get<size>(data)));
	}
	template <typename T>
	void read_one_element(std::istringstream& iss, T & data_element)
	{
		iss >> data_element;
		iss.ignore(1, ',');
	}

	std::vector<std::string> column_names_;
	std::vector<std::tuple<DataRows...>> data_;
	std::filesystem::path path_;
	bool has_header_;
};


#include "csv_data_reader.inl"

#endif //CSV_DATA_READER_H
