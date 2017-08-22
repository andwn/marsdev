// Required headers
#include <stdint.h>
#include "echoblob.h"
#include "echo.h"

// Z80 addresses
static volatile uint8_t*  const z80_ram    = (uint8_t *)  0xA00000;
static volatile uint16_t* const z80_busreq = (uint16_t *) 0xA11100;
static volatile uint16_t* const z80_reset  = (uint16_t *) 0xA11200;

// Macros to control the Z80
#define Z80_REQUEST() \
   { *z80_busreq = 0x100; while (*z80_busreq & 0x100); }
#define Z80_RELEASE() \
   { *z80_busreq = 0; }
#define Z80_RESET() \
   { *z80_reset = 0; \
     volatile int16_t i; for (i = 4; i >= 0; i--); \
     *z80_reset = 0x100; }

// Macro to add delays
// Using volatile is needlessly ugly but at least portable
// GCC is already awful at optimizing, so this isn't that bad...
#define DELAY() \
   { volatile int16_t i; for (i = 0xFF; i >= 0; i--); }

// Look-up tables for echo_set_volume
static const uint8_t fm_volumes[] = {
   0x7F,0x7B,0x77,0x73,0x70,0x6C,0x68,0x65,
   0x61,0x5E,0x5A,0x57,0x54,0x50,0x4D,0x4A,
   0x47,0x44,0x41,0x3F,0x3C,0x39,0x36,0x34,
   0x31,0x2F,0x2D,0x2A,0x28,0x26,0x24,0x22,
   0x20,0x1E,0x1C,0x1A,0x18,0x16,0x15,0x13,
   0x12,0x10,0x0F,0x0D,0x0C,0x0B,0x0A,0x09,
   0x08,0x07,0x06,0x05,0x04,0x04,0x03,0x02,
   0x02,0x01,0x01,0x01,0x00,0x00,0x00,0x00
};
static const uint8_t psg_volumes[] = {
   0x0F,0x0F,0x0E,0x0E,0x0D,0x0D,0x0C,0x0C,
   0x0B,0x0B,0x0B,0x0A,0x0A,0x0A,0x09,0x09,
   0x08,0x08,0x08,0x07,0x07,0x07,0x06,0x06,
   0x06,0x06,0x05,0x05,0x05,0x04,0x04,0x04,
   0x04,0x03,0x03,0x03,0x03,0x03,0x02,0x02,
   0x02,0x02,0x02,0x02,0x01,0x01,0x01,0x01,
   0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

//***************************************************************************
// echo_init
// Initializes Echo and gets it running.
//---------------------------------------------------------------------------
// param list: pointer to instrument list
//***************************************************************************

void echo_init(const void* const* list) {
   // Take over the Z80
   Z80_RESET();
   Z80_REQUEST();
   
   // Tell Echo to not run any commands by default (the assembly counterpart
   // would tell it to load the instrument list, but we can't do that here
   // due to linker shenanigans)
   z80_ram[0x1FFF] = 0x00;
   
   // Direct stream is empty yet
   z80_ram[0x1F00] = 0xFF;
   
   // Load the instrument list manually, since thanks to linker shenanigans
   // we can't implement the list properly in ROM :/
   volatile uint8_t *dest = &z80_ram[0x1C00];
   while (*list) {
      // Retrieve pointer to next instrument
      // Cast it to an integer since we need to treat it as such
      // This should be considered bad C, but since this is hardware-specific
      // code this should be fine to do (portability is not expected)
      uint32_t ptr = (uint32_t) *list;
      
      // Turn the pointer into the base+address notation Echo wants and store
      // it in Z80 RAM directly (where the list would go)
      dest[0x000] = (ptr >> 8 & 0x7F) | 0x80;
      dest[0x100] = (ptr & 0xFF);
      dest[0x200] = (ptr >> 15 & 0x7F) | (ptr >> 16 & 0x80);
      
      // Go for next pointer
      list++;
      dest++;
   }
   
   // Copy the Echo blob into Z80 RAM
   // No, memcpy() won't do here since we must ensure accesses are byte-sized
   // (memcpy() may not know this and try word or long accesses)
   const uint8_t *src = res_echoblob;
   dest = z80_ram;
   int16_t count = sizeof(res_echoblob)-1;
   while (count-- >= 0)
      *dest++ = *src++;
   
   // Set up global volume
   int i;
   for (i = 0; i < 16; i++)
      z80_ram[0x1FE0+i] = 0;
   z80_ram[0x1FEC] = 1;
   z80_ram[0x1FF1] = 1;
   
   // Let Echo start running!
   Z80_RESET();
   Z80_RELEASE();
}

//***************************************************************************
// echo_send_command
// Sends a raw command to Echo. No parameters are taken.
//---------------------------------------------------------------------------
// param cmd: command to send
//***************************************************************************

void echo_send_command(uint8_t cmd) {
   // We need access to Z80 bus
   Z80_REQUEST();
   
   // Is Echo busy yet?
   volatile uint8_t *ptr = &z80_ram[0x1FFC];
   if (ptr[3] != 0x00) {
      ptr -= 4;
      while (ptr[3] != 0x00) {
         Z80_RELEASE();
         DELAY();
         Z80_REQUEST();
      }
   }
   
   // Write the command
   ptr[3] = cmd;
   
   // Done with the Z80
   Z80_RELEASE();
}

//***************************************************************************
// echo_send_command_addr
// Sends a raw command to Echo. An address parameter is taken.
//---------------------------------------------------------------------------
// param cmd: command to send
// param addr: address parameter
//***************************************************************************

void echo_send_command_addr(uint8_t cmd, const void *addr) {
   // Since we need to split the address into multiple bytes we put it in an
   // integer. This is a bad practice in general, period, but since we don't
   // care about portability here we can afford to do it this time.
   uint32_t param = (uint32_t) addr;
   
   // We need access to Z80 bus
   Z80_REQUEST();
   
   // Is Echo busy yet?
   volatile uint8_t *ptr = &z80_ram[0x1FFC];
   if (ptr[3] != 0x00) {
      ptr -= 4;
      while (ptr[3] != 0x00) {
         Z80_RELEASE();
         DELAY();
         Z80_REQUEST();
      }
   }
   
   // Write the command
   ptr[3] = cmd;
   ptr[1] = param;
   param >>= 8;
   ptr[2] = param | 0x80;
   param >>= 7;
   param = (param & 0x7F) | (param >> 1 & 0x80);
   ptr[0] = param;
   
   // Done with the Z80
   Z80_RELEASE();
}

//***************************************************************************
// echo_send_command_byte
// Sends a raw command to Echo. A byte parameter is taken.
//---------------------------------------------------------------------------
// param cmd: command to send
// param byte: parameter
//***************************************************************************

void echo_send_command_byte(uint8_t cmd, uint8_t byte) {
   // We need access to Z80 bus
   Z80_REQUEST();
   
   // Is Echo busy yet?
   volatile uint8_t *ptr = &z80_ram[0x1FFC];
   if (ptr[3] != 0x00) {
      ptr -= 4;
      while (ptr[3] != 0x00) {
         Z80_RELEASE();
         DELAY();
         Z80_REQUEST();
      }
   }
   
   // Write the command
   ptr[3] = cmd;
   ptr[0] = byte;
   
   // Done with the Z80
   Z80_RELEASE();
}

//***************************************************************************
// echo_play_bgm
// Starts playing background music.
//---------------------------------------------------------------------------
// param ptr: pointer to BGM stream
//***************************************************************************

void echo_play_bgm(const void *ptr) {
   echo_send_command_addr(ECHO_CMD_PLAYBGM, ptr);
}

//***************************************************************************
// echo_stop_bgm
// Stops background music playback.
//***************************************************************************

void echo_stop_bgm(void) {
   echo_send_command(ECHO_CMD_STOPBGM);
}

//***************************************************************************
// echo_pause_bgm
// Pauses background music playback.
//***************************************************************************

void echo_pause_bgm(void) {
   echo_send_command(ECHO_CMD_PAUSEBGM);
}

//***************************************************************************
// echo_resume_bgm
// Resumes background music playback.
//***************************************************************************

void echo_resume_bgm(void) {
   echo_send_command(ECHO_CMD_RESUMEBGM);
}

//***************************************************************************
// echo_play_sfx
// Starts playing a sound effect.
//---------------------------------------------------------------------------
// param ptr: pointer to SFX stream
//***************************************************************************

void echo_play_sfx(const void *ptr) {
   echo_send_command_addr(ECHO_CMD_PLAYSFX, ptr);
}

//***************************************************************************
// echo_stop_sfx
// Stops sound effect playback.
//***************************************************************************

void echo_stop_sfx(void) {
   echo_send_command(ECHO_CMD_STOPSFX);
}

//***************************************************************************
// echo_play_direct
// Injects events into the BGM stream for the next tick.
//---------------------------------------------------------------------------
// param ptr: pointer to BGM stream
//***************************************************************************

void echo_play_direct(const void *ptr) {
   // We need access to Z80 bus
   Z80_REQUEST();
   
   // Check where we can start writing events
   volatile uint8_t *dest = &z80_ram[0x1F00];
   while (*dest != 0xFF) dest++;
   
   // Write the events
   const uint8_t *src = (uint8_t*)(ptr);
   for (;;) {
      uint8_t byte = *src++;
      *dest++ = byte;
      if (byte == 0xFF) break;
   }
   
   // Done with the Z80
   Z80_RELEASE();
}

//***************************************************************************
// echo_set_volume
// Changes the global volume for every channel.
//---------------------------------------------------------------------------
// param vol: new volume (0 = quietest, 255 = loudest)
//***************************************************************************

void echo_set_volume(uint8_t vol) {
   // We need access to Z80 bus
   Z80_REQUEST();
   
   // Set FM volume values
   uint8_t fm_vol = fm_volumes[vol >> 2];
   z80_ram[0x1FE0] = fm_vol;
   z80_ram[0x1FE1] = fm_vol;
   z80_ram[0x1FE2] = fm_vol;
   z80_ram[0x1FE3] = fm_vol;
   z80_ram[0x1FE4] = fm_vol;
   z80_ram[0x1FE5] = fm_vol;
   z80_ram[0x1FE6] = fm_vol;
   z80_ram[0x1FE7] = fm_vol;
   
   // Set PSG volume values
   uint8_t psg_vol = psg_volumes[vol >> 2];
   z80_ram[0x1FE8] = psg_vol;
   z80_ram[0x1FE9] = psg_vol;
   z80_ram[0x1FEA] = psg_vol;
   z80_ram[0x1FEB] = psg_vol;
   
   // Determine whether to enable PCM
   z80_ram[0x1FEC] = (vol >= 0x40) ? 1 : 0;
   
   // Tell Echo to update all the volumes
   z80_ram[0x1FF1] = 1;
   
   // Done with the Z80
   Z80_RELEASE();
}

//***************************************************************************
// echo_set_volume_ex
// Changes the global volume for each individual channel.
//---------------------------------------------------------------------------
// param ptr: pointer to array with volume values
//***************************************************************************

void echo_set_volume_ex(const uint8_t *ptr) {
   // We need access to Z80 bus
   Z80_REQUEST();
   
   // Store the new volume values
   int i;
   for (i = 0; i < 16; i++)
      z80_ram[0x1FE0+i] = ptr[i];
   
   // Tell Echo to update all the volumes
   z80_ram[0x1FF1] = 1;
   
   // Done with the Z80
   Z80_RELEASE();
}

//***************************************************************************
// echo_set_pcm_rate
// Changes the playback rate of PCM.
//---------------------------------------------------------------------------
// param rate: new rate (timer A value)
//***************************************************************************

void echo_set_pcm_rate(uint8_t rate) {
   echo_send_command_byte(ECHO_CMD_SETPCMRATE, rate);
}

//***************************************************************************
// echo_get_status
// Retrieves Echo's current status.
//---------------------------------------------------------------------------
// return: status flags (see ECHO_STAT_*)
//***************************************************************************

uint16_t echo_get_status(void) {
   // Look-up tables used to work around the fact that playing/stopping
   // won't set the status immediately (only when Echo processes the command)
   // and this can catch programmers off guard
   static const uint8_t and_flags[] = {
      0xFF,0xFF, 0xFF,0xFE,0xFF,0xFD, 0xFF,0xFF,0xFF
   };
   static const uint8_t or_flags[] = {
      0x00,0x00, 0x01,0x00,0x02,0x00, 0x00,0x00,0x00
   };
   
   // We need access to the Z80
   Z80_REQUEST();
   
   // Retrieve status from Z80 RAM
   uint16_t status = 0;
   status = z80_ram[0x1FF0];
   if (z80_ram[0x1FFB] != 0)
      status |= ECHO_STAT_BUSY;
   if (z80_ram[0x1F00] != 0xFF)
      status |= ECHO_STAT_DIRBUSY;
   
   // Look ahead in the queue for any pending commands
   // Adjust the flags accordingly if needed
   uint8_t command = z80_ram[0x1FFF];
   status &= and_flags[command];
   status |= or_flags[command];
   command = z80_ram[0x1FFB];
   status &= and_flags[command];
   status |= or_flags[command];
   
   // Done with the Z80
   Z80_RELEASE();
   
   // Return status
   return status;
}

//***************************************************************************
// echo_get_flags
// Gets the current values of the flags.
//---------------------------------------------------------------------------
// return: bitmask with flags
//***************************************************************************

uint8_t echo_get_flags(void)
{
   Z80_REQUEST();
   uint8_t flags = z80_ram[0x1FF2];
   Z80_RELEASE();
   return flags;
}

//***************************************************************************
// echo_set_flags
// Sets flags from the 68000.
//---------------------------------------------------------------------------
// param flags: bitmask of flags to be set (1 = set, 0 = intact)
//***************************************************************************

void echo_set_flags(uint8_t flags)
{
   Z80_REQUEST();
   z80_ram[0x1FF2] |= flags;
   Z80_RELEASE();
}

//***************************************************************************
// echo_clear_flags
// Clears flags from the 68000.
//---------------------------------------------------------------------------
// param flags: bitmask of flags to be cleared (1 = clear, 0 = intact)
//***************************************************************************

void echo_clear_flags(uint8_t flags)
{
   Z80_REQUEST();
   z80_ram[0x1FF2] &= ~flags;
   Z80_RELEASE();
}
