If you want to test this stuff out...

Follow this guide: https://dojofive.com/blog/using-the-qemu-emulator-with-zephyr-builds-and-vscode/

Ignore the cortex-debug stuff if you want. 
Make sure to clone this repository under the zephyrproject (or whatever the name is) folder.

Running a specific demo:

- cd to the demo folder
- make sure your shell is with the correct Python virtual environment
- run `west build -b qemu_cortex_m3`
- if that goes well, then run `west build -t run`

Zephyr RTOS: https://www.zephyrproject.org
