//
//  note127abc.c
//   Note127abc
//
//  created by phyl on 1/12/2020
//
//
#include <stdio.h>
#include "m_pd.h"

static t_class *note127abc_class;

typedef struct _note127abc {
  t_object    x_obj;
  t_int       midi_nvalue;
  t_outlet    *out_letterName;
} t_note127abc;

void note127abc_setMidiValue(t_note127abc *x, t_floatarg f1){
  x->midi_nvalue = (f1 <= 0) ? 0 : f1;
}

void note127abc_onFloatIn(t_note127abc *x, t_floatarg f1)
{
  note127abc_setMidiValue(x,f1);

  int midi_nvalue  = x->midi_nvalue;
  int pitchClass = midi_nvalue % 12;
  int octavNum = (midi_nvalue / 12)-1;

  char noteLetter;
  char accidental;

  switch(pitchClass){
    case 0: noteLetter= 'C'; accidental = ' ';break;
    case 1: noteLetter= 'C'; accidental = '#';break;
    case 2: noteLetter= 'D'; accidental = ' ';break;
    case 3: noteLetter= 'D'; accidental = '#';break;
    case 4: noteLetter= 'E'; accidental = ' ';break;
    case 5: noteLetter= 'F'; accidental = ' ';break;
    case 6: noteLetter= 'F'; accidental = '#';break;
    case 7: noteLetter= 'G'; accidental = ' ';break;
    case 8: noteLetter= 'G'; accidental = '#';break;
    case 9: noteLetter= 'A'; accidental = ' ';break;
    case 10:noteLetter= 'A'; accidental = '#';break;
    case 11:noteLetter= 'B'; accidental = ' ';break;
    default: noteLetter= '?'; accidental = '?';break;
  }

  char bufr[50];
  sprintf(bufr,"%c%c%d",noteLetter,accidental, octavNum);

  outlet_symbol(x->out_letterName, gensym(bufr));
}

void *note127abc_new(t_floatarg f1)
{
  t_note127abc *x = (t_note127abc *)pd_new(note127abc_class);

  note127abc_setMidiValue(x,f1);

  x->out_letterName = outlet_new(&x->x_obj, &s_symbol);
  return (void *)x;
}

void note127abc_free(t_note127abc *x){
    outlet_free(x->out_letterName);
}

void note127abc_setup(void) {
  note127abc_class = class_new(gensym("note127abc"),
        (t_newmethod)note127abc_new,
        (t_method)note127abc_free,
        sizeof(t_note127abc),
        CLASS_DEFAULT,
        A_DEFFLOAT,
        0);

  class_addfloat(note127abc_class, (t_method)note127abc_onFloatIn);
}
