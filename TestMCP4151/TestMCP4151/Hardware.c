void Init_Hardware(void)
{
	/* Configuration I/O */

	// LED en PA3 en mode Output
	SET_BIT(DDRA, DDA3);
	// LED OFF au démarrage
	CLR_BIT(PORTA, PA3);

	// RELAIS en PD6 en mode Output
	SET_BIT(DDRD, DDD6);
	// Contacts RELAIS ouverts au démarrage
	Relais = FALSE;
	CLR_BIT(PORTD, PD6);

	// Bouton poussoir en PD2 en mode Input avec pull up
	CLR_BIT(DDRD, DDD2);
	// Pull UP en PD2 enabled
	SET_BIT(PORTD, PD2);

	// Contact secondaire relais en PA6 en mode Input avec pull up
	CLR_BIT(DDRA, DDA6);
	// Pull UP en PA6 enabled
	SET_BIT(PORTA, PA6);

	// Interruption externe via INT0 de la broche PD2 enabled
	SET_BIT(EIMSK, INT0);
	// Interruption sur flanc descendant (EICRA : ISC01 = 1 | ISC00 = 0)
	SET_BIT(EICRA, ISC01);
	CLR_BIT(EICRA, ISC00);

	// Configuration clavier 5 touches : UP (PC6), DOWN (PC4), LEFT (PC5), RIGHT (PC2), ENTER (PC3)
	// Input Mode
	CLR_BIT(DDRC, DDC6);
	CLR_BIT(DDRC, DDC2);
	CLR_BIT(DDRC, DDC3);
	CLR_BIT(DDRC, DDC4);
	CLR_BIT(DDRC, DDC5);
	// Enable pull up
	SET_BIT(PORTC, PORTC6);
	SET_BIT(PORTC, PORTC2);
	SET_BIT(PORTC, PORTC3);
	SET_BIT(PORTC, PORTC4);
	SET_BIT(PORTC, PORTC5);
	// Enable interrupts
	SET_BIT(PCICR, PCIE2);
	// Enable mask
	SET_BIT(PCMSK2, PCINT22); // UP
	SET_BIT(PCMSK2, PCINT18); // RIGHT
	SET_BIT(PCMSK2, PCINT19); // ENTER
	SET_BIT(PCMSK2, PCINT20); // DOWN
	SET_BIT(PCMSK2, PCINT21); // LEFT

	// ADC sur PA7
	CLR_BIT(DDRA, DDA7); // Input Mode

	// PWM
	// PWM1B sur PD4, Output Mode
	SET_BIT(DDRD, DDD4);
	// PWM1A sur PD5, Output Mode
	SET_BIT(DDRD, DDD5);
	// PWM3A sur PB6, Output Mode
	SET_BIT(DDRB, DDB6);

	// Sortie PWM Timer2
	SET_BIT(DDRD, DDD7); // OC2A (sortie)

	// CS DAC (SPI) en PC7
	SET_BIT(DDRC, DDC7);
	SET_BIT(PORTC, PORTC7); // CS non activé (à HIGH par défaut)

	// CS MCP4151 (SPI) en PB4
	SET_BIT(DDRB, DDB4);
	SET_BIT(PORTB, PORTB4); // CS non activé (à HIGH par défaut)

	// FOR DEBUG
	SET_BIT(DDRB, DDB4);
	CLR_BIT(PORTB, PORTB4);
}
