#ifndef MESSAGE_SINK_W51_INCLUDED
#define MESSAGE_SINK_W51_INCLUDED

#ifdef PLATFORM_WIN51
namespace engine {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MessageSinkW51 : public kaynine::ThreadBase {
    static const unsigned PERIOD = 10;

public:
    // interface: kaynine::ThreadBase
    virtual bool initialize();
    virtual bool update();
    virtual void terminate();

private:
    static LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);

private:
    kaynine::Timer timer_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
#endif
