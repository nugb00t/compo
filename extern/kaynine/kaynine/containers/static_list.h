#pragma once

#include <assert.h>

#include "../debug/macros.h"

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TValue, unsigned TSize>
class StaticList {
public:
	typedef TValue VALUE_TYPE;
	static const unsigned SIZE = TSize;

	//-----------------------------------------------------------------------------------------------------------------

protected:

#pragma pack(push, 4)
	struct Item {
		Item* prev;
		Item* next;

		TValue value;
	};
#pragma pack(pop)

	//-----------------------------------------------------------------------------------------------------------------

public:

	class Range {
	public:
		inline Range(StaticList& list) : list_(list), current_() {}

		//inline const bool finished() { return current_ >= (int)list_.size_; }
		//inline void next();

		inline		 TValue& get()		 { return current_->value; }
		inline const TValue& get() const { return current_->value; }

		inline const unsigned index() const { return current_ - &list_.items_[0]; }

	private:
		StaticList& list_;
		Item* current_;
	};

	//-----------------------------------------------------------------------------------------------------------------

public:
	StaticList();

	inline TValue* add(const TValue value);
	inline void remove(const TValue* item);
	inline void reset();

	inline		 TValue& operator [](const unsigned i)		 { assert(valid(i)); return items_[i]; }
	inline const TValue& operator [](const unsigned i) const { assert(valid(i)); return items_[i]; }

private:
    Item items_[SIZE];

	Item* head_;
	Item* tail_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TValue, unsigned TSize>
StaticList<TValue, TSize>::StaticList() : head_(NULL), free_(&items_[0]) {
	Item* item = free_;
	item->prev = NULL;
	item->next = item + 1;

	for (; item < &items_[TSize - 1]; ++item) {
		item->prev = item - 1;
		item->next = item + 1;
	}

	item->prev = item - 1;
	item->next = NULL;
}

//---------------------------------------------------------------------------------------------------------------------

template <class TValue, unsigned TSize>
TValue* StaticList<TValue, TSize>::add(TValue value) {
	assert(free_);
	free_->value = value;

	free_ = free_->next;
}

//---------------------------------------------------------------------------------------------------------------------

template <class TValue, unsigned TSize>
void StaticList<TValue, TSize>::remove(const TValue* item) {
	assert(&items_[0] <= item && item < &items_[TSize] && ((unsigned)item - (unsigned)&items_[0]) % sizeof(Item*) == 0);

	item->prev->next = item->next;
	item->next->prev = item->prev;

	item->prev = NULL;
	item->next = free_;

	free_->prev = item;
}

//---------------------------------------------------------------------------------------------------------------------

template <class TValue, unsigned TSize>
void StaticList<TValue, TSize>::reset() {
	head_ = NULL;
	free_ = &items_[0];

	Item* item = free_;
	item->prev = NULL;
	item->next = item + 1;

	for (; item < &items_[TSize - 1]; ++item) {
		item->prev = item - 1;
		item->next = item + 1;
	}

	item->prev = item - 1;
	item->next = NULL;
}

//---------------------------------------------------------------------------------------------------------------------

}
