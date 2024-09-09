# MiniApp

## Overview

This project consists of two main components:
1. **C++ Application**: Generates numbers and serves them via a WebSocket server.
2. **Python Bokeh Application**: Displays these numbers in a web-based GUI.

## Building the C++ Application

1. Navigate to the build directory:

   ```bash
   cd genNumber && cd build
   ```

2. Build the application:
    ```bash
   cmake .. && make -j8
   ```

## Running the WebSocket Server
1. Start the WebSocket server by running the C++ application:
    ```bash
    ./genNumber
   ```

## Setting Up the Python Environment
1. Install the required Python packages:
    ```bash
    python3 -m pip install -r requirements.txt
    ```

## Running the Bokeh GUI

1. Launch the Bokeh application:
    ```bash
    python3 gui.py
    ```
