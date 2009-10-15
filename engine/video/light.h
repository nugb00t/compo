#ifndef LIGHT_INCLUDED
#define LIGHT_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Light : public IntrusivePtrBase, public Updatable {
};

typedef boost::intrusive_ptr<Light> LightPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace engine

#endif
