# Escape Obliterizer for the Game Boy Color
Escape Obliterizer is a really small game I made with a couple of friends during an hackathon in 2016 (available on [itch.io](https://9studios.itch.io/escape-obliterizer) and you can read about it on [Behance](https://www.behance.net/gallery/45779923/Escape-Obliterizer-HTML5-Game-(2016))). If you look at its core mechanics and visuals, it fits Game Boy Color hardware and its limitations (almost) perfectly. That said, why not just port it for the fun of it? Due to its color palettes, the game only runs on Game Boy Color or Game Boy Advance systems, it doesn't run on any prior systems (DMG, SGB, MGB).

## Compiling
The game is being developed in C using the Game Boy Development Kit. If you'd like to compile the code yourself, you first need to download and setup the last available version of [GBDK](http://gbdk.sourceforge.net/) on your machine. All you have to do afterwards is clone this repo, run the **build.bat** script, and it should build a playable .GB file into the **build** folder (the current build of the game is already available in that folder, if you'd like to just test the current build). 

If you're using [Visual Studio Code](https://code.visualstudio.com/) to edit the code, you'll probably enjoy the task included in the **.vscode** folder. It automates the building script to run every time you make changes to any **.c** or **.h** files, saving you from the hassle of having to run the script manually every time (uses the [Trigger Task On Save](https://marketplace.visualstudio.com/items?itemName=Gruntfuggly.triggertaskonsave) extension). 

## Development
The development is still ongoing, what's still missing from the original game? 

GENERAL:

    - Music implementation (GBT Player ?)

STUN:

    - Draw the sprite animation for visual queue (4 frames)

    - Implement sprite animation on key press, on release animation resets

    - Play animation when stunned

    - Sound for when player is stunned

SCORE: 

    - When pressing a key (up down left right), score should implement faster

HAZARDS:

    - Everything for bombs and vertical lasers


## Flashing
If you'd like to play the game on real hardware, you can flash it onto chinese bootleg carts using specific hardware. I'm personally using GBxCartRW 1.3 without any hassle, but you can also use Bennvenn's Joey-Joebags or equivalent. Check the lcc flags on the **build.bat** script if you need ROM specifications.

## Invaluable Resources
- Everything about the Game Boy Hardware: [The Ultimate Game Boy Talk](https://www.youtube.com/watch?v=HyzD8pNlpwI) / [Offical Nintendo Documentation](https://ia801906.us.archive.org/19/items/GameBoyProgManVer1.1/GameBoyProgManVer1.1.pdf)
- GBDK Documentation: [GBDK Libraries Documentation](http://gbdk.sourceforge.net/doc/html/book01.html)
- Sound FX: [The Skinny on GB Sound](https://github.com/bwhitman/pushpin/blob/master/src/gbsound.txt) / [Game Boy Sound Operation](https://gist.github.com/drhelius/3652407) 
- Saving to RAM - [GB Save Ram](http://www.devrs.com/gb/files/sram.txt)
- Useful demos - [GBDK Playground](https://github.com/mrombout/gbdk_playground)