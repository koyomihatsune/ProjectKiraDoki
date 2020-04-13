**2020/04/12 (pause game, better GUI, remove binary)**

- added the ability to pause the game
- cleaned the repository
- better note handling
- fixed mouseEvent lag
- better stage ingame quality
- added countdown and fixed songGuide before game
- changed engines to cpp and header files
- new readme.md

**2020/04/09 (songGuide in newGame, UI improved, lower CPU)**

- added songGuide in a few seconds after press play to show how to play the game.
- improved the UI
- new sfx and arts
- lower the CPU usage by reduce usage of SDL_PollEvent and imageEngine
- changed textEngine to handle font styles
- add Release mode from Visual Studio to test the game

**2020/04/07 (improved songPicker and newGame, turn off vsync)**

- added song list, difficulty list to choose in songPicker and new game input variables to newGame)
- add constants of positions to easily make changes to game UI later
- added some graphics
- fixed mouse input which was not handling well.
- fixed bad quality textEngine input and game animation.

**added some stuffs**

**2020/04/06 (new GUI, songPicker)**

- fixed almost every memory leak
- added new GUI but uncompleted
- added an uncompleted songPicker
- move source code to a new folder called Source
- made a playable game in folder KiraDokiProject_Playable as requested by teacher

**2020/04/01 Late (musicEngine + noteHandle + fps fix)**

- Added musicEngine to sync with every variables (bpm, song difficulties, rendering frames)
- Better noteHandle added note speed, song difficulties & bpm support)
- Added base of key events to develop later
- Happy April Fools' Day!

**2020/04/01 Early (new header & cpp)**

Added the SDL_utils + newGame + noteHandle header & cpp.
noteHandle now can spawn & delete unlimited notes.
RandomSpawn() now works correctly.
Continued working on sound control but nothing achieved.

**2020/03/31 - Second Day + one moving note + sound control**

Successfully rendered a moving note as instructed by Mrs.Chau on the video.
Added the randomSpawn() to randomize the note spawn on 4 lanes.
Added the sound control library SDL_Mixer but having trouble playing mp3/wav/ogg files (all tried).
Added a demo song Songs/yourreality.mp3 (BPM 105).
Don't understand why RAM are used too much as i play music. Finding way to resolve this.

**2020/03/30 - First Day**

Made the project & SDL base of the game.