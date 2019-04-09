Graphics Project
=========================

Directory structure

Zelda-Game
      |
      ---CMakeLists.txt
      ---README.md
      ---src
           |
           ---all code containing files
      ---resources	

- Running the code
    --mkdir build
    --cd mkdir
    --cmake ..
    --make
    --./graphics_assign1
- CONTROLS
     Up arrow        ->  move forward
     Down arrow      ->  move backward
     SPACE           ->  jump
     Left arrow      ->  rotate left
     Right arrow     ->  rotate right 
     F               -> bullet shhot
     z,m             ->cannon moment
     1 ->topview
     2 ->boat front view
     3  -> tower view
     4  ->boat follow view(Default)
     5  -> helicopter view(a,s,d,w for movement)  
     B ->Boost
-Game play
    --Boat killing monsters gets points(20)
    --Killing 3 monsters gets big boss(30)
    --To kill big boss shoot 5 bullets
    --Coin gives boosters.
    -- hitting rocks -ve health
    -- gifts  +ve health
    -- hitting monster respawn.

Resourses file has sound files.
    



