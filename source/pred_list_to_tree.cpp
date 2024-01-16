/// @file pred_list_to_tree.cpp
/// @brief Convert a predecessor list into a tree (a forest).
#include <ogxx/graph_search.hpp>

namespace ogxx
{

	auto pred_list_to_tree(Index_iterator_uptr preds, Graph_view& gv)
		-> Scalar_size
	{
		Scalar_size roots = 0;
		Scalar_index target = 0;
		for (Scalar_index source; preds->next(source); ++target)
		{
			if (source == target || source < 0)
			{
				++roots;
				continue;
			}

			gv.connect(source, target);
		}

		return roots;
	}

}
