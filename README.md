# Escape Obliterizer for the Game Boy Color
Escape Obliterizer is a really small game I made with a couple of friends during an hackathon in 2016 (available on [itch.io](https://9studios.itch.io/escape-obliterizer) and you can read about it on [Behance](https://www.behance.net/gallery/45779923/Escape-Obliterizer-HTML5-Game-(2016))). If you look at its core mechanics and visuals, it fits Game Boy Color hardware and its limitations (almost) perfectly. That said, why not just port it for the fun of it? Since it's a Game Boy Color game, it only runs on a Game Boy Color or Game Boy Advance. It doesn't run on any prior systems (DMG, SGB, POCKET).

## Compiling
The game is being developed in C using the Game Boy Development Kit. If you'd like to compile the code yourself, you first need to download and setup the last available version of [GBDK](http://gbdk.sourceforge.net/) on your machine. From there, all you have to do is clone this repo, run the **build.bat** script, and it should build and place a playable .GB file in the **build** folder (the current build of the game is already available in that folder, if you'd like to just play the game). 

If you're using [Visual Studio Code](https://code.visualstudio.com/) to edit the code, you'll probably enjoy the task included in the **.vscode** folder. It automates the building script to run every time you make changes to any **.c** or **.h** files, saving you from the hassle of having to run the script manually every time (uses the [Trigger Task On Save](https://marketplace.visualstudio.com/items?itemName=Gruntfuggly.triggertaskonsave) extension). 

## Development
The development is still ongoing, what's still missing from the original game? 
- Implementation of the horizontal lasers, bombs and the stun functionality. Vertical lasers are fully done and animated.
- Background music/beat (currently researching into GBT Player);
- Quote system on the game over screen (might have to delete this one, will see how it goes);

Stuff I've added in this version that's not on the original version:
- Credits screen;
- Player skin changing via cheat code (KONAMI CODE)
- Highscore saving (uses non-volatile ram, so no battery needed on real carts)
- Fade transitions between states (needs fixing on SGB)
- Player death dissolving animation. It's currently using a placeholder animation, needs redesign.

## Invaluable Resources
- Everything about the Game Boy Hardware: [The Ultimate Game Boy Talk](https://www.youtube.com/watch?v=HyzD8pNlpwI) / [Offical Nintendo Documentation](https://ia801906.us.archive.org/19/items/GameBoyProgManVer1.1/GameBoyProgManVer1.1.pdf)
- GBDK Documentation: [GBDK Libraries Documentation](http://gbdk.sourceforge.net/doc/html/book01.html)
- Sound FX: [The Skinny on GB Sound](https://github.com/bwhitman/pushpin/blob/master/src/gbsound.txt) / [Game Boy Sound Operation](https://gist.github.com/drhelius/3652407) 
- Saving to RAM - [GB Save Ram](http://www.devrs.com/gb/files/sram.txt)
- Useful demos - [GBDK Playground](https://github.com/mrombout/gbdk_playground)