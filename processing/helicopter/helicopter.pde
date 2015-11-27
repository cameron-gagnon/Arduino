final int GRID_SIZE = 20;
int halfScreen;

public static final float GRAVITY = .5;

// Simple scenery definition, can be (must be!) most complex
int[] scenery = new int[200];

int currentPos;
int scrollPos = GRID_SIZE;
GameChar mainChar = new GameChar(width / 2, height / 2, 20, 10, 2); // Character!

void setup()
{
  size(600, 200);

  for (int i = 0; i < scenery.length; i++)
  {
    if (random(1) > 0.85)
    {
      scenery[i] = int(random(height / GRID_SIZE));
    }
  }
  // Half screen in terms of grid size
  halfScreen = currentPos = width / GRID_SIZE / 2;  // 15
}

void draw()
{
  background(255);

  text(currentPos + " -- " + scrollPos, 10, 50);

  for (int i = currentPos - halfScreen, j = 0; i < currentPos + halfScreen; i++, j++)
  {
    if (scenery[i] > 0)
    {
      Obstacle obs = new Obstacle(scrollPos + j * GRID_SIZE, height - scenery[i] * GRID_SIZE, 
        GRID_SIZE, height);
        obs.collision(mainChar);
    }
  }
  mainChar.update();

  scrollPos--;

  //scrollPos %= halfScreen;
  if (scrollPos == 0)
  {
    currentPos++;
    scrollPos = GRID_SIZE;
    if (currentPos == scenery.length - halfScreen)
      exit(); // End
  }
}

class Object {
  int x, y, width_, height_;

  Object(int inX, int inY, int inWidth, int inHeight) {
    x = inX;
    y = inY;
    width_ = inWidth;
    height_ = inHeight;
  }
}
class Obstacle extends Object {

  Obstacle(int inX, int inY, int inWidth, int inHeight) {
    super(inX, inY, inWidth, inHeight);
    fill(#005588);
    rect(x, y, width_, height_);
  }

  boolean collision(GameChar character) {
    if (!((character.widthX() > x) && (character.widthX() < x + width_) ||
      (character.x > x) && (character.x < x)) &&
      ((character.heightY() < y) && (character.heightY() < y + height_) ||
      (character.y > y) && (character.y < y))) {
      textSize(32);
      text("COLLISION", 15, 60); 
      return true;
    }
    return false;
  }
} 

class GameChar extends Object {
  float yVel;

  GameChar(int inX, int inY, int inWidth, int inHeight, float inYVel) {
    super(inX, inY, inWidth, inHeight);
    yVel = inYVel;
  }

  int widthX() {
    return x + width_;
  }

  int heightY() {
    return y + height_;
  }

  void update() {
    fill(#AA8800);
    ellipse(x, y, width_, height_);
    x = width / 2;
    
    if (keyCode == UP){
      yVel += .25;
      y -= .25;
    } else {
      yVel -= GRAVITY;
      y += yVel;
    }
  }
}