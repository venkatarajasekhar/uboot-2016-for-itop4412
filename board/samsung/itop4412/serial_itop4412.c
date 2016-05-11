#include <serial.h>
#include <mach/uart.h>
#include <mach/periph.h>

#define CLK_SRC_PERIL0      (0x10030000 + 0xC250)
#define CLK_SRC_MASK_PERIL0 (0x10030000 + 0xC350)
#define CLK_DIV_PERIL0      (0x10030000 + 0xC550)
#define CLK_DIV_STAT_PERIL0 (0x10030000 + 0xC650)

#define UART_REG_BASE (0x13820000)

static struct s5p_uart *uart = (struct s5p_uart *)UART_REG_BASE;

static void s5p_serial_putc(const char ch)
{
	while (!(readl(&uart->utrstat) & (1 << 2)));

	writeb(ch, &uart->utxh);
}

static int s5p_serial_getc(void)
{
	while (!(readl(&uart->utrstat) & (1 << 0)));

	return (int)(readb(&uart->urxh) & 0xff);
}

static void s5p_serial_baud(void)
{
	/* clock for uart init */
	writel((readl(CLK_SRC_PERIL0) & ~(0xF << 8)) | (0x6 << 8), CLK_SRC_PERIL0);
	writel(readl(CLK_SRC_MASK_PERIL0) | (1 << 8), CLK_SRC_MASK_PERIL0);
	writel((readl(CLK_DIV_PERIL0) & ~(0xF << 8)) | (13 << 8), CLK_DIV_PERIL0);

	while(readl(CLK_DIV_STAT_PERIL0) & (1 << 8));

	writel(0x2 << 0 | 0x2 << 4, (0x11400000 + 0x0020));
	writel(30, &uart->ubrdiv);
	writeb(0 , &uart->rest.value);
}

static int s5p_serial_tstc(void)
{
	return 0;
}

static int s5p_serial_init(void);
static struct serial_device s5p_serial = {
	.name = "s5p_serial",
	.start = s5p_serial_init,
	.setbrg = s5p_serial_baud,
	.putc = s5p_serial_putc,
	.puts = default_serial_puts,
	.getc = s5p_serial_getc,
	.tstc = s5p_serial_tstc,
};

static int s5p_serial_init(void)
{
	/* enable FIFOs, auto clear Rx FIFO */
	writel((7 << 8) | (1 << 2) | (1 << 0), &uart->ufcon);
	writel(0, &uart->umcon);
	/* 8N1 */
	writel(0x3, &uart->ulcon);
	/* No interrupts, no DMA, pure polling */
	writel(0x5, &uart->ucon);

	s5p_serial_baud();

	serial_register(&s5p_serial);
	return 0;
}

struct serial_device *default_serial_console(void)
{
	return &s5p_serial;
}
