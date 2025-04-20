# pong game
This is a simple pong game created in cpp. It's built using the raylib library and it is my first use of a .bat file to help compile the code.


## mechanics
This game slowly gets faster over time until someone scores. The way that that mechanism works is that every frame it counts up on the clock and once it gets to a set number it increases the ball's velocity. Once the ball scores it resets the clock and the speed of the ball. it also resets the position of the ball.


## blocker movement
One blocker is controlled by the player using the up and down arrow keys. the opposing blocker is controlled by the computer the computer has different modes


### how we know which mode to use
The mode we use is determined by the score of the game which means that the farther ahead you are the harder it gets to score. This makes the game very progressive and prevents the player from getting too big of a lead in the game.


### mode one
In the first mode the computer just tries to match the y position of the blocker with that of the ball. however this can be beaten by just hitting the ball with sufficient angle.


### mode two
In the second mode the computer tries to hit the ball so that it doesn't have any y velocity to do this it calculates where on the paddle to hit the ball and then tries to match the y position of that point with the y position of the ball. This is harder to beat because it is harder to build up y velocity to beat the computer.


### mode three
In the third mode the computer predicts the final position of the ball when it gets to the side. This is achieved by finding out how many frames until it hits the wall and then multiplying that by the y velocity to find out the final y position. if the y position is less then 0 or greater then the height of the window it accounts for the bounce off of the wall and then it moves to that position.


### mode four
This mode is a combination of the second and third modes it predicts where it needs to be to give the ball a velocity of zero and then goes there this mode is the hardest to beat.



