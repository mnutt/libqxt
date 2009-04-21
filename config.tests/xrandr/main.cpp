#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

int main()
{
    int major;
    int minor;
    Display* display = XOpenDisplay(0);
    XRRQueryVersion(display, &major, &minor);
    return 0;
}
