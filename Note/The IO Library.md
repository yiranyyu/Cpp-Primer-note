# The IO Library

* Managing the Output Buffer
  + flush manipulator flushes the stream
  + ends manipulator inserts a null character into the buffer and then flushes the stream
  + Use the unitbuf manipulator if we want to flush after every output.
  + Use the nounitbuf manipulator restores the stream to use normal, system-managed buffer flushing.
  + Output buffers are not flushed if program terminates abnormally.
  + Tying Input and Output Stream Together
    - When an input stream is tied to an output stream, any attempt to read the input stream will first flush the buffer associated with the output stream.
    - Interactive systems usually should tie their input stream to their output stream. Doing so means that all output, which might include the prompts to the user, will be written before attempting to read the input

```C++
    auto p_cout = cin.tie();
    bool same = (p_cout == &cout); // true

    // tie cin with cerr by transfer a pointer to the stream and return the old tied stream
    auto p_cout_1 = cin.tie(&cerr);
    cin.tie(p_cout_1);// retie cin with cout(normal state)
```

  + Each stream can be tied to at most one stream at a time. However, multiple streams can tie themselves to the same ostream (both cin and cerr are tied to cout).
* File Input and Output
  + Once a file stream has been opened, it remains associated with the specified file. Indeed, calling open on a file stream that is already open will fail and set failbit.
  + When an fstream objects is destroyed, close is called automatically.
  + File Modes
    - out may be set only for an ofstream or fstream object
    - in may set only for an ifstream or fstream object
    - trunc may be set only when out is also specified
    - app mode may be specified so long as trunc is not. If app is specified, the file is always opened in output mode, even if out was not explicitly specified.
    - By default, a file opened in out mode is truncated even if we do not specify trunc. To preserve the contents of a file opened with out, either we must also specify app, in which case we can write only at the end of the file, or we must also specify in, in which case the file is open for both input and output.
    - The ate and binary modes may be specified on any file stream object type and in combination with any other file modes.
  + The only way to preserve the existing data in a file opened by an ofstream is to specify app or in mode explicitly