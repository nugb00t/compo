#ifndef MESSAGE_SINK_INTERFACE_INCLUDED
#define MESSAGE_SINK_INTERFACE_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Input system that tracks the time of the input event in addition to the event itself.
// May allow for more precise (?) button handling and / or smarter (?) axis interpolation.
class MessageSinkInterface : public Callable, public IntrusivePtrBase {
public:
	MessageSinkInterface();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Holder<MessageSinkInterface> MessageSink;
typedef boost::intrusive_ptr<MessageSinkInterface> MessageSinkPtr;

}

#endif
