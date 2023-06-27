# Jetpack Joyride

# Student details:
    Shahar Hevrony - 209180967
    Lior Yakobovich - 207258625
    Aviv Erez - //FIX

# General explanations:
    In this project we will realize the game "". In this game we meet Berry, who breaks into a secret laboratory. 
    The goal of the game is to help Barry collect as much money as possible and avoid various obstacles along the way. 
    Berry can also collect special powers that help him survive the maze.

# Files:
    - Events: 
        - Event: Receives a situation and activates the desired response to that situation.
        - EventQueue: A queue manager of different events that happened in a certain sequence.

    - Managers:
        - AudioManager: Manages the sound buttons of the settings.
        - Exeption: Manages the exceptions in the program and sending the appropriate message.
        - GameManager: Manages game details such as maximum score, audio volume and avatars purchased by the player.
        - PlayerStateManager: Manages the different types of players such as regular, super or dead and adjusts the duration
                              of the game according to each type.
        - ResourcesManager: Manages the loading of the various image and audio files.
        - Values: Responsible for project data such as strings, numbers, and enums.

    - Menu:
        - Help: Manages the "help" of the project called by the "Controller".
        - Settings:Manages the "settings" of the project called by the "Controller". Allows you to adjust the volume of the music 
                   and sounds and also shows a table of the 5 best. Remembers these settings even after closing the program.
        - Shop: Responsible for the "shop" of the projectcalled by the "Controller". As long as the program runs, you can 
                accumulate money in different games and thus purchase different avatars and change the character. A purchased 
                character belongs to the user and you can switch between characters until the program is closed.

    - Objects:
        - Box2Objects:
            - Bound: Defines the boundaries of the board - floor and ceiling. Inherits from "Box2Object".
            - Box2Object: Defines a generic object that inherits from "Object" and uses Box2D. Abstract class.
            - Coin: Defines a coin, can be both static and dynamic, depending on the received definitions. Inherits from "Box2Object".
            - Player: Defines an player, which has a "regular" deductive state but can be changed and managed by "PlayerStateManager". 
                      Inherits from "Box2Object".
        - Beam: Defines the middle part between two lasers by the angle and distance between the lasers connecting it. Inherits from "Object".
        - Laser: Defines a laser, each laser depends on its partner in order to define an angle between them and create the beam connecting
                 them. Inherits from "Object".
        - Missile: Defines a missile, which at a certain range tracks the player's position, then settles and then flies at a speed higher than 
                   the displacement set on the board. Inherits from "Object".
        - NonCollisionObject: Defines general objects that do not collide with the player such as the jetpack's flame, the lights of the 
                              corridors and the scientists walking around there. The definition of these objects is in the same file. 
                              Inherits from "Object".
        - Object: Defines a general object that is run in the game. Abstract class.
        - Piggy: Defines a pig, when colliding with the player it drops a number of coins to the floor with a dynamic displacement. 
                 Inherits from "Object".
        - SuperPower: Defines the superpower box, by taking this box the player gets different superpowers each time. Inherits from "Object".

    - PlayGame:
        - Animation: Defines the animation of the various objects in the game and moves the character as needed.
        - Board: Defines the rate of movement of the board, background and non-colliding characters. In addition, reads from a series of 
                 files different maps for arranging the objects and saves each map separately. When necessary, randomly selects a map and 
                 transfers it to the game management.
        - GameSettings: Defines the settings of the game itself, such as resume, retry or quit.
        - PlayGame: Manages the duration of the entire game, creates the objects, manages collisions and deletions and creates maps as needed.
        - ScordBoard: Sets the scoreboard of the game, counting the time elapsed since the start of the round, the number of money earned in 
                      this round and the best score earned in the past.

    - Controller: Manages the main screen and defines "PlayGame", "Shop", "Settings" and "Help" buttons.

    - Main: Runs the game with the controller.

# Data structures:
     EventQueue:
          - A "queue" that keeps a number of situations that have happened and need to be responded to.

     GameManager:
          - A boolean array to keep track of purchased avatars.

     Values: 
          - A number of "enum" to give names to numbered stuff.
          - A number of vectors of "String" to save names.

     Beam: 
          - A vector of CircleShape, to creates circles along the beam. Define the most accurate collision with the beam despite the rotation.

     Laser:
          - A CircleShape, to creates a circle in the laser. Define the most accurate collision with the laser despite the rotation.

     PlayGame:
          - A number of "unique_ptr" type vectors for managing objects on the screen
          - A "shared_ptr" type pointer to the player, that is used in "PlayGame" and also "PlayerStateManager".

# Algorithms
     - We would like to make sure that we always have two lasers that "see" each other in order to calculate an angle between
       them and the connecting beam. Therefore, define a vector of even lasers, and we will create a beam and a print each time we insert 
       an even-numbered member into this array.
     - When we rotate an image to a certain angle, the collision with it is distorted. Therefore for all the parts of the laser we will want 
       to create circles and check for collision with them instead of with the object itself. For the beam - we will want to create a vector 
       of circles, where the distance between each circle is smaller than the player himself, so that he cannot accidentally pass between the
       circles. The position of the balls is calculated by an the calculation of the hypotenuse in a right triangle.

# Design:
     The program contains objects used by the player during the game and other objects around.
          - The main screen contains buttons to enter the game, help menu, shop for avaters and the game's settings.
          - The game itself have an obctacle to avoid and awards to collect throw the maze.
          - The shop offers a number of avatars that the player can change to by collecting maony in the game. Every avatar that been perchesed
            can be use throw the games, even after changing to a new avatar. After closing the program the collected maony and the perchesed 
            avatars will reset for the next game.
          - The settings offers the player the opthion to set the volum of the sound or the music in the game. The user can also check the 
            top-five scorces in privies games. The settings are saved every time they change and will be defined in the next game in the 
            same way the user set them in previous games.
          - The help screen explains to the player the way and purpose of the game and the various options offered by the program.

# Known bugs: 
     none at this point.

# Other remarks: 
     none