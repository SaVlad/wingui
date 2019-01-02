# wingui
C++ library to make you Windows GUI easier.

Standard Win32 API for windows is bit complicated and C compatibility makes it even harder. This library's purpose is to bring OOP into your project, so you don't have to write tons of boilerplate to display "Hello World" or simple window with two buttons.

# Features
Library is far from being done. So far only those features has been completed:
* Controls management
* Window creation
* Window notification listening
* Some exceptions for Win32 **ERROR_** constants
* Few miscellaneous functions and typedefs

# Usage
* Clone this repo and compile `wingui` project. It will output `wingui.lib`.
* Copy `.h` header files somewhere you like.
* Link `wingui.lib` binary file to you project and then include `wingui.h`.
* In most cases you'd like to create `wg::controls::Window` class and find your way from here.
* You also can define `WG_USING_ALL` before including `wingui.h` to enable all library namespaces.

Precompiled binaries will be released later, when I'm satisfied with functionality.
*(I promise, I'll arrange files better later)*

## Controls management
Using handy `wg::controls::Control` class, Window and other controls *(in future)* are easily created and managed. Here's list what you can do to any control (including Windows):
* Get/Set Position
* Get/Set Size
* Get/Set Text *(C and C++ strings both supported)*
* Send custom message
* Get native handle

## Window creation
Window creation is easy really. You just call a contructor and that's it. Constructor handles window class creation and registering. You can and should pass `WindowStyle`, `WindowStyleEx` and `WindowClassStyle` to constructor to tune window for your needs. Thos styles available as `enum`'s and you can combine them with OR `|` operator. Example:
```
new Window(
    WindowStyle::HasCaption |
    WindowStyle::HasWindowMenu
    ,
    WindowClassStyle::MoveSizeRedraw |
    WindowClassStyle::DropShadow);
```

## Window notification listening
`wg::controls::Window` class has `MessagePump` function that runs `GetMessage` loop. Also, Window constructor creates and set's up `WndProc` to handle message and notifications. By default, Window has no behaviour for any message received, but you can add some using `SetEventListener` function.
`SetEventListener` registers `wg::controls::WindowEventListener` object as message handler. It has quite a lot of functions to register your own handler for notification messages. You don't have to parse `WPARAM` and `LPARAM` yourself! EventListener does it for you and passes parameters to your handlers. Example:
```
bool CALLBACK MouseDownHandler(Window*window, MouseButton button, WORD x, WORD y, bool shift, bool ctrl)
{
    if(HASFLAG(button, MouseButton::LeftButton)){
        printf("Left mouse button down at %d, %d\n", x, y);
        return true;
    }
    return false;
}
...
Window *window = new Window();
WindowEventListener *el = new WindowEventListener();
el->SetMouseDownCallback(MouseDownHandler);
window->SetEventListener(el);
window->Show();
window->MessagePump();
```
This is code is shortened obviously, but you can grasp possibilities of WindowEventListener. At the moment, there are **32** notifications supported. Each is parsed, if needed, and passed to your handler.
Also notice, that handler must return a `bool`. If handler returned `true`, message considered as handled. If `false` is returned, then message is passed to `DefWindowProc` and handled by system.

## Win32Exception
`wg::exceptions::Win32Exception` is an all purpose class for standard Win32 errors. You pass it code from `GetLastError` and it extracts description from it.
There are few more specific exceptions for you to catch:
* `InvalidHandleException`
* `OutOfMemoryException`
You can create the yourself, or call `ThrowWin32Exception` function that deduces appropriate exception class for passed error code and throws it immediately.

## Miscellaneous functions and types
There are some helper functions that are widely used across library and open for you too:
* `HASFLAG(value, flag)` macro to check if `flag` is present in `type`.
* `MAKEFLAGS(type)` macro that spawns inline OR `|` operator for enums.
* `_tstring` typedef that resolves to `std::wstring`, if `UNICODE` is defined, and `std::string` otherwise.
* `HideConsole` function that hides from user console window if any.
* `ShowConsole` function that show user console window if one is allocated.
* `assert_win32(bool)` function that throws `wg::exceptions::Win32Exception` or more specific one in case condition is `false`.
* `assert_win32_maybe` function that throw `wg::exceptions::Win32Exception` or more specific one in case there's error pending in `GetLastError`.

## Changelog
### 0.1.0
* Initial commit.
* Window class.
* Exceptions, misc. functions, etc.

### 0.1.1
* Classes distributed to separate namespaces.
* EventListener renamed to WindowEventListener.