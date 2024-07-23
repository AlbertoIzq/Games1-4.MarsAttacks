# Games1-4.MarsAttacks
Mars Attacks game with a swear words touch

Check "Screenshots" folder to see how the game works
Check "Text Invaders" folder for installation package

_BUGS LIST_

- 2020/01/10 Alien swarm movement
When alien swarm movement touches right side, it inmediately goes down without waiting "movement timer" time.
Error occurs in "void updateAlienSwarmMovement" in "move downwards" if. "move_horizontal" is false but the whole if evaluates to true and therebefore, it moves down inmediately without waiting "movement timer" time.


_TO DO_

Game class: Add pause mode
