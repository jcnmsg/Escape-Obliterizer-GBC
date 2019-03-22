# Escape Obliterizer for the Game Boy
Escape Obliterizer is a really small JavaScript game I made with a couple of friends during an hackathon in 2016 (original game is available on [itch.io](https://9studios.itch.io/escape-obliterizer) and you can read about it on [Behance](https://www.behance.net/gallery/45779923/Escape-Obliterizer-HTML5-Game-(2016))). If you look at its core mechanics and visuals, the game is so simple that it fits the original Game Boy hardware and its limitations (almost) perfectly. That said, why not just port it for the fun of it? 

![GIF of the current build](https://i.imgur.com/mLxwB2y.gif)

## Compiling
The game is being developed in C using the Game Boy Development Kit. If you'd like to compile the code yourself, you first need to download and setup the last available version of [GBDK](http://gbdk.sourceforge.net/) on your machine. From there, all you have to do is clone this repo, run the **build.bat** script, and it should build and place a playable .GB file in the **build** folder (the current build of the game is already available in that folder, if you'd like to just play the game). 

If you're using [Visual Studio Code](https://code.visualstudio.com/) to edit the code, you'll probably enjoy the task included in the **.vscode** folder. It automates the building script to run every time you make changes to any **.c** or **.h** files, saving you from the hassle of having to run the script manually every time (uses the [Trigger Task On Save](https://marketplace.visualstudio.com/items?itemName=Gruntfuggly.triggertaskonsave) extension). 

## Development
The development is just starting so I'll keep a checklist of what I've done so far and what I still need to do, below. This way, if you're just here to learn something specific or read some code, you can know what you'll find in this repo beforehand. List is not complete, so I'll keep adding to it as I go along...
- [x] Setup development environment and folder structure 
- [x] Basic background and player sprite implementation
- [x] Basic player movement based on user input 
- [x] Implementation of basic game states (splash screen, main menu, game loop, game over screen)
- [x] Score implementation (counter and typefont display)
- [x] ~~Set sprite priority flags for player vs hazards~~ Change player sprite order to 39th on the OAM to allow hazards to overlap it
- [x] Implementation of the vertical lasers with animations, collisions and sound
- [ ] Implementation of the horizontal lasers with animations, collisions and sound
- [ ] Implementation of the bombs with animations, collisions and sound
- [ ] Implementation of the 'Stun' with animations
- [ ] Player death animation
- [ ] Add background music/beat like the original
- [ ] Design and add splash screen
- [x] Design and add pause screen
- [ ] Add Main-Menu Interactivity
- [ ] Add credits screen
- [ ] Save highscores to non-volatile RAM
- [ ] Design and add interactive game over screen with a "random quote system" like the original
- [x] Beautify: "fade" transitions between states
- [x] Cheat code on menu (UUDDLRLRBA)
- [ ] Implement support for Game Boy Color's color palettes

## Invaluable Resources
- Everything about the Game Boy Hardware: [The Ultimate Game Boy Talk](https://www.youtube.com/watch?v=HyzD8pNlpwI) / [Offical Nintendo Documentation](https://ia801906.us.archive.org/19/items/GameBoyProgManVer1.1/GameBoyProgManVer1.1.pdf)
- GBDK Documentation: [GBDK Libraries Documentation](http://gbdk.sourceforge.net/doc/html/book01.html)
- Sound FX: [The Skinny on GB Sound](https://github.com/bwhitman/pushpin/blob/master/src/gbsound.txt) / [Game Boy Sound Operation](https://gist.github.com/drhelius/3652407) 
- Saving to RAM - [GB Save Ram](http://www.devrs.com/gb/files/sram.txt)