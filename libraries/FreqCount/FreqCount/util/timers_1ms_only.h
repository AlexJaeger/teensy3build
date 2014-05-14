#ifndef FreqCount_timers_h_
#define FreqCount_timers_h_

#include <avr/io.h>
#include <avr/interrupt.h>

// Arduino Mega
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  // #define COUNTER_USE_TIMER1 // T1 is not connected
  // #define COUNTER_USE_TIMER3 // T3 is not connected
  // #define COUNTER_USE_TIMER4 // T4 is not connected
  #define COUNTER_USE_TIMER5    // T5 is pin 47
  #define TIMER_USE_TIMER2

// Teensy 2.0
#elif defined(__AVR_ATmega32U4__)
  #define COUNTER_USE_TIMER1    // T1 is pin 11  (has LED connected)
  #define TIMER_USE_TIMER4H

// Teensy++ 1.0 & 2.0
#elif defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
  #define COUNTER_USE_TIMER1    // T1 is pin 6   (has LED connected)
  //#define COUNTER_USE_TIMER3  // T3 is pin 13
  #define TIMER_USE_TIMER2

// Sanguino
#elif defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644__)
  #define COUNTER_USE_TIMER1    // T1 is pin 1
  #define TIMER_USE_TIMER2

// Arduino Duemilanove, Diecimila, LilyPad, Mini, Fio, etc
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
  #define COUNTER_USE_TIMER1    // T1 is pin 5
  #define TIMER_USE_TIMER2

#else
  #error "Unknown chip, please edit me with timer+counter definitions"

#endif


/**********************************************/
/*   Counter Hardware Abstraction             */
/**********************************************/

#if defined(COUNTER_USE_TIMER1) // 16 bit Timer 1

static uint8_t saveTCCR1A, saveTCCR1B;

static inline void counter_init(void)
{
	saveTCCR1A = TCCR1A;
	saveTCCR1B = TCCR1B;
	TCCR1B = 0;
	TCCR1A = 0;
	TCNT1 = 0;
	TIFR1 = (1<<TOV1);
	TIMSK1 = 0;
}

static inline void counter_start(void)
{
	TCCR1B = (1<<CS12) | (1<<CS11) | (1<<CS10);
}

static inline void counter_shutdown(void)
{
	TCCR1B = 0;
	TCCR1A = saveTCCR1A;
	TCCR1B = saveTCCR1B;
}

static inline uint16_t counter_read(void)
{
	return TCNT1;
}

static inline uint8_t counter_overflow(void)
{
	return TIFR1 & (1<<TOV1);
}

static inline uint8_t counter_overflow_reset(void)
{
	return TIFR1 = (1<<TOV1);
}



#elif defined(COUNTER_USE_TIMER3) // 16 bit Timer 3

static uint8_t saveTCCR3A, saveTCCR3B;

static inline void counter_init(void)
{
	saveTCCR3A = TCCR3A;
	saveTCCR3B = TCCR3B;
	TCCR3B = 0;
	TCCR3A = 0;
	TCNT3 = 0;
	TIFR3 = (1<<TOV3);
	TIMSK3 = 0;
}

static inline void counter_start(void)
{
	TCCR3B = (1<<CS32) | (1<<CS31) | (1<<CS30);
}

static inline void counter_shutdown(void)
{
	TCCR3B = 0;
	TCCR3A = saveTCCR3A;
	TCCR3B = saveTCCR3B;
}

static inline uint16_t counter_read(void)
{
	return TCNT3;
}

static inline uint8_t counter_overflow(void)
{
	return TIFR3 & (1<<TOV3);
}

static inline uint8_t counter_overflow_reset(void)
{
	return TIFR3 = (1<<TOV3);
}


#elif defined(COUNTER_USE_TIMER4) // 16 bit Timer 4

static uint8_t saveTCCR4A, saveTCCR4B;

static inline void counter_init(void)
{
	saveTCCR4A = TCCR4A;
	saveTCCR4B = TCCR4B;
	TCCR4B = 0;
	TCCR4A = 0;
	TCNT4 = 0;
	TIFR4 = (1<<TOV4);
	TIMSK4 = 0;
}

static inline void counter_start(void)
{
	TCCR4B = (1<<CS42) | (1<<CS41) | (1<<CS40);
}

static inline void counter_shutdown(void)
{
	TCCR4B = 0;
	TCCR4A = saveTCCR4A;
	TCCR4B = saveTCCR4B;
}

static inline uint16_t counter_read(void)
{
	return TCNT4;
}

static inline uint8_t counter_overflow(void)
{
	return TIFR4 & (1<<TOV4);
}

static inline uint8_t counter_overflow_reset(void)
{
	return TIFR4 = (1<<TOV4);
}


#elif defined(COUNTER_USE_TIMER5) // 16 bit Timer 5

static uint8_t saveTCCR5A, saveTCCR5B;

static inline void counter_init(void)
{
	saveTCCR5A = TCCR5A;
	saveTCCR5B = TCCR5B;
	TCCR5B = 0;
	TCCR5A = 0;
	TCNT5 = 0;
	TIFR5 = (1<<TOV5);
	TIMSK5 = 0;
}

static inline void counter_start(void)
{
	TCCR5B = (1<<CS52) | (1<<CS51) | (1<<CS50);
}

static inline void counter_shutdown(void)
{
	TCCR5B = 0;
	TCCR5A = saveTCCR5A;
	TCCR5B = saveTCCR5B;
}

static inline uint16_t counter_read(void)
{
	return TCNT5;
}

static inline uint8_t counter_overflow(void)
{
	return TIFR5 & (1<<TOV5);
}

static inline uint8_t counter_overflow_reset(void)
{
	return TIFR5 = (1<<TOV5);
}


#endif // COUNTER_USE_***



/**********************************************/
/*   Timer Hardware Abstraction               */
/**********************************************/

#if defined(TIMER_USE_TIMER2) // 8 bit Timer 2

#if F_CPU == 16000000L
  #define TIMER2_OCR2A_VAL   124			// div 125
  #define TIMER2_TCCR2B_VAL  (1<<CS22) | (1<<CS20)	// div 128
#elif F_CPU == 8000000L
  #define TIMER2_OCR2A_VAL   124			// div 125
  #define TIMER2_TCCR2B_VAL  (1<<CS22)			// div 64
#elif F_CPU == 4000000L
  #define TIMER2_OCR2A_VAL   124			// div 125
  #define TIMER2_TCCR2B_VAL  (1<<CS21) | (1<<CS20)	// div 32
#elif F_CPU == 2000000L
  #define TIMER2_OCR2A_VAL   249			// div 250
  #define TIMER2_TCCR2B_VAL  (1<<CS21)			// div 8
#elif F_CPU == 1000000L
  #define TIMER2_OCR2A_VAL   124			// div 125
  #define TIMER2_TCCR2B_VAL  (1<<CS21)			// div 8
#else
#error "Clock must be 16, 8, 4, 2 or 1 MHz"
#endif

static uint8_t saveTCCR2A, saveTCCR2B;

static inline uint16_t timer_init(uint16_t msec)
{
	saveTCCR2A = TCCR2A;
	saveTCCR2B = TCCR2B;
	TCCR2B = 0;
	TCCR2A = (1<<WGM21);
	OCR2A = TIMER2_OCR2A_VAL;
	TIFR2 = (1<<OCF2A);
	TCNT2 = 0;
	return msec;
}

static inline void timer_start(void)
{
	GTCCR = (1<<PSRASY);
	TCCR2B = TIMER2_TCCR2B_VAL;
	TIMSK2 = (1<<OCIE2A);
}

static inline void timer_shutdown(void)
{
	TCCR2B = 0;
	TIMSK2 = 0;
	TCCR2A = saveTCCR2A;
	TCCR2B = saveTCCR2B;
}

#define TIMER_ISR_VECTOR TIMER2_COMPA_vect

/*
There is a typical latency from the timer interrupt until the first
actual line of code executes.  Here is a typical compiler output of
approximately 34 cycles.  When starting, this same delay is used to
begin counting, so the first reading will not have 34 cycles of
extra measurement.  Because each measurement period gates instantly
after the previous, this approximate correction only affects the
first measurement.  If you do not define TIMER_LATENCY_CYCLES, this
extra delay is skipped (saving a tiny bit of code space), and the
only downside is a slight inaccuracy in the first measurement.
2  00000326 <__vector_13>:
2       326:       1f 92           push    r1
2       328:       0f 92           push    r0
1       32a:       0f b6           in      r0, 0x3f        ; 63
2       32c:       0f 92           push    r0
1       32e:       11 24           eor     r1, r1
2       330:       ef 92           push    r14
2       332:       ff 92           push    r15
2       334:       0f 93           push    r16
2       336:       1f 93           push    r17
2       338:       2f 93           push    r18
2       33a:       3f 93           push    r19
2       33c:       4f 93           push    r20
2       33e:       5f 93           push    r21
2       340:       8f 93           push    r24
2       342:       9f 93           push    r25
2       344:       af 93           push    r26
2       346:       bf 93           push    r27
*/
#define TIMER_LATENCY_CYCLES 34



#elif defined(TIMER_USE_TIMER4H)  // 10 bit "high speed" Timer 4

#if F_CPU == 16000000L
  #define TIMER4H_OCR4C_VAL   124				// div 125
  #define TIMER4H_TCCR4B_VAL  (1<<CS43)				// div 128
#elif F_CPU == 8000000L
  #define TIMER4H_OCR4C_VAL   124				// div 125
  #define TIMER4H_TCCR4B_VAL  (1<<CS42) | (1<<CS41) | (1<<CS40)	// div 64
#elif F_CPU == 4000000L
  #define TIMER4H_OCR4C_VAL   124				// div 125
  #define TIMER4H_TCCR4B_VAL  (1<<CS42) | (1<<CS41)		// div 32
#elif F_CPU == 2000000L
  #define TIMER4H_OCR4C_VAL   124				// div 125
  #define TIMER4H_TCCR4B_VAL  (1<<CS42) | (1<<CS40)		// div 16
#elif F_CPU == 1000000L
  #define TIMER4H_OCR4C_VAL   124				// div 125
  #define TIMER4H_TCCR4B_VAL  (1<<CS42)				// div 8
#else
#error "Clock must be 16, 8, 4, 2 or 1 MHz"
#endif

static uint8_t saveTCCR4A, saveTCCR4B, saveTCCR4C, saveTCCR4D, saveTCCR4E, saveOCR4C;

static inline uint16_t timer_init(uint16_t msec)
{
	saveTCCR4A = TCCR4A;
	saveTCCR4B = TCCR4B;
	saveTCCR4C = TCCR4C;
	saveTCCR4D = TCCR4D;
	saveTCCR4E = TCCR4E;
	saveOCR4C = OCR4C;
	TCCR4B = 0;
	TCCR4A = 0;
	TCCR4C = 0;
	TCCR4D = 0;
	TCCR4E = 0;
	OCR4C = TIMER4H_OCR4C_VAL;
	TIFR4 = (1<<TOV4);
	TCNT4 = 0;
	return msec;
}

static inline void timer_start(void)
{
	TCCR4B = TIMER4H_TCCR4B_VAL | (1<<PSR4);
	TIMSK4 = (1<<TOIE4);
}

static inline void timer_shutdown(void)
{
	TCCR2B = 0;
	TIMSK4 = 0;
	OCR4C = saveOCR4C;
	TCCR4A = saveTCCR4A;
	TCCR4C = saveTCCR4C;
	TCCR4D = saveTCCR4D;
	TCCR4E = saveTCCR4E;
	TCCR4B = saveTCCR4B;
}

#define TIMER_ISR_VECTOR TIMER4_OVF_vect
#define TIMER_LATENCY_CYCLES 34


#endif // TIMER_USE_***




static inline void timer_isr_latency_delay(void)
{
#ifdef TIMER_LATENCY_CYCLES
	uint8_t cycles_times_3 = TIMER_LATENCY_CYCLES / 3;
	asm volatile(
		"L_%=_loop:"
		"subi   %0, 1"		"\n\t"
		"brne   L_%=_loop"	"\n\t"
		: "+d" (cycles_times_3)
		: "0" (cycles_times_3)
	);
#endif
}


/**********************************************/
/*   Board Specific Interrupts (to hog)       */
/**********************************************/

static inline void disable_other_interrupts(void)
{
}
static inline void restore_other_interrupts(void)
{
}



#endif
