# Escape Obliterizer for the Game Boy Color
Escape Obliterizer is a really small game I made with a couple of friends during an hackathon in 2016 (available on [itch.io](https://9studios.itch.io/escape-obliterizer) and you can read about it on [Behance](https://www.behance.net/gallery/45779923/Escape-Obliterizer-HTML5-Game-(2016))). If you look at its core mechanics and visuals, it fits Game Boy Color hardware and its limitations (almost) perfectly. That said, why not just port it for the fun of it? It runs on all Game Boy models, but you might encounter some minor graphical glitches on DMG and MGB models because they handle palettes and sprite priority differently.

## Compiling
The game is being developed in C using the Game Boy Development Kit. If you'd like to compile the code yourself, you first need to download and setup the last available version of [GBDK](http://gbdk.sourceforge.net/) on your machine. All you have to do afterwards is clone this repo, run the **build.bat** script, and it should build a playable .GB file into the **build** folder (the current build of the game is already available in that folder, if you'd like to just test the current build). 

If you're using [Visual Studio Code](https://code.visualstudio.com/) to edit the code, you'll probably enjoy the task included in the **.vscode** folder. It automates the building script to run every time you make changes to any **.c** or **.h** files, saving you from the hassle of having to run the script manually every time (uses the [Trigger Task On Save](https://marketplace.visualstudio.com/items?itemName=Gruntfuggly.triggertaskonsave) extension). 

## Development
The development is still ongoing, will update once it's done.

## Flashing
If you'd like to play the game on real hardware, you can flash it onto chinese bootleg carts using specific hardware. I'm personally using GBxCartRW 1.3 without any hassle, but you can also use Bennvenn's Joey-Joebags or equivalent. The ROM specifications are as follows (or you can just check the lcc flags on the **build.bat** script):

- MBC type: MBC1+RAM+BATTERY (battery for saving highscores)
- ROM: 32KB (no ROM banking)
- RAM: 8KB (1 bank)

## Invaluable Resources
- Everything about the Game Boy Hardware: [The Ultimate Game Boy Talk](https://www.youtube.com/watch?v=HyzD8pNlpwI) / [Official Nintendo Documentation](https://ia801906.us.archive.org/19/items/GameBoyProgManVer1.1/GameBoyProgManVer1.1.pdf)
- GBDK Documentation: [GBDK Libraries Documentation](http://gbdk.sourceforge.net/doc/html/book01.html)
- Sound FX: [The Skinny on GB Sound](https://github.com/bwhitman/pushpin/blob/master/src/gbsound.txt) / [Game Boy Sound Operation](https://gist.github.com/drhelius/3652407) / [GBSoundDemo](https://github.com/Zal0/GBSoundDemo/blob/master/sound.c)
- Saving to RAM - [GB Save Ram](http://www.devrs.com/gb/files/sram.txt)
- Useful demos - [GBDK Playground](https://github.com/mrombout/gbdk_playground)
- Tools for Game Boy Color Development - [Robert Ramey Software Development](http://rrsd.com/software_development/gameboy_development/)

## Special Thanks
A special thanks is due to everyone at the [GBDev Community](https://github.com/gbdev/awesome-gbdev) Discord server, whom have answered all my questions and taught me the intricacies of developing for the Game Boy. These are the people who are keeping these consoles alive today and they sure deserve our appreciation.