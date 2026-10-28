#include <avr/io.h>
#include <util/delay.h>

void spi0_init_master(void)
{
    // PA4=MOSI, PA5=MISO, PA6=SCK, PA7=SS
    PORTA.DIRSET = PIN4_bm | PIN6_bm | PIN7_bm; // Outputs
    PORTA.DIRCLR = PIN5_bm;                     // Input

    // Set SS high initially
    PORTA.OUTSET = PIN7_bm;

    // Enable SPI0 Master, Prescaler DIV4, Mode 0
    SPI0.CTRLA = SPI_ENABLE_bm | SPI_MASTER_bm | SPI_PRESC_DIV4_gc;
    SPI0.CTRLB = 0; // Unbuffered mode
}

void spi0_send(uint8_t data)
{
    PORTA.OUTCLR = PIN7_bm;                 // SS low
    SPI0.DATA = data;                        // Load data
    while (!(SPI0.INTFLAGS & SPI_IF_bm));   // Wait for transfer complete
    SPI0.INTFLAGS = SPI_IF_bm;              // Clear flag
    PORTA.OUTSET = PIN7_bm;                 // SS high
}

int main(void)
{
    spi0_init_master();
spi0_send('|');
spi0_send(0x0D);

    while (1)
    {


        // Optional delay to avoid spamming
        _delay_ms(500);
    }
}

