
#define GPK1CON (*(volatile unsigned long *)(0x11000000 + 0x0060))
#define GPK1DAT (*(volatile unsigned long *)(0x11000000 + 0x0064))
#define GPK1PUD (*(volatile unsigned long *)(0x11000000 + 0x0068))
#define GPK1DRV (*(volatile unsigned long *)(0x11000000 + 0x006C))
#define GPL2CON (*(volatile unsigned long *)(0x11000000 + 0x0100))
#define GPL2DAT (*(volatile unsigned long *)(0x11000000 + 0x0104))
#define GPL2PUD (*(volatile unsigned long *)(0x11000000 + 0x0108))
#define GPL2DRV (*(volatile unsigned long *)(0x11000000 + 0x010C))

void led2_on(void)
{
	GPL2CON = (GPL2CON & ~(0xF << 0)) | (1 << 0);
	GPL2DAT = GPL2DAT | (1 << 0);
}

void led2_off(void)
{
	GPL2DAT = GPL2DAT & ~(1 << 0);
}

void led3_on(void)
{
	GPK1CON = (GPK1CON & ~(0xF << 4)) | (1 << 4);
	GPK1DAT = GPK1DAT | (1 << 1);
}

void led3_off(void)
{
	GPK1DAT = GPK1DAT & ~(1 << 1);
}
