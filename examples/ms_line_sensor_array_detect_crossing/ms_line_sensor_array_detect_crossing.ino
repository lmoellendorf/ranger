/**
 * In this example the "Result" value of the Mindsensors Line Sensor Array is
 * used to calculate the width of a line e.g. to detect crossings.
 *
 * Bit operators are used to count the number of Bits set in Result.
 *
 * In a loop for each Bit in Result a Bit mask is created using a Bit shift
 * operation:
 *
 * 1 << n
 *
 * For 1 << 0 the Bit mask is:
 *
 * +---+---+---+---+---+---+---+---+
 * | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 |
 * +---+---+---+---+---+---+---+---+
 *
 * For 1 << 3 the Bit mask is:
 *
 * +---+---+---+---+---+---+---+---+
 * | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 |
 * +---+---+---+---+---+---+---+---+
 *
 * For 1 << 7 the Bit mask is:
 *
 * +---+---+---+---+---+---+---+---+
 * | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
 * +---+---+---+---+---+---+---+---+
 *
 * These 8 Bitmasks are each compared with the value of Result using a bitwise
 * AND operation (result & bitmask).
 *
 * This operation performs a logical AND operation on each pair of the
 * corresponding bits. If both Bits in a compared position are 1, the Bit in
 * the result of this operation is 1. If at least one of the Bits is 0, the Bit
 * in the result will be 0.
 *
 * Given a Result with 4th, 5th and 6th Bit set:
 *
 * +---+---+---+---+---+---+---+---+
 * | 0 | 0 | 0 | 1 | 1 | 1 | 0 | 0 | Result
 * +---+---+---+---+---+---+---+---+
 *                                   bitwise AND
 * +---+---+---+---+---+---+---+---+
 * | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 1 | (1 << 0) -> 0
 * +---+---+---+---+---+---+---+---+
 * +---+---+---+---+---+---+---+---+
 * | 0 | 0 | 0 | 0 | 0 | 0 | 1 | 0 | (1 << 1) -> 0
 * +---+---+---+---+---+---+---+---+
 * +---+---+---+---+---+---+---+---+
 * | 0 | 0 | 0 | 0 | 0 | 1 | 0 | 0 | (1 << 2) -> 1
 * +---+---+---+---+---+---+---+---+
 * +---+---+---+---+---+---+---+---+
 * | 0 | 0 | 0 | 0 | 1 | 0 | 0 | 0 | (1 << 3) -> 1
 * +---+---+---+---+---+---+---+---+
 * +---+---+---+---+---+---+---+---+
 * | 0 | 0 | 0 | 1 | 0 | 0 | 0 | 0 | (1 << 4) -> 1
 * +---+---+---+---+---+---+---+---+
 * +---+---+---+---+---+---+---+---+
 * | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | (1 << 5) -> 0
 * +---+---+---+---+---+---+---+---+
 * +---+---+---+---+---+---+---+---+
 * | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | (1 << 6) -> 0
 * +---+---+---+---+---+---+---+---+
 * +---+---+---+---+---+---+---+---+
 * | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | (1 << 7) -> 0
 * +---+---+---+---+---+---+---+---+
 *
 * Each time the result of the bitwise AND operation is greater 0 the Bit is
 * counted. In the above example the counted number is 3.
 *
 * A crossing may be detected if the number Bits is significantly greater than
 * the number of sensors covered by the line. Note, that the number of sensors
 * covered by the line is also greater if the Line Sensor is at an angle to the
 * line.
 */
#include <MeAuriga.h>
#include <LmMsLineSensorArray.h>

MsLineSensorArray lsa = MsLineSensorArray();

void setup() {
  Serial.begin(9600);
}

void loop() {
  int result, bitmask, counter = 0;

  result = lsa.getResult();

  for (int n = 0; n < 8; n++) {
    /* shift a Bit by n places to the left */
    bitmask = 1 << n;

    /* perform a logical AND operation on each Bit */
    if ((result & bitmask) > 0) {
      /* if the n-th Bit in result is set, increment counter by one */
      counter++;
    }
  }

  Serial.print("Line width: ");
  Serial.println(counter);

  /**
   * if the line normally covers 2 sensors, a counter of 5 or greater is most
   * likely indicating a crossing
   */
  if (counter > 4) {
    Serial.println("Looks like a crossing!");
  }
}
