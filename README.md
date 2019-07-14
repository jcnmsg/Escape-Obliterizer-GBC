# Escape Obliterizer DX for the Game Boy Color
Escape Obliterizer is a really small game I made with a couple of friends during an hackathon in 2016 (it's available on [itch.io](https://9studios.itch.io/escape-obliterizer)). Back in the day we were just getting into JavaScript so naturally, the code was pretty messed up. I did however really like how the game turned out so I decided to port it to the Game Boy Color for the fun of it, as a way of learning my way around programming for the Game Boy. It's a Game Boy Color specific game, so if you happen to jam this cart into any prior Game Boy models (DMG, SGB, MGB), you'll simply be greeted with a blank screen.

## :hammer: Development
Developing for a retro console always poses some limitations and I sure have felt them, mostly in terms of ROM space. Exceeding 32kb of ROM size would imply including ROM banking into the code, which I have not accounted for when I started this project. Implementing ROM banking would probably mean redoing all of the code. For that reason, there's no music in the game. Implementing music features would probably take most space in bank 1, so I decided to keep that out. On the other hand, I have also managed to include new things that the original game didn't have, like a skin selection menu, credits, noticeable incremental difficulty, a death animation, etc (hence the DX terminology). Please note that this was my first contact with the C language and Game Boy programming in general, so the code is not the best of examples. 

## :file_folder: Compiling
The game was developed in C using the Game Boy Development Kit. If you'd like to compile the code yourself, you first need to download and setup the last available version of [GBDK](http://gbdk.sourceforge.net/) on your machine. Then, clone this repo, run the **build.bat** script, and it should build a playable .GB file into the **build** folder. The most current build of the game can be found in the exact same folder. I've also included a task in the **.vscode** folder for [Visual Studio Code](https://code.visualstudio.com/) to make your life easier. It automates the building script to run automatically every time you make changes to any **.c**, **.h** or **.s** files (requires the [Trigger Task On Save](https://marketplace.visualstudio.com/items?itemName=Gruntfuggly.triggertaskonsave) extension). 

## :computer: Flashing
If you'd like to play the game on real hardware, you can flash it onto chinese bootleg carts using specific hardware. I'm personally using GBxCartRW 1.3 without any hassle, but you can also use Bennvenn's Joey-Joebags or equivalent. The ROM specifications are as follows (or you can just check the lcc flags on the **build.bat** script):

- MBC type: MBC1+RAM+BATTERY (battery for saving highscores)
- ROM: 32KB (no ROM banking)
- RAM: 8KB (1 bank)

## :video_game: Playtesting
I have playtested it alone, so the chance of finding bugs is definitely not ruled out. The current build is available in the build folder, so if you end up downloading, playing and finding any unknown bug not stated in the list below, please report it to me so I can look into it. I have played it in a couple of different emulators for the Web, Android, Windows and PSP, as well as on real hardware (Game Boy Advance SP 001 and 101, Game Boy Advance and Game Boy Color).

## :beetle: Known bugs
- The colors are way too dark when played using a classic Game Boy Advance. That's due to the way the GBA translates Game Boy Color palettes. The current colors have been balanced to fit GBA SPs without washing out the GBCs' colors too much, so playing it on an SP (001 or 101) or Game Boy Color fixes it;
- When you switch directions too fast without releasing the buttons (eg. you go from left to right but don't pass in the middle position), the stun counter doesn't reset, meaning you can get stunned for doing something that was ok in the original game. Easily fixable by adding a direction flag, but I think it really adds to the challenge anyway, so I'm probably keeping this one;

## :notebook_with_decorative_cover: Invaluable Resources
- Everything about the Game Boy Hardware: [The Ultimate Game Boy Talk](https://www.youtube.com/watch?v=HyzD8pNlpwI) / [Official Nintendo Documentation](https://ia801906.us.archive.org/19/items/GameBoyProgManVer1.1/GameBoyProgManVer1.1.pdf)
- GBDK Documentation: [GBDK Libraries Documentation](http://gbdk.sourceforge.net/doc/html/book01.html)
- GBDK Programming Guidelines: [GBDK Programming Guidelines](http://gbdk.sourceforge.net/guidelines.html)
- Sound FX: [The Skinny on GB Sound](https://github.com/bwhitman/pushpin/blob/master/src/gbsound.txt) / [Game Boy Sound Operation](https://gist.github.com/drhelius/3652407) / [GBSoundDemo](https://github.com/Zal0/GBSoundDemo/blob/master/sound.c)
- Saving to RAM - [GB Save Ram](http://www.devrs.com/gb/files/sram.txt)
- Useful demos - [GBDK Playground](https://github.com/mrombout/gbdk_playground)
- Tools for Game Boy Color Development - [Robert Ramey Software Development](http://rrsd.com/software_development/gameboy_development/)
- Beginner Tutorials - [GamingMonsters Youtube Channel](https://www.youtube.com/playlist?list=PLeEj4c2zF7PaFv5MPYhNAkBGrkx4iPGJo)

## :beers: Special Thanks
A special thanks is due to everyone at the [GBDev Community](https://github.com/gbdev/awesome-gbdev) Discord server, whom have answered all my questions and taught me the intricacies of developing for the Game Boy. These are the people who are keeping these consoles alive today and they sure deserve our appreciation.
