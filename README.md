John's Quest
(created by John Salame)

This is the game I created for the project of my first semester Computer Science class in college. It is a text-based game with no visuals. Download the Project3 folder and run runner.exe to play the game.

The game follows the adventure of you, the king, as you prepare for the invasion that will happen in your country in two days. The combat is simple (not as complicated as I initially planned to make it) and the game is half skill-based, half luck-based. Some interesting features are the abilities to choose how to ration your time, either by travelling around the map or shopping or sleeping. How you spend your precious 48 hours is up to you.

The tutorial segment of the game lasts until noon of day 1 (based on the in-game clock). During the tutorial, you can quit the game but you cannot save, so make sure you get through the tutorial before you quit.

Any saved data will be added to a save file called save_data.txt. If save_file.txt does not exist, the game will create a fresh file upon running runner.exe. If save_data.txt already exists when you run the game, your progress will be automatically loaded from save_data.txt. If you wish to start over your adventure but keep the save data for another day, change the name of save_data.txt to something else (for example, save1.txt), and rename that file to save_data.txt whenever you want to continue that save.

If you wish to change up your experience (or cheat), you can directly edit the information in the text files for save data, monster info, weapon info, and region info. You can read the Data.cpp, Data.h, and Story.cpp to understand the formats of these text files. With your imagination, you can create new regions with new monsters and new weapons to go with them. Create whatever world you can think of!

You do not need to recomplie the game for modded text files to take effect (you only need to quit the game and run it again). However, if you decide to modify the .cpp files and .h files (to change gameplay mechanics), you need to recompile the program. You can copy and paste the g++ line in bashline.txt into your terminal to do this.
