c:\gbdk\bin\lcc -Wa-l -Wf-ba0 -DUSE_SFR_FOR_REG -c -o build/savestate.o game/savestate.c
c:\gbdk\bin\lcc -Wa-l -DUSE_SFR_FOR_REG -c -o build/main.o main.c
c:\gbdk\bin\lcc -Wl-yt3 -Wl-yo8 -Wl-ya4 -Wl-yp0x143=0x80 -DUSE_SFR_FOR_REG -o build/main.gb build/main.o build/savestate.o
