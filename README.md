# MemTreeVisualizer

This program is a tool for visualizing the hierarchy of virtual addresses from Linux's /proc/pid/pagemap file.

## Build

To build the program, configure and build it using CMake:

```bash
cmake -S . -B build
cmake --build build
```

## Usage

To get the pagemap data from Linux's /proc/pid/pagemap file, you can use the [pagemap](https://github.com/dwks/pagemap) utility:

```bash
pagemap $PID > pagemap.data
```

where `$PID` is the process ID of the process whose pagemap data you want to retrieve. If you want to get the pagemap data for the current process (terminal), you can use `$$`:

```bash
pagemap $$ > pagemap.data
```

Then, run the following command:

```bash
MemTreeVisualizer < pagemap.data
```

The program will read the pagemap data from the specified file and print it in a tree-like structure.
