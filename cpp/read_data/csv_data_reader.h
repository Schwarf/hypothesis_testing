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
#include <concepts>

template<typename ...ColumnTypes>
class CSVDataReader
{

public:
	explicit CSVDataReader(const std::string &path, bool has_header = true)
		: has_header_(has_header),
		  path_(path)
	{
		if (!std::filesystem::is_regular_file(path_)) {
			throw std::invalid_argument("Path '" + path + "' does not exist");
		}

	}
	void read()
	{
		std::ifstream file(path_);
		std::string line;
		if (file.is_open()) {
			if (has_header_) {
				std::getline(file, line);
				read_header(std::move(line));
			}
			while (std::getline(file, line)) {
				read_data_row<sizeof...(ColumnTypes)>(std::move(line));
			}

			return;
		}
	}

	std::vector<std::string> get_header() const
	{
		return column_names_;
	}

	std::vector<std::tuple<ColumnTypes...>> get_data() const
	{
		return data_;
	}


private:
	void read_header(const std::string &&line)
	{
		std::istringstream header(line);
		std::string column_name;
		while (std::getline(header, column_name, ',')) {
			column_names_.push_back(column_name);
		}
	}

	template<size_t... size>
	void read_data_row(const std::string &&line)
	{
		std::istringstream data_row(line);
		std::tuple<ColumnTypes...> data;
		read_helper(data_row, data, std::make_index_sequence<sizeof...(ColumnTypes)>());
		data_.push_back(data);
	}
	template<size_t... size>
	void read_helper(std::istringstream &iss, std::tuple<ColumnTypes...> &data, std::index_sequence<size...>)
	{
		(..., read_one_element(iss, std::get<size>(data)));
	}
	template<typename T>
	void read_one_element(std::istringstream &iss, T &data_element)
	{
		iss >> data_element;
		iss.ignore(1, ',');
	}

	std::vector<std::string> column_names_;
	std::vector<std::tuple<ColumnTypes...>> data_;
	std::filesystem::path path_;
	bool has_header_;

};

#endif //CSV_DATA_READER_H
