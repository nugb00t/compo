#ifndef _KN_RESOURCES_INCLUDED_
#define _KN_RESOURCES_INCLUDED_

#include "../fs_tools/scoped_file.h"

namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Resources {
	template <class T>
	static void* load(MemoryPool<T>& pool, const TCHAR* const path);
};


template <class T>
void* Resources::load(MemoryPool<T>& pool, const TCHAR* const path) {
	ScopedFile file(path, _O_BINARY | _O_RDONLY | _O_SEQUENTIAL);
	if (!file.isOpen())
		return NULL;

	long length = file.length();
	if (!length)
		return NULL;

	void* buffer = pool.allocate(length);
	if (!buffer)
		return NULL;

	int ret = file.read(buffer, length);
	if (!ret || ret == -1 || ret != length)
		return NULL;

	return buffer;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace metro_engine

#endif
