![Escape Obliterizer DX](https://img.itch.zone/aW1nLzI3OTg5MDUucG5n/original/mosMtU.png)
# Escape Obliterizer Deluxe for the Game Boy Color
Escape Obliterizer Deluxe is a remake of [this game](https://ninestudios.itch.io/escape-obliterizer) for the Game Boy Color. The ROM is available for download at [my website](https://joaomakes.games/games/escape-obliterizer-deluxe/), [itch.io](https://joaomakesgames.itch.io/escape-obliterizer-dx) and [romhacking.net](https://www.romhacking.net/homebrew/122/) and a blog article detailing the development process can be found [here](https://joaomakes.games/game-development/the-making-of-a-game-boy-color-game-in-2019-from-zero-to-physical/).

## :hammer: Development
The game was developed in C using the last known version of Game Boy Development Kit (GBDK, not [GBDK-2020](https://github.com/gbdk-2020/gbdk-2020)). This was my first contact with the C language and Game Boy programming in general, so while the code might not be the best of examples, it might be enough to get you going if you're a newb yourself.

## :file_folder: Compiling (on Windows)

If you'd like to compile the code yourself, you first need to download and setup the last version of [GBDK](http://gbdk.sourceforge.net/) on your machine and clone this repository. After doing so, running the **build.bat** script should build a playable .GB file into the **build** folder automatically. 

## :computer: Flashing
If you'd like to play the game on real hardware, you can flash it onto chinese bootleg carts using specific hardware. I'm personally using GBxCartRW 1.3 without any hassle, but you can also use Bennvenn's Joey-Joebags or equivalent. The ROM specifications are as follows (or you can just check the lcc flags on the **build.bat** script):

- MBC type: MBC1+RAM+BATTERY (battery for saving highscores)
- ROM: 32KB (no ROM banking)
- RAM: 8KB (1 bank)

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
A special thanks is due to everyone at the [GBDev Community](https://github.com/gbdev/awesome-gbdev) Discord server, whom have answered all my questions and taught me the intricacies of developing for the Game Boy. These are the people who are keeping these consoles alive today and they sure deserve our appreciation. Also thanks to everyone on [/r/GameBoy](https://www.reddit.com/r/Gameboy/) and on my Instagram page who have taken some of their time to playtest this really small and silly game.
