#include <sstream>
#include <iostream>
#include "read_data/csv_data_reader.h"

template<typename... Types>
class TupleSummer {
public:
	TupleSummer(const std::vector<std::tuple<Types...>>& vec, const std::vector<size_t>& indices) :
		m_vec(vec),
		m_indices(indices)
	{}

	// Function that sums the specified tuple elements of all tuples in the vector
	std::tuple<Types...> get_sum() const {
		std::tuple<Types...> result{};
		sum_helper<0>(result);
		return result;
	}

private:
	// Recursive helper function to get_sum tuple elements
	template<size_t Index>
	void sum_helper(std::tuple<Types...>& result) const {
		if constexpr (Index < sizeof...(Types)) {
			if (std::find(m_indices.begin(), m_indices.end(), Index) != m_indices.end()) {
				// Sum the current element
				std::get<Index>(result) = sum_elements<Index>();
			}
			sum_helper<Index + 1>(result);
		}
	}

	// Helper function to get_sum the elements of the tuple with the specified index
	template<size_t Index>
	auto sum_elements() const {
		using TupleType = std::tuple_element_t<Index, std::tuple<Types...>>;
		TupleType sum = {};
		for (const auto& t : m_vec) {
			sum += std::get<Index>(t);
		}
		return sum;
	}

	std::vector<std::tuple<Types...>> m_vec;
	std::vector<size_t> m_indices;
};

template <typename... Types>
std::tuple<std::vector<Types>...> transform(const std::vector<std::tuple<Types...>>& v) {
	std::tuple<std::vector<Types>...> result;
	std::apply([&](auto&... vecs) {
		((vecs.reserve(v.size()), void()), ...);
	}, result);
	for (const auto& t : v) {
		std::apply([&](auto&... vecs) {
			(vecs.push_back(std::get<decltype(vecs)::value_type::value>(t)), ...);
		}, result);
	}
	return result;
}


int main()
{

	std::string path{"/media/linux_data/projects/cpp/hypothesis_testing/data/billig.csv"};
	constexpr size_t count_index = 0;
	constexpr size_t fuel_index = 1;
	auto d = CSVDataReader<int, int, int, double>(path);
	d.read();
	auto data = d.get_data();
	std::vector<std::tuple<int, double, std::string>> input {
		{1, 3.14, "foo"},
		{2, 2.71, "bar"},
		{3, 1.23, "baz"}
	};
	auto result = transform(input);
	std::vector<int>& int_vec = std::get<std::vector<int>>(result);
	std::vector<double>& double_vec = std::get<std::vector<double>>(result);
	std::vector<std::string>& string_vec = std::get<std::vector<std::string>>(result);
	auto headers = d.get_header();
	std::vector<size_t> index{1};
	auto summer = TupleSummer(data, index);
	auto sum = summer.get_sum();
	std::cout << std::get<3>(sum) << std::endl;
}