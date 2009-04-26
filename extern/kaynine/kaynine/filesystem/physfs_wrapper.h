#ifndef _KN_PHYSFS_WRAPPER_INCLUDED_
#define _KN_PHYSFS_WRAPPER_INCLUDED_


#include "../utility/singleton.h"


namespace kaynine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PhysFS : public kaynine::Singleton<PhysFS> {

public:
	class File {
	public:
		File(const char* path = 0) : file(path ? PHYSFS_openRead(path) : 0) {}
		~File() { if (isOpen()) close(); }

		inline bool open(const char* path) { file_ = PHYSFS_openRead(path); }
		inline isOpen() const { return file_ != 0; }
		inline void close() { PHYSFS_close(file_); }

		inline PHYSFS_sint64 size() const { return PHYSFS_fileLength(file_); };
		inline int read(void* buffer, PHYSFS_uint32 objSize, PHYSFS_uint32 objCount) { return PHYSFS_read(file_, buffer, objSize, objCount); }

	private:
		PHYSFS_file* file_;
	};

	inline void addToSearchPath(const char* path, bool last = false) { PHYSFS_AddToSearchPath(path, last ? 1 : 0); }
	inline void exists(const char* path) { PHYSFS_exists(path); }

private:
	inline PhysFS() { PHYSFS_init(0); }
	inline ~PhysFS() { PHYSFS_deinit(); }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}


#endif