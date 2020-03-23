void prueba() {
	volatile char *video = (volatile char*) 0xB8000;
	*video++ = 'H';
	*video++ = 4;
}
