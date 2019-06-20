c:\gbdk\bin\lcc -Wa-l -DUSE_SFR_FOR_REG -Wf-ba0 -c -o build/savestate.o game/savestate.c
c:\gbdk\bin\lcc -Wa-l -DUSE_SFR_FOR_REG -c -o build/main.o main.c
c:\gbdk\bin\lcc -Wl-yt3 -Wl-yo2 -Wl-ya1 -Wl-yp0x143=0x80 -DUSE_SFR_FOR_REG -o build/escape_obliterizer.gb build/main.o build/savestate.o
