/// @file index_set_vector.cpp
/// @brief set interface (vector<Scalar_index>)
/// @author KaigorodovAB

include<source/stl_iterator.hpp>
include<vector>

namespace ogxx{
	class Index_set_vector : public ogxx::Index_set, public ogxx::Indexed_iterable<Scalar_index> {
	private:
		vector<Scalar_index> set;
	public:
		void push(Scalar_index element) {
			set.push_back(element);
		}
	};
}