# Games1-4.MarsAttacks
Mars Attacks game with a swear words touch

_____BUGS LIST_____

-2020/01/10 Alien swarm movement
When alien swarm movement touches right side, it inmediately goes down without waiting "movement timer" time.
Error occurs in "void updateAlienSwarmMovement" in "move downwards" if. "move_horizontal" is false but the whole if evaluates to true and therebefore, it moves down inmediately without waiting "movement timer" time.

Bombs collide with shield going through it completely


_____TO REVIEW_____

-2020/01/10 Bomb shooting
It may happen that the same alien shoots more than one bomb at once due to rand()