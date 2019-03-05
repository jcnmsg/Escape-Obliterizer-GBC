# Escape Obliterizer for the Game Boy
Escape Obliterizer is a really small JavaScript game I made with a couple of friends during an hackathon in 2016 (original game is available on [itch.io](https://9studios.itch.io/escape-obliterizer) and you can read about it on [Behance](https://www.behance.net/gallery/45779923/Escape-Obliterizer-HTML5-Game-(2016))). If you look at its core mechanics and visuals, the game is so simple that it fits the original Game Boy hardware and its limitations perfectly. That said, why not just port it for the fun of it? 

![Splash screen for the GameBoy version of the game](https://i.imgur.com/3gkS2pz.gif)

## Compiling
The game is being developed in C using the Game Boy Development Kit. If you'd like to compile the code yourself, you first need to download and setup [GBDK](http://gbdk.sourceforge.net/) on your machine. From there, all you have to do is clone this repo, run the **build.bat** script, and you should have the output file (a playable .GB ROM file you can run on [BGB](http://bgb.bircd.org/)) in the **build** folder. If you're using [Visual Studio Code](https://code.visualstudio.com/), you'll probably enjoy the task included in the **.vscode** folder. It automates the building script to run every time you make changes to the code, saving you the hassle of having to run the script manually every time (makes use of the [Trigger Task On Save](https://marketplace.visualstudio.com/items?itemName=Gruntfuggly.triggertaskonsave) extension). I'm trying to keep a simple folder structure and clean/commented code throughout development, but beware, there might be some hacks here and there.

## Development
The development is just starting so I'll keep a checklist of what I've done so far and what I still need to do, below. This way, if you're just here to learn something specific or read some code, you can know what you'll find in this repo beforehand. List is not complete, so I'll keep adding to it as I go along...
- [x] Setup development environment and folder structure 
- [x] Basic background and player sprite implementation
- [x] Basic player movement based on user input 
- [x] Implementation of basic game states (splash screen, main menu, game loop, game over screen)
- [x] Score implementation (counter and typefont display)
- [ ] ~~Set sprite priority flags for player vs hazards~~
- [ ] Invert color palettes to use 4 colors
- [ ] Add music and sound effects
- [ ] Design and add splash screen
- [ ] Design and add pause screen
- [ ] Implementation of multiple hazards (sprite animation and collision detection)
- [ ] Beautify: "fade" transitions between states, general idle animations on menus
- [ ] Implement support for Game Boy Color's color palettes
