#pragma once

#include <assert.h>

#include "../debug/macros.h"

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// [FACE] <> [HEAD] <> <used> <> <last> <> [FREE] <> <free> <> [BACK]  <great nothing............>
// 
template <class TValue, unsigned TSize>
class StaticList {
public:
	typedef TValue VALUE_TYPE;
	static const unsigned SIZE = TSize;	// the structure needs the last terminator cell

	//-----------------------------------------------------------------------------------------------------------------

protected:

#pragma pack(push, 4)
	struct Cell {
		Cell* prev;
		Cell* next;

		TValue value;
	};
#pragma pack(pop)

	//-----------------------------------------------------------------------------------------------------------------

public:

	class Range {
	public:
		inline Range(StaticList& list) : list_(list), current_(list_.face_->next) {}

		inline const bool finished()		{ return current_ == list_.free_; }
		inline void next()					{ current_ = current_->next;      }
		inline void remove();

		inline		 TValue& get()			{ return current_->value;		  }
		inline const TValue& get() const	{ return current_->value;		  }

		inline const unsigned index() const	{ return current_ - list_.face_;  }

	private:
		StaticList& list_;
		Cell* current_;
	};

	//-----------------------------------------------------------------------------------------------------------------

public:
	StaticList();

	inline const unsigned add(const TValue value);
	inline void remove(const unsigned i);
	inline void reset();

	inline		 TValue& operator [](const unsigned i)		 { assert(valid(i)); return chain_[i]; }
	inline const TValue& operator [](const unsigned i) const { assert(valid(i)); return chain_[i]; }

private:
	inline void link(Cell* left, Cell* right);
	inline void insert(Cell* cell, Cell* before);

private:
    Cell chain_[SIZE + 2];

	Cell* face_;
	Cell* free_;
	Cell* back_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TValue, unsigned TSize>
void StaticList<TValue, TSize>::Range::remove() {
	current_ = current_->prev;
	list_.remove(current->next);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TValue, unsigned TSize>
StaticList<TValue, TSize>::StaticList() : face_(chain_), free_(face_ + 1), back_(free_) {
	face_->prev = NULL;

	link(face_, free_);

	free_->next = NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TValue, unsigned TSize>
const unsigned StaticList<TValue, TSize>::add(TValue value) {
	if (free_ == back_) {			// no free prepared items available - expand the chain
		assert(back_ < &chain_[SIZE + 2]);
		
		++back_;					// expand
		
		link(free_, back_);			// make a new link to the expansion cell
	}

	free_->value = value;

	free_ = free_->next;
	return free_->prev - face_ - 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TValue, unsigned TSize>
void StaticList<TValue, TSize>::remove(const unsigned i) {
	assert(0 <= i && i < SIZE - 2);

	Cell* cell = &chain_[i + 1];
	
	link(cell->prev, cell->next);	// cross-link the neighbors
	insert(cell, free_);			// link newly emptied cell between 'free->prev' and 'free'

	free_ = cell;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TValue, unsigned TSize>
void StaticList<TValue, TSize>::reset() {
	face_ = chain_;
	free_ = back_ = face_ + 1;

	// initial links
	face_->prev = NULL;

	link(face_, free_);

	free_->next = NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class TValue, unsigned TSize>
void StaticList<TValue, TSize>::link(Cell* left, Cell* right) {
	left->next = right;
	right->prev = left;
}

template <class TValue, unsigned TSize>
void StaticList<TValue, TSize>::insert(Cell* cell, Cell* before) {
	before->prev->next = cell;
	cell->prev = before->prev;

	cell->next = before;
	before->prev = cell;
}

//---------------------------------------------------------------------------------------------------------------------

}
