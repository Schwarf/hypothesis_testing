//
// Created by andreas on 18.03.23.
//

#include "csv_data_reader.h"

template<typename ...DataRows>
CSVDataReader<DataRows...>::CSVDataReader(std::string &path, bool has_header)
	: has_header_(has_header),
	path_(path)
{
	if (!std::filesystem::is_regular_file(path_)) {
		throw std::invalid_argument("Path '" + path + "' does not exist");
	}

}
template<typename... DataRows>
void CSVDataReader<DataRows...>::read()
{
	std::ifstream file(path_);
	std::string line;
	if(file.is_open())
	{
		if(has_header_) {
			std::getline(file, line);
			read_header(std::move(line));
		}

		while(std::getline(file, line))
		{

		}

		return;
	}
}

template<typename... DataRows>
std::vector<std::string> CSVDataReader<DataRows...>::get_header() const
{
	return column_names_;
}

template<typename... DataRows>
std::vector<std::tuple<DataRows...>> CSVDataReader<DataRows...>::get_data() const
{
	return data_;
}
