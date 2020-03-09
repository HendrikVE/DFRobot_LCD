/*!
 * @file DFRobot_LCD.h
 * @brief DFRobot's LCD
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2016
 * @copyright	GNU Lesser General Public License
 *
 * @author [yangyang](971326313@qq.com)
 * @version  V1.0
 * @date  2017-2-10
 */


#ifndef DFRobot_LCD_H
#define DFRobot_LCD_H

#include <inttypes.h>
#include "Print.h"

/*!
 *  @brief Device I2C address
 */
#define LCD_ADDRESS     (0x7c >> 1)
#define RGB_ADDRESS     (0xc0 >> 1)


/*!
 *  @brief Color defines
 */
#define WHITE           0
#define RED             1
#define GREEN           2
#define BLUE            3
#define ONLY            3

#define REG_RED         0x04        // pwm2
#define REG_GREEN       0x03        // pwm1
#define REG_BLUE        0x02        // pwm0
#define REG_ONLY        0x02

#define REG_MODE1       0x00
#define REG_MODE2       0x01
#define REG_OUTPUT      0x08

/*!
 *  @brief Commands
 */
#define CMD_LCD_CLEAR_DISPLAY 0x01
#define CMD_LCD_RETURN_HOME 0x02
#define CMD_LCD_ENTRY_MODE_SET 0x04
#define CMD_LCD_DISPLAY_CONTROL 0x08
#define CMD_LCD_CURSOR_SHIFT 0x10
#define CMD_LCD_FUNCTION_SET 0x20
#define CMD_LCD_SET_CGRAM_ADDR 0x40
#define CMD_LCD_SET_DDRAM_ADDR 0x80

/*!
 *  @brief Flags for display entry mode
 */
#define FLAG_LCD_ENTRY_RIGHT 0x00
#define FLAG_LCD_ENTRY_LEFT 0x02
#define FLAG_LCD_ENTRY_SHIFT_INCREMENT 0x01
#define FLAG_LCD_ENTRY_SHIFT_DECREMENT 0x00

/*!
 *  @brief Flags for display on/off control
 */
#define FLAG_LCD_DISPLAY_ON 0x04
#define FLAG_LCD_DISPLAY_OFF 0x00
#define FLAG_LCD_CURSOR_ON 0x02
#define FLAG_LCD_CURSOR_OFF 0x00
#define FLAG_LCD_BLINK_ON 0x01
#define FLAG_LCD_BLINK_OFF 0x00

/*!
 *  @brief Flags for display/cursor shift
 */
#define FLAG_LCD_DISPLAY_MOVE 0x08
#define FLAG_LCD_CURSOR_MOVE 0x00
#define FLAG_LCD_MOVE_RIGHT 0x04
#define FLAG_LCD_MOVE_LEFT 0x00

/*!
 *  @brief Flags for function set
 */
#define FLAG_LCD_8_BIT_MODE 0x10
#define FLAG_LCD_4_BIT_MODE 0x00
#define FLAG_LCD_2_LINE 0x08
#define FLAG_LCD_1_LINE 0x00
#define FLAG_LCD_5x10_DOTS 0x04
#define FLAG_LCD_5x8_DOTS 0x00

class DFRobot_LCD : public Print {

public:

    /*!
    *  @brief Constructor
    */
    DFRobot_LCD(uint8_t lcd_cols, uint8_t lcd_rows,
                uint8_t lcd_Addr = LCD_ADDRESS,
                uint8_t RGB_Addr = RGB_ADDRESS);

    /*!
    *  @brief Initialize
    */
    void init();

    void clear();

    void home();

    /*!
    *  @brief Turn the display on/off (quickly)
    */
    void noDisplay();

    void display();

    /*!
    *  @brief Turn on and off the blinking showCursor
    */
    void stopBlink();

    void blink();

    /*!
    *  @brief Turns the underline showCursor on/off
    */
    void noCursor();

    void cursor();

    /*!
    *  @brief These commands scroll the display without changing the RAM
    */
    void scrollDisplayLeft();

    void scrollDisplayRight();

    /*!
    *  @brief This is for text that flows left to right
    */
    void leftToRight();

    /*!
    *  @brief This is for text that flows right to left
    */
    void rightToLeft();

    /*!
    *  @brief This will 'left justify' text from the showCursor
    */
    void noAutoscroll();

    /*!
    *  @brief This will 'right justify' text from the showCursor
    */
    void autoscroll();

    /*!
    *  @brief Allows us to fill the first 8 CGRAM locations
    *         with custom characters
    */
    void customSymbol(uint8_t, uint8_t[]);

    void setCursor(uint8_t, uint8_t);

    /*!
    *  @brief Color control
    */
    void setRGB(uint8_t r, uint8_t g, uint8_t b);               // set rgb
    void setPWM(uint8_t color, uint8_t pwm) {
        setReg(color, pwm);
    }      // set pwm
    void setColor(uint8_t color);

    void setColorAll() { setRGB(0, 0, 0); }

    void setColorWhite() { setRGB(255, 255, 255); }

    /*!
    *  @brief Blink the LED backlight
    */
    void blinkLED(void);

    void noBlinkLED(void);

    /*!
    *  @brief Send data
    */
    virtual size_t write(uint8_t);

    /*!
    *  @brief Send command
    */
    void command(uint8_t);

    /*!
    *  @brief Compatibility API function aliases
    */
    void blink_on();      // alias for blink()
    void blink_off();     // alias for noBlink()
    void cursor_on();     // alias for cursor()
    void cursor_off();    // alias for noCursor()
    void
    setBacklight(uint8_t new_val);   // alias for backlight() and nobacklight()
    void load_custom_character(uint8_t char_num,
                               uint8_t *rows);  // alias for createChar()
    void printstr(const char[]);

    /*!
    *  @brief Unsupported API functions (not implemented in this library)
    */
    uint8_t status();

    void setContrast(uint8_t new_val);

    uint8_t keypad();

    void setDelay(int, int);

    void on();

    void off();

    uint8_t init_bargraph(uint8_t graphtype);

    void draw_horizontal_graph(uint8_t row, uint8_t column, uint8_t len,
                               uint8_t pixel_col_end);

    void draw_vertical_graph(uint8_t row, uint8_t column, uint8_t len,
                             uint8_t pixel_col_end);

    using Print::write;

private:
    void begin(uint8_t cols, uint8_t rows, uint8_t charsize = FLAG_LCD_5x8_DOTS);

    void send(uint8_t *data, uint8_t len);

    void setReg(uint8_t addr, uint8_t data);

    uint8_t _showfunction;
    uint8_t _showcontrol;
    uint8_t _showmode;
    uint8_t _initialized;
    uint8_t _numlines, _currline;
    uint8_t _lcdAddr;
    uint8_t _RGBAddr;
    uint8_t _cols;
    uint8_t _rows;
    uint8_t _backlightval;
};

#endif /* DFRobot_LCD_H */
