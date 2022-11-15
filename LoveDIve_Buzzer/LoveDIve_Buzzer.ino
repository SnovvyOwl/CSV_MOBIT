/*
LOVE_DIVE
IVE
*/

#include "pitches.h"

// notes in the melody:
int melody[] = {
  0,
  0,0,NOTE_FS4,
  NOTE_GS4,0,
  0,0,NOTE_B3,
  0,NOTE_GS3,NOTE_E4,NOTE_DS4,NOTE_E4,NOTE_DS4,NOTE_CS4,
  NOTE_C4,NOTE_AS3,NOTE_C4,NOTE_AS3,NOTE_C4,NOTE_AS3,NOTE_GS3,NOTE_FS3,
  0,NOTE_GS3,NOTE_E4,NOTE_DS4,NOTE_E4,NOTE_DS4,NOTE_CS4,
  NOTE_C4,NOTE_AS3,NOTE_C4,NOTE_AS3,NOTE_C4,NOTE_AS3,NOTE_GS3,NOTE_FS3,
  0,NOTE_E4,NOTE_E4,NOTE_E4,NOTE_FS4,NOTE_GS4,
  NOTE_FS4,NOTE_FS4,NOTE_FS4,NOTE_E4,NOTE_A4,NOTE_GS4,NOTE_FS4,
  0,NOTE_E4,NOTE_DS4,NOTE_E4,NOTE_DS4,NOTE_CS4,
  NOTE_C4,NOTE_AS3,NOTE_C4,NOTE_AS3,NOTE_C4,NOTE_AS3,NOTE_GS3,
  0,NOTE_GS4,NOTE_FS4,NOTE_B4,
  NOTE_GS4,NOTE_FS4,NOTE_FS4,NOTE_FS4,NOTE_FS4,NOTE_E4,NOTE_FS4,
  NOTE_FS4,NOTE_GS4,NOTE_FS4,NOTE_B4,NOTE_GS4,NOTE_FS4,NOTE_FS4,NOTE_FS4,NOTE_E4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  1, //1
  2,4,4,//3
  2,2,//2
  2,4,4,//3
  8,8,8,8,8,8,4,//7
  8,8,8,8,8,8,8,8,//8
  8,8,8,8,8,8,4,//7
  8,8,8,8,8,8,8,8,//8
  4,8,8,8,8,4, //6
  8,8,8,8,8,8,4,//7
  4,8,8,8,8,4,//6
  8,8,8,8,8,8,4,//7
  4,4,4,4,//4
  2,12,12,12,12,12,12, //7
  4,4,4,4,//4
  2,8,16,16,8,8//6
};

void setup() {

  // iterate over the notes of the melody:

  for (int thisNote = 0; thisNote < 86; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.

    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = 1000 / noteDurations[thisNote];

    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.

    // the note's duration + 30% seems to work well:

    int pauseBetweenNotes = noteDuration * 1.30;

    delay(pauseBetweenNotes);

    // stop the tone playing:

    noTone(8);

  }
}

void loop() {

  // no need to repeat the melody.
}