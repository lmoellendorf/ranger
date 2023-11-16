/**
 * In this example the "Position state" value of the Makeblock RGB Line
 * Follower is used to calculate the width of a line e.g. to detect crossings.
 *
 * Bit operators are used to count the number of Bits set in Position state.
 *
 * In a loop for each Bit in Position state a Bit mask is created using a Bit
 * shift operation:
 *
 * 1 << n
 *
 * For 1 << 0 the Bit mask is:
 *
 * +---+---+---+---+---+---+---+---+
 * | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |
 * +---+---+---+---+---+---+---+---+
 *
 * For 1 << 1 the Bit mask is:
 *
 * +---+---+---+---+---+---+---+---+
 * | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 |
 * +---+---+---+---+---+---+---+---+
 *
 * ...
 *
 * For 1 << 3 the Bit mask is:
 *
 * +---+---+---+---+---+---+---+---+
 * | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 |
 * +---+---+---+---+---+---+---+---+
 *
 * These 4 Bitmasks are each compared with the value of Position state using a
 * bitwise AND operation (position & bitmask).
 *
 * This operation performs a logical AND operation on each pair of the
 * corresponding bits. If both Bits in a compared position are 1, the Bit in
 * the result of this operation is 1. If at least one of the Bits is 0, the Bit
 * in the result will be 0.
 *
 * Given a Position state with 2nd, 3rd and 4th Bit set:
 *
 * +---+---+---+---+---+---+---+---+
 * | 0 | 0 | 0 | 0 | 1 | 1 | 1 | 0 | Position state
 * +---+---+---+---+---+---+---+---+
 *                                   bitwise AND
 * +---+---+---+---+---+---+---+---+
 * | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | (1 << 0) -> 0
 * +---+---+---+---+---+---+---+---+
 * +---+---+---+---+---+---+---+---+
 * | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | (1 << 1) -> 1
 * +---+---+---+---+---+---+---+---+
 * +---+---+---+---+---+---+---+---+
 * | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | (1 << 2) -> 1
 * +---+---+---+---+---+---+---+---+
 * +---+---+---+---+---+---+---+---+
 * | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | (1 << 3) -> 1
 * +---+---+---+---+---+---+---+---+
 *
 * Each time the result of the bitwise AND operation is greater 0 the Bit is
 * counted. In the above example the counted number is 3.
 *
 * A crossing may be detected if the number Bits is significantly greater than
 * the number of sensors covered by the line. Note, that the number of sensors
 * covered by the line is also greater if the Line Leader is at an angle to the
 * line.
 */
#include <MeAuriga.h>
#include "MeRGBLineFollower.h"

MeRGBLineFollower linefollower = MeRGBLineFollower(PORT_6, ADDRESS2);

void setup() {
  linefollower.begin();
  Serial.begin(9600);
}

void loop() {
  uint8_t position, bitmask, counter = 0;

  linefollower.loop();

  position = linefollower.getPositionState();

  /* line follower hase 4 sensors to check */
  for (int n = 0; n < 4; n++) {
    /* shift a Bit by n places to the left */
    bitmask = 1 << n;

    /* perform a logical AND operation on each Bit */
    if ((position & bitmask) > 0) {
      /* if the n-th Bit in position is set, increment counter by one */
      counter++;
    }
  }

  Serial.print("Position state: ");
  Serial.println(position, BIN);
  Serial.print("Line width: ");
  Serial.println(counter);

  /**
   * if the line normally covers 1 sensor, a counter of 3 or greater is most
   * likely indicating a crossing
   */
  if (counter > 2) {
    Serial.println("Looks like a crossing!");
  }
}
