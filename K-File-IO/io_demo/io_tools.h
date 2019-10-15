#ifndef __IO_TOOLS__
#define __IO_TOOLS__

// DO NOT WORRY ABOUT THE FOLLOWING 
// They are tools to make code in io_demo.c cleaner.

// DemoPacket is a struct to hold onto all information needed for the demos.
// This is a nice way to not flood the function parameters, so that we only pass in one parameter.
struct DemoPacket
{
    const char *filename;       // points to name of our file
    const char *msg1;           // points to message 1 content
    const char *msg2;           // points to message 2 content
};

// Prints test name preceeded and succeeded by 20 dashes
void print_test_name(const char *test_name);

#endif
