#pragma once

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
class InstanceCount {
public:
	InstanceCount()  { unsigned& c = count_(); ++c; }
	~InstanceCount() { unsigned& c = count_(); --c; }

	const unsigned count() const { count_(); }

private:
	static unsigned& count_() {
		static unsigned count_ = 0;
		return count_;
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
