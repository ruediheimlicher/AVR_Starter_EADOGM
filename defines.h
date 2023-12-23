/*
 * ----------------------------------------------------------------------------
 * defines
 */

#define LOOPLED_PORT	PORTD
#define LOOPLED_DDR	DDRD
#define LOOPLED_PIN	5


#define OSZIPORT           PORTD
#define OSZIPORTDDR        DDRD
#define OSZIPORTPIN        PIND
#define OSZI_PULS_A        6
#define OSZI_PULS_B        7

#define OSZI_A_LO() OSZIPORT &= ~(1<<OSZI_PULS_A)
#define OSZI_A_HI() OSZIPORT |= (1<<OSZI_PULS_A)
#define OSZI_A_TOGG()  OSZIPORT ^= (1<<OSZI_PULS_A)


#define OSZI_B_LO() OSZIPORT &= ~(1<<OSZI_PULS_B)
#define OSZI_B_HI() OSZIPORT |= (1<<OSZI_PULS_B)
#define OSZI_B_TOGG() OSZIPORT ^= (1<<OSZI_PULS_B)



