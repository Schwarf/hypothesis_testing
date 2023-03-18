//
// Created by andreas on 18.03.23.
//

#include "csv_data_reader.h"

template <typename ...DataRows >
CSVDataReader<DataRows...>::CSVDataReader(std::string &path)
{
	if(!exists(std::filesystem::path(path)))
	{
		throw std::invalid_argument("Path '" + path +"' does not exist");
	}
}
template<typename... DataRows>
void CSVDataReader<DataRows...>::read()
{

}
