#include <stdio.h>
#include <unistd.h>
#include "io_tools.h"

#define BUFFERSIZE 100

// Macro that returns number of elements in an array
#define ARRAYSIZE(a) ((sizeof(a))/(sizeof(a[0])))

////////////////////////////////////////////////////////////////
// DEMO CODE
////////////////////////////////////////////////////////////////

// Demo of fprintf and fscanf.
void scan_print_demo(const struct DemoPacket *packet) 
{
    char buffer[BUFFERSIZE] = {0};    // buffer to read/write strings from/to files
    FILE *file = NULL;                // good initialization

    print_test_name("print_scan_demo");

    /*
     * int fprintf(FILE *, const char *, ...)
     * - prints a string to a file specified by user
     * - can format string
     * - extra runtime cost for formatting
     */
    
    // equivalent to printf("Writing to %s... ", packet->filename); 
    fprintf(stdout, "Writing to %s... ", packet->filename); 

    file = fopen(packet->filename, "w");                    // open file in write-mode
    fprintf(file, "%s\n%s\n", packet->msg1, packet->msg2);  // file contains 2 lines now with msg1 and msg2
    fclose(file);                                           // ALWAYS close your file once finished using the resource

    fprintf(stdout, "done.\n");

    /*
     * int fscanf(FILE *, const char *, ...)
     * - same pros and cons as fprintf
     * - extra con: reading a single line is quite difficult
     *      - %s means read from file until a whitespace is read and copy to buffer
     * - extra con: no safeguard against buffer not being large enough
     *      - can lead to seg fault/valgrind errors if buffer not large enough
     *      - try running print_scan_demo by changing BUFFERSIZE from 100 to 1
     */
    
    printf("Reading from %s... \n", packet->filename);

    file = fopen(packet->filename, "r");    // open file in read-mode

    fscanf(file, "%s", buffer);             // buffer: Hello'\0'
    //fscanf(file, "%[^]\n]\n", buffer);    // more correct way to read an entire line using fscanf
                                            // NOT REQUIRED TO KNOW FOR CLASS
                                            // (may still give seg fault if buffer not large enough)
                                            // uncomment this line and comment out the one above to see...
    printf("msg1: %s\n", buffer);           // prints msg1: Hello\n

    fscanf(file, "%s", buffer);             // buffer (overwritten): world.'\0'
    //fscanf(file, "%[^]\n]\n", buffer);    
    printf("msg2: %s\n", buffer);           // prints msg2: world.\n

    fclose(file);

    printf("done.\n");
}

// Demo of fgets and fputs.
void get_put_demo(const struct DemoPacket *packet) 
{
    FILE *file = NULL;
    char buffer[BUFFERSIZE] = {0};

    print_test_name("get_put_demo");

    /*
     * int fputs(const char *, FILE *)
     * - cannot format like fprintf
     * - writes to file EXACTLY what is in string
     */
    
    file = fopen(packet->filename, "w");
    fputs(packet->msg1, file);  // writes: Hello world.
    fputs("\n", file);          // writes: '\n'
    fputs(packet->msg2, file);  // writes: I am your conscience.
    fputs("\n", file);          // writes: '\n'
    fclose(file);

    /*
     * char * fgets(char *, int size, FILE *)
     * - cannot format like fscanf
     * - reading a single line is extremely easy
     * - reads at most (size - 1) number of bytes (it may only read a subset of a line)
     *      - stops reading after copying '\n' (if copying were possible)
     *      - the last char written into buffer is ALWAYS '\0'
     *      - guarantees not to write past the array
     *      - try running get_put_demo by changing BUFFERSIZE to 1, then try 2
     *          - are there any compiler or valgrind errors?
     *          - why is output for BUFFERSIZE == 1 different from BUFFERSIZE == 2?
     *          - why is output for BUFFERSIZE == 2 different from BUFFERSIZE == 100?
     */
    
    // the following assumes buffer has large size
    file = fopen(packet->filename, "r");
    fgets(buffer, ARRAYSIZE(buffer), file);     // buffer: Hello world.\n
    printf("msg1: %s", buffer);                 // prints: msg1: Hello world.\n
    fgets(buffer, ARRAYSIZE(buffer), file);     // buffer: I am your conscience.\n
    printf("msg2: %s", buffer);                 // prints: I am your conscience.\n
    fclose(file);
    
}

// Demo of fread and fwrite.
void read_write_demo(const struct DemoPacket *packet)
{
    FILE *file = NULL;

    print_test_name("read_write_demo");

    /*
     * size_t fwrite(const void *ptr, size_t size, size_t nitems, FILE *stream)
     * - writes nitems objects each size bytes long to stream
     */
    char arr[] = {0, 0, 0, 1};
    file = fopen(packet->filename, "w");
    fwrite(arr, sizeof(char), ARRAYSIZE(arr), file);
    fclose(file);
     
    /*
     * size_t fread(void *ptr, size_t size, size_t nitems, FILE *stream)
     * - reads nitems each size bytes long from stream
     *   and stores them in memory pointed by ptr.
     */
    
    // Sensible thing: read 4 items each one byte and store into array of chars
    char char_buffer[ARRAYSIZE(arr)] = {0};
    file = fopen(packet->filename, "r");
    fread(char_buffer, sizeof(char), ARRAYSIZE(char_buffer), file);
    fclose(file);
    /* char_buffer where each box is one BYTE
     * *-*-*-*-*
     * |0|0|0|1|
     * *-*-*-*-*
     */
    for (int i = 0; i < ARRAYSIZE(char_buffer); ++i) {
        printf("char_buffer[%d] == %d: %s\n", i, arr[i], 
                (char_buffer[i] == arr[i] ? "TRUE" : "FALSE"));
    }

    // Weird but legal: read 4 items each one byte and store into array of ints
    // The first number is 2^24. After learning endianness, it will be clearer why this is the case.
    int int_buffer[ARRAYSIZE(arr)] = {0};
    file = fopen(packet->filename, "r");
    fread(int_buffer, sizeof(char), ARRAYSIZE(int_buffer), file);
    fclose(file);
    /* int_buffer where each box is one BYTE
     * *-*-*-*-*-*---*-*
     * |0|0|0|1|0|...|0|
     * *-*-*-*-*-*---*-*
     */
    printf("int_buffer: ");
    for (int i = 0; i < ARRAYSIZE(int_buffer); ++i) {
        printf("%d ", int_buffer[i]);
    }
    printf("\n");
}

// This demo will demonstrate that stdout is line-buffered and stderr is unbuffered.
// This means stdout will not flush its contents to the terminal until it sees a newline.
// However, stderr will flush its contents immediately.
void std_demo()
{
    print_test_name("std_demo");
    fprintf(stdout, "From stdout: sorry I'm late");
    fprintf(stderr, "From stderr: I'm so punctual and amazing");
    // wait 1 second to show that stderr prints first
    sleep(1); 
    fprintf(stderr, "\n");
    fprintf(stdout, "\n");  // this is when stdout flushes the entire message to terminal
}

int main() 
{
    struct DemoPacket packet;
    packet.filename = "myiofile";
    packet.msg1 = "Hello world.";
    packet.msg2 = "I am your conscience.";

    // Comment out whichever test you do not want to run
    std_demo();
    scan_print_demo(&packet);
    //get_put_demo(&packet);
    //read_write_demo(&packet);
    return 0;
}
