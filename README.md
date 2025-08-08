# depens
```
sudo apt install libsdl1.2-dev

```

# test
```
cd test && mkdir build && cd build && make -j4
```

# build sigle file
```
gcc listViewVar.c -o listnew libucgui.a -IGUI_X -IGUI/Core -IGUI/Widget -IGUI/WM -lSDL
```
