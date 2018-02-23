const int DATA_PIN = 0x04; // digital pin 2
const int SYNC_PIN = 0x08; // digital pin 3

const int BIT_WIDTH = 18; // microseconds (us)
const unsigned int INTERBYTE_GAP = 6; // microseconds (us)

const int INTERPACKET_GAP = 15; // milliseconds (ms)

const int TX_BUFFER_SIZE = 12;
uint8_t tx_buffer[TX_BUFFER_SIZE]; // data to be transmitted to the SPS HC20

unsigned long last_tx_time = 0;

void setup()
{
    // set DATA_PIN & SYNC_PIN as output
    DDRD |= DATA_PIN | SYNC_PIN;

    // assert DATA & SYNC lines
    PORTD |= DATA_PIN | SYNC_PIN;

    tx_buffer[ 0] = 0x3f; // 0
    tx_buffer[ 1] = 0x00; //
    tx_buffer[ 2] = 0x00; //
    tx_buffer[ 3] = 0x3f; // 0
    tx_buffer[ 4] = 0x06; // 1
    tx_buffer[ 5] = 0xfd; // 6.
    tx_buffer[ 6] = 0x6d; // 5
    tx_buffer[ 7] = 0x6f; // 9
    tx_buffer[ 8] = 0x00; //
    tx_buffer[ 9] = 0x00; //
    tx_buffer[10] = 0x3f; // 0
    tx_buffer[11] = 0x3f; // 0
}

void transmit_bit(int value)
{
    // set DATA line
    if (value)
        PORTD |= DATA_PIN;
    else
        PORTD &= ~DATA_PIN;

    // generate SYNC pulse
    PORTD &= ~SYNC_PIN;
    delayMicroseconds(BIT_WIDTH / 2);
    PORTD |= SYNC_PIN;
    delayMicroseconds(BIT_WIDTH / 2);
}

void transmit_byte(uint8_t value)
{
    for (int i = 0; i < 8; i++)
        transmit_bit(value & (0x80 >> i));

    delayMicroseconds(INTERBYTE_GAP);
}

void transmit_buffer(const uint8_t* buffer, int size)
{
    for (int i = 0; i < size; i++)
        transmit_byte(buffer[i]);
}

void loop()
{
    unsigned long curr_time = millis();

    if (curr_time - last_tx_time >= INTERPACKET_GAP) {
        transmit_buffer(tx_buffer, TX_BUFFER_SIZE);

        // assert DATA & SYNC lines
        PORTD |= DATA_PIN | SYNC_PIN;

        last_tx_time = curr_time;
    }
}
