//
// Created by andreas on 18.03.23.
//

#ifndef TUPLE_SUMMER_H
#define TUPLE_SUMMER_H
#include <vector>
#include <tuple>

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

#endif //TUPLE_SUMMER_H
