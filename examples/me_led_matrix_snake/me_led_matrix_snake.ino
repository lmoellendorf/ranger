#include "MeAuriga.h"

#define MATRIX_WIDTH 16
#define MATRIX_HEIGHT 8

enum direction {
  UP = KEY_1,
  DOWN = KEY_3,
  LEFT = KEY_4,
  RIGHT = KEY_2,
};

enum states {
  MOVE,
  GROW,
  CRASH,
};

const int max_body_len = MATRIX_HEIGHT * MATRIX_WIDTH;

struct pixel {
  int x;
  int y;
};

struct snake {
  struct pixel body[max_body_len];
  size_t len = 0;
};

Me4Button button = Me4Button(PORT_9);
MeLEDMatrix matrix = MeLEDMatrix(PORT_10);

struct pixel orb = {
  .x = -1,
  .y = -1,
};

struct snake snake;
uint8_t dir = UP;
uint8_t bitmap[MATRIX_WIDTH] = { 0 };
int state = MOVE;

void setPixel(int x, int y, size_t len, uint8_t bitmap[]) {
  if (!bitmap
      || x >= len
      || x < 0
      || y >= MATRIX_HEIGHT
      || y < 0)
    return;
  bitmap[x] |= 1 << y;
}

void resetSnake(void) {
  snake.body[0].x = MATRIX_WIDTH / 2;
  snake.body[0].y = MATRIX_HEIGHT / 2;
  snake.len = 1;
}

void gameOver(size_t len, uint8_t bitmap[]) {
  for (int i = 0; i < 7; i++) {
    matrix.setColorIndex(0);
    matrix.drawBitmap(0, 0, MATRIX_WIDTH, bitmap);
    delay(300);
    matrix.setColorIndex(1);
    matrix.drawBitmap(0, 0, MATRIX_WIDTH, bitmap);
    delay(300);
  }
  resetSnake();
}

void score(size_t len, uint8_t bitmap[]) {
  for (int i = Brightness_8; i >= 0; i--) {
    matrix.setBrightness(i);
    matrix.drawBitmap(0, 0, MATRIX_WIDTH, bitmap);
    delay(60);
  }
  for (int i = 0; i < Brightness_8; i++) {
    matrix.setBrightness(i);
    matrix.drawBitmap(0, 0, MATRIX_WIDTH, bitmap);
    delay(60);
  }
}

void printOrb() {
  Serial.print("Orb: ");
  Serial.print(orb.x);
  Serial.print(":");
  Serial.println(orb.y);
}

void printSnakeBody(int x, int y) {
  Serial.print("Snake: ");
  Serial.print(x);
  Serial.print(":");
  Serial.println(y);
}


void moveSnake() {
  /* move (only the old part of) the snake body into the latest direction */
  for (int i = snake.len - 1; i > 0; i--) {
    snake.body[i].x = snake.body[i - 1].x;
    snake.body[i].y = snake.body[i - 1].y;
  }
  switch (dir) {
    case UP:
      Serial.println("UP");
      snake.body[0].y++;
      break;
    case DOWN:
      Serial.println("DOWN");
      snake.body[0].y--;
      break;
    case RIGHT:
      Serial.println("RIGHT");
      snake.body[0].x++;
      break;
    case LEFT:
      Serial.println("LEFT");
      snake.body[0].x--;
      break;
    default:
      Serial.println("INVALID");
      break;
  }
}

bool isCollision() {
  /* detect collision with border */
  if (snake.body[0].x < 0
      || snake.body[0].x > 15
      || snake.body[0].y < 0
      || snake.body[0].y > 7) {
    Serial.println("Snake hit border!");
    return true;
  }
  /* detect collision with snake */
  for (int i = 1; i < snake.len; i++) {
    if (snake.body[0].x == snake.body[i].x
        && snake.body[0].y == snake.body[i].y) {
      Serial.println("Snake hit itself!");
      return true;
    }
  }
  return false;
}

bool reachedOrb() {
  /* snake head reaches the orb */
  if (snake.body[0].x == orb.x && snake.body[0].y == orb.y) {
    return true;
  }
  return false;
}

void growSnake() {
  bool orb_placed = false;

  score(MATRIX_WIDTH, bitmap);
  Serial.print("Snake ate ");
  printOrb();
  /* append a copy of the last element to the body */
  snake.body[snake.len].x = snake.body[snake.len - 1].x;
  snake.body[snake.len].y = snake.body[snake.len - 1].y;
  snake.len++;
  if (snake.len >= max_body_len) {
    /* maximum length - reset game! */
    score(MATRIX_WIDTH, bitmap);
    resetSnake();
  }
  Serial.print("Snake length: ");
  Serial.println(snake.len);
  /* add a new orb */
  while (!orb_placed) {
    orb.x = random(0, MATRIX_WIDTH);
    orb.y = random(0, MATRIX_HEIGHT);
    orb_placed = true;
    /* check if the orb is below the snake */
    for (int i = 0; i < snake.len; i++) {
      if (snake.body[i].x == orb.x && snake.body[i].y == orb.y)
        orb_placed = false;
    }
  }
  Serial.print("New ");
  printOrb();
}

void drawMatrix() {
  memset(bitmap, 0, MATRIX_WIDTH);
  /* draw orb */
  setPixel(orb.x, orb.y, MATRIX_WIDTH, bitmap);
  /* draw snake */
  for (int i = 0; i < snake.len; i++) {
    setPixel(snake.body[i].x, snake.body[i].y, MATRIX_WIDTH, bitmap);
    printSnakeBody(snake.body[i].x, snake.body[i].y);
  }
  matrix.drawBitmap(0, 0, MATRIX_WIDTH, bitmap);
}

void setup() {
  resetSnake();
  orb.x = random(0, MATRIX_WIDTH);
  orb.y = random(0, MATRIX_HEIGHT);
  Serial.begin(9600);
}

void loop() {
  /* remember the current snake length */
  uint8_t key_pressed;

  key_pressed = button.pressed();
  switch (key_pressed) {
    case UP:
    case DOWN:
    case RIGHT:
    case LEFT:
      dir = key_pressed;
  }

  if (!(millis() % 600)) {
    printOrb();
    drawMatrix();
    switch (state) {
      case MOVE:
        moveSnake();
        if (isCollision())
          state = CRASH;
        else if (reachedOrb())
          state = GROW;
        break;

      case GROW:
        growSnake();
        state = MOVE;
        break;

      case CRASH:
        gameOver(MATRIX_WIDTH, bitmap);
        state = MOVE;
        break;
    }
  }
}
