#pragma once
#include <queue>
#include <vector>
#include <map>
#include <ostream>

namespace Utils
{
	// Wrapper class to enable comparisons independent of value
	template <class _CompareValueTyupe, class _ValueType>
	class CompareContainer
	{
	public:
		_CompareValueTyupe compareValue;
		_ValueType value;

		/**
		 * Constructor
		 *
		 * \param[in]  compareValue		This variable is used for comparison.
		 * \param[in]  value			Variable for which a comparison is needed.
		 */
		CompareContainer(_CompareValueTyupe compareValue, _ValueType value) : compareValue{ compareValue }, value{ value } {}

	
		// Compares two Compare Containers
		bool operator==(const CompareContainer& other) const { return compareValue == other.compareValue; }
		bool operator!=(const CompareContainer& other) const { return !this->operator==(other); }
		bool operator<(const CompareContainer& other) const { return compareValue < other.compareValue; }
		bool operator>(const CompareContainer& other) const { return !this->operator<(other) && !this->operator==(other); }
		bool operator<=(const CompareContainer& other) const { return !this->operator>(other); }
		bool operator>=(const CompareContainer& other) const { return !this->operator<(other); }
	};

	// Wrapper class to extend the functionality of std::priority_queue. Allows loading objects with independent weights into the priority queue and extends the priority queue with additional methods.
	// The smallest weight is always located at the top position (top()) of the priority queue.
	template <typename _Tr>
	class PriorityQueue : public std::priority_queue<CompareContainer<double, _Tr>, std::vector<CompareContainer<double, _Tr>>, std::greater<CompareContainer<double, _Tr>>>
	{
	public:
		void push(_Tr item, double weight)
		{
			std::priority_queue<CompareContainer<double, _Tr>, std::vector<CompareContainer<double, _Tr>>, std::greater<CompareContainer<double, _Tr>>>::push(CompareContainer<double, _Tr>(weight, item));
		}

		_Tr pop_top()
		{
			_Tr item = this->top().value;
			this->pop();
			return item;
		}

		bool remove(const _Tr& element)
		{
			for (auto it = this->c.begin(); it != this->c.end(); it++)
			{
				if ((*it).value == element) {
					this->c.erase(it);
					return true;
				}
			}
			return false;
		}

		bool contains(const _Tr& element)
		{
			for (auto it = this->c.begin(); it != this->c.end(); it++)
			{
				if ((*it).value == element) {
					return true;
				}
			}
			return false;
		}

		bool change(const _Tr& element, double weight)
		{
			if (!remove(element)) return false;
			this->push(element, weight);
			return true;
		}
	};
}