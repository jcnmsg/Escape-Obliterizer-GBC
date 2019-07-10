# Escape Obliterizer Deluxe for the Game Boy Color
Escape Obliterizer is a really small game I made with a couple of friends when I was learning JavaScript during an hackathon in 2016 (available on [itch.io](https://9studios.itch.io/escape-obliterizer)). I just thought its core mechanics and visuals fitted the Game Boy Color hardware (almost) perfectly, so I decided to port it for the fun of it and as a way of learning my way around programming for the Game Boy, one of my favorite retro consoles of all time. It's a Game Boy Color specific game, so if you happen to jam this cart on any prior Game Boy models (DMG, SGB, MGB), you'll simply be greeted with a blank screen.

## Development
Developing for a retro console always poses some limitations and I sure have felt them, mostly in terms of ROM space. Exceeding 32kb of ROM size would imply including ROM banking into the code, which I have not accounted for when I started this project. Implementing ROM banking would probably mean redoing all of the code. For that reason, there's no music in the game. Implementing music features would probably take most space in bank 1, so I decided to keep that out. On the other hand, I have also managed to include new things that the original game didn't have, like a skin selection menu, credits, noticeable incremental difficulty, a death animation, etc. Please note that this was my first contact with the C language and Game Boy programming in general, so the code is not the best of examples right now. If I find the time and patience, I'll definitely clean and comment it and rewrite this section to let you know it has been done.

## Compiling
The game was developed in C using the Game Boy Development Kit. If you'd like to compile the code yourself, you first need to download and setup the last available version of [GBDK](http://gbdk.sourceforge.net/) on your machine. Then, clone this repo, run the **build.bat** script, and it should build a playable .GB file into the **build** folder. The most current build of the game can be found in the exact same folder. I've included a task in the **.vscode** folder for [Visual Studio Code](https://code.visualstudio.com/). It automates the building script to run automatically every time you make changes to any **.c**, **.h** or **.s** files (uses the [Trigger Task On Save](https://marketplace.visualstudio.com/items?itemName=Gruntfuggly.triggertaskonsave) extension). 

## Flashing
If you'd like to play the game on real hardware, you can flash it onto chinese bootleg carts using specific hardware. I'm personally using GBxCartRW 1.3 without any hassle, but you can also use Bennvenn's Joey-Joebags or equivalent. The ROM specifications are as follows (or you can just check the lcc flags on the **build.bat** script):

- MBC type: MBC1+RAM+BATTERY (battery for saving highscores)
- ROM: 32KB (no ROM banking)
- RAM: 8KB (1 bank)

## Invaluable Resources
- Everything about the Game Boy Hardware: [The Ultimate Game Boy Talk](https://www.youtube.com/watch?v=HyzD8pNlpwI) / [Official Nintendo Documentation](https://ia801906.us.archive.org/19/items/GameBoyProgManVer1.1/GameBoyProgManVer1.1.pdf)
- GBDK Documentation: [GBDK Libraries Documentation](http://gbdk.sourceforge.net/doc/html/book01.html)
- GBDK Programming Guidelines: [GBDK Programming Guidelines](http://gbdk.sourceforge.net/guidelines.html)
- Sound FX: [The Skinny on GB Sound](https://github.com/bwhitman/pushpin/blob/master/src/gbsound.txt) / [Game Boy Sound Operation](https://gist.github.com/drhelius/3652407) / [GBSoundDemo](https://github.com/Zal0/GBSoundDemo/blob/master/sound.c)
- Saving to RAM - [GB Save Ram](http://www.devrs.com/gb/files/sram.txt)
- Useful demos - [GBDK Playground](https://github.com/mrombout/gbdk_playground)
- Tools for Game Boy Color Development - [Robert Ramey Software Development](http://rrsd.com/software_development/gameboy_development/)
- Beginner Tutorials - [GamingMonsters Youtube Channel](https://www.youtube.com/playlist?list=PLeEj4c2zF7PaFv5MPYhNAkBGrkx4iPGJo)

## Special Thanks
A special thanks is due to everyone at the [GBDev Community](https://github.com/gbdev/awesome-gbdev) Discord server, whom have answered all my questions and taught me the intricacies of developing for the Game Boy. These are the people who are keeping these consoles alive today and they sure deserve our appreciation.