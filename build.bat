c:\gbdk\bin\lcc -Wa-l -DUSE_SFR_FOR_REG -Wf-ba0 -c -o build/savestate.o game/savestate.c
c:\gbdk\bin\lcc -Wa-l -DUSE_SFR_FOR_REG -c -o build/main.o main.c
c:\gbdk\bin\lcc -Wl-yt3 -Wl-yo4 -Wl-ya1 -DUSE_SFR_FOR_REG -Wl-yp0x143=0xc0 -o build/escape_obliterizer.gb build/main.o build/savestate.o
