John's Quest
(created by John Salame)

This game was not created in the Github repository, but I decided to put the finished project here.

This is the game I created for the project of my first semester Computer Science class in college. It is a text-based game with no visuals. Download the Project3 folder and run runner.exe to play the game.

The game follows the adventure of you, the king, as you prepare for the invasion that will happen in your country in two days. The combat is simple (not as complicated as I initially planned to make it) and the game is half skill-based, half luck-based. Some interesting features are the abilities to choose how to ration your time, either by travelling around the map or shopping or sleeping. How you spend your precious 48 hours is up to you.

The tutorial segment of the game lasts until noon of day 1 (based on the in-game clock). During the tutorial, you can quit the game but you cannot save, so make sure you get through the tutorial before you quit.

Upon saving, data will be saved to save_data.txt. If save_data.txt does not exist, the game will create it when you save. The contents of save_file.txt are replaced to reflect your current progress. No backup file is made. If save_data.txt exists when you run the program, your progress will be automatically loaded from save_data.txt; otherwise, the game will start at the introduction. If you wish to have multiple save files or save states, rename the save files you aren't using. While playing, you can make save states by renaming your current save file to something else, then saving. Your save file from the last time you saved should be the one you renamed, and your current save file should be save_data.txt. When starting a new session, choosing which save file to load is simple; before running the game, just rename the save you want to play as save_data.txt, or start fresh by having no files named save_file.txt.

If you wish to change up your experience (or cheat), you can directly edit the information in the text files for save data, monster info, weapon info, and region info. The data is only read from these files upon booting up the game, so you must quit and reenter the game in order to see the changes you made. You can read the Data.cpp, Data.h, and Story.cpp to understand the formats of these text files. With your imagination, you can create new regions with new monsters and new weapons to go with them. Create whatever world you can think of!

You do not need to recomplie the game for modded text files to take effect (you only need to quit the game and run it again). However, if you decide to modify the .cpp files and .h files (to change gameplay mechanics), you need to recompile the program. You can copy and paste the g++ line in bashline.txt into your terminal to do this.


GOOD LUCK AND HAVE FUN!
~JOHN SALAME
