#ifndef MESSAGE_SINK_INTERFACE_INCLUDED
#define MESSAGE_SINK_INTERFACE_INCLUDED

namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef kaynine::Holder<class MessageSinkInterface> MessageSink;

class MessageSinkInterface : public Callable, public kaynine::IntrusivePtrBase {
public:
	MessageSinkInterface() { MessageSink::set(*this); }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef boost::intrusive_ptr<MessageSinkInterface> MessageSinkPtr;

}

#endif
