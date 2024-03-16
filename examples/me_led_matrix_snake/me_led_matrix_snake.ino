#include "MeAuriga.h"

#define MATRIX_WIDTH 16
#define MATRIX_HEIGHT 8

enum direction {
  UP = KEY_1,
  DOWN = KEY_3,
  LEFT = KEY_4,
  RIGHT = KEY_2,
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

struct pixel orb;
struct snake snake;
uint8_t bitmap[MATRIX_WIDTH] = { 0 };
uint8_t dir = UP;
int crash_counter = 0;
int brightness = Brightness_8;
bool score = false;

bool setPixel(int x, int y, size_t len, uint8_t bitmap[]) {
  if (!bitmap
      || x >= len
      || x < 0
      || y >= MATRIX_HEIGHT
      || y < 0)
    return false;
  bitmap[x] |= 1 << y;
  return true;
}

void resetSnake(void) {
  snake.body[0].x = MATRIX_WIDTH / 2;
  snake.body[0].y = MATRIX_HEIGHT / 2;
  snake.len = 1;
}

void newOrb() {
  /* check if there is room for orb */
  if (snake.len >= max_body_len) {
    resetSnake();
  }

  do {
    /* add a new orb */
    orb.x = random(0, MATRIX_WIDTH);
    orb.y = random(0, MATRIX_HEIGHT);
    /* check if the orb is below the snake */
  } while (bitmap[orb.x] & (1 << orb.y));
}

void moveSnake() {
  struct pixel head, tail;

  head.x = snake.body[0].x;
  head.y = snake.body[0].y;
  tail.x = snake.body[snake.len - 1].x;
  tail.y = snake.body[snake.len - 1].y;

  switch (dir) {
    case UP:
      head.y++;
      break;
    case DOWN:
      head.y--;
      break;
    case RIGHT:
      head.x++;
      break;
    case LEFT:
      head.x--;
      break;
    default:
      break;
  }

  /* move the snake body */
  for (int i = snake.len - 1; i > 0; i--) {
    snake.body[i].x = snake.body[i - 1].x;
    snake.body[i].y = snake.body[i - 1].y;
    /* draw snake body */
    setPixel(snake.body[i].x, snake.body[i].y, MATRIX_WIDTH, bitmap);
    /* check if head hits the body */
    if (head.x == snake.body[i].x && head.y == snake.body[i].y) {
      crash_counter = 7;
    }
  }

  /* snake head reaches the orb */
  if (head.x == orb.x && head.y == orb.y) {
    /* append a copy of tail to the body */
    snake.body[snake.len].x = tail.x;
    snake.body[snake.len].y = tail.y;
    snake.len++;
    score = true;
    /* draw new snake tail */
    setPixel(tail.x, tail.y, MATRIX_WIDTH, bitmap);
    newOrb();
  }

  /* draw snake head */
  if (!setPixel(head.x, head.y, MATRIX_WIDTH, bitmap)) {
    /* head hit border */
    crash_counter = 7;
  }
  snake.body[0].x = head.x;
  snake.body[0].y = head.y;
}

void setup() {
  resetSnake();
  newOrb();
  matrix.setBrightness(Brightness_8);
}

void loop() {
  uint8_t key_pressed;

  key_pressed = button.pressed();
  switch (key_pressed) {
    case UP:
      if (dir != DOWN) {
        dir = key_pressed;
      }
      break;
    case DOWN:
      if (dir != UP) {
        dir = key_pressed;
      }
      break;
    case RIGHT:
      if (dir != LEFT) {
        dir = key_pressed;
      }
      break;
    case LEFT:
      if (dir != RIGHT) {
        dir = key_pressed;
      }
      break;
  }

  if (crash_counter > 0) {
    if (!(millis() % 300)) {
      matrix.setColorIndex(crash_counter % 2);
      matrix.drawBitmap(0, 0, MATRIX_WIDTH, bitmap);
      crash_counter--;
      if (!crash_counter) {
        matrix.setColorIndex(true);
        resetSnake();
      }
    }
    return;
  }

  if (!(millis() % 60)) {
    if (score) {
      matrix.setBrightness(--brightness);
      matrix.drawBitmap(0, 0, MATRIX_WIDTH, bitmap);
      if (brightness <= 0) {
        score = false;
      }
    } else if (brightness < Brightness_8) {
      matrix.setBrightness(++brightness);
      matrix.drawBitmap(0, 0, MATRIX_WIDTH, bitmap);
    }
  }

  if (!(millis() % 600)) {
    /* clear bitmap */
    memset(bitmap, 0, MATRIX_WIDTH);
    /* draw orb */
    setPixel(orb.x, orb.y, MATRIX_WIDTH, bitmap);
    moveSnake();
    matrix.drawBitmap(0, 0, MATRIX_WIDTH, bitmap);
  }
}
