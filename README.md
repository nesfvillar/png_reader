# png_reader

## Usage
In order to compile the program, just use `make`.

Run the compiled binary, located in the new folder `bin/`, with the png images to run as arguments in the terminal. You should see all the chunk sizes, names, and cyclic-redundancy-check (CRC) code.

## Using the chunks
If you intend to use these chunks, or maybe you intend to add some 'secret' chunk with information, you can use the function `png_read` declared in png_reader.h. It returns a dynamic array of all the chunks that make the image.

