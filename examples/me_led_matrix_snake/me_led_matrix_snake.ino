#include "MeAuriga.h"

#define KEY_UP KEY_1
#define KEY_LEFT KEY_4
#define KEY_RIGHT KEY_2
#define KEY_DOWN KEY_3
#define MATRIX_WIDTH 16
#define MATRIX_HEIGHT 8

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
uint8_t dir = KEY_UP;
uint8_t bitmap[MATRIX_WIDTH] = { 0 };

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

void setup() {
  resetSnake();
  orb.x = random(0, MATRIX_WIDTH);
  orb.y = random(0, MATRIX_HEIGHT);
  Serial.begin(9600);
}

void loop() {
  /* remember the current snake length */
  int snake_len;
  uint8_t key_pressed = button.pressed();
  bool orb_placed = false;

  if (!(millis() % 600)) {
    snake_len = snake.len;
    /* if the snake head reaches the orb */
    if (snake.body[0].x == orb.x && snake.body[0].y == orb.y) {
      score(MATRIX_WIDTH, bitmap);
      Serial.print("Snake ate orb: ");
      Serial.print(orb.x);
      Serial.print(":");
      Serial.println(orb.y);
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
      Serial.print("New orb: ");
      Serial.print(orb.x);
      Serial.print(":");
      Serial.println(orb.y);
    }

    switch (key_pressed) {
      case KEY_UP:
      case KEY_DOWN:
      case KEY_RIGHT:
      case KEY_LEFT:
        dir = key_pressed;
    }

    /* move (only the old part of) the snake body into the latest direction */
    for (int i = snake_len - 1; i > 0; i--) {
      snake.body[i].x = snake.body[i - 1].x;
      snake.body[i].y = snake.body[i - 1].y;
    }
    switch (dir) {
      case KEY_UP:
        Serial.println("UP");
        snake.body[0].y++;
        break;
      case KEY_DOWN:
        Serial.println("DOWN");
        snake.body[0].y--;
        break;
      case KEY_RIGHT:
        Serial.println("RIGHT");
        snake.body[0].x++;
        break;
      case KEY_LEFT:
        Serial.println("LEFT");
        snake.body[0].x--;
        break;
      default:
        Serial.println("INVALID");
        break;
    }
    Serial.print("Orb: ");
    Serial.print(orb.x);
    Serial.print(":");
    Serial.println(orb.y);
    memset(bitmap, 0, MATRIX_WIDTH);
    /* draw orb */
    setPixel(orb.x, orb.y, MATRIX_WIDTH, bitmap);
    /* draw snake */
    for (int i = 0; i < snake.len; i++) {
      setPixel(snake.body[i].x, snake.body[i].y, MATRIX_WIDTH, bitmap);
      Serial.print("Snake: ");
      Serial.print(snake.body[i].x);
      Serial.print(":");
      Serial.println(snake.body[i].y);
    }
    /* detect collision with border */
    if (snake.body[0].x < 0
        || snake.body[0].x > 15
        || snake.body[0].y < 0
        || snake.body[0].y > 7) {
      gameOver(MATRIX_WIDTH, bitmap);
      Serial.println("Snake hit border!");
    }
    /* detect collision with snake */
    for (int i = 1; i < snake.len; i++) {
      if (snake.body[0].x == snake.body[i].x
          && snake.body[0].y == snake.body[i].y) {
        gameOver(MATRIX_WIDTH, bitmap);
        Serial.println("Snake hit itself!");
      }
    }
    matrix.drawBitmap(0, 0, MATRIX_WIDTH, bitmap);
  }
}
